import json
import os
from pathlib import Path
import requests
import dotenv
import yaml
from dotenv import load_dotenv
import os
import toml
from pathlib import Path

load_dotenv()  # loads .env into environment
BUILD_REQUEST_DIR = "pypi-wheel-builder/build-requests"
OUTPUT_FILE = "output/missing.json"
ARTI_URL = "https://na.artifactory.swg-devops.com/artifactory/api/search/aql"
ARTI_REPO = "wcp-wea-pypi-local"
GITHUB_TOKEN=os.getenv("GITHUB_TOKEN")
GITHUB_API = "https://api.github.com"
GITHUB_REPO = os.getenv("GITHUB_REPO")
ARTI_USER = os.getenv("ARTI_USER")
ARTI_TOKEN = os.getenv("ARTI_TOKEN")

if not ARTI_USER or not ARTI_TOKEN:
    raise RuntimeError("ARTI_USER and ARTI_TOKEN must be set")

if not GITHUB_TOKEN or not GITHUB_REPO:
    raise RuntimeError("GITHUB_TOKEN and GITHUB_REPO must be set")


HEADERS = {
    "Authorization": f"Bearer {GITHUB_TOKEN}",
    "Accept": "application/vnd.github+json",
    "X-GitHub-Api-Version": "2022-11-28",
}

REQ_FILE = None
if Path("requirements.txt").exists():
    REQ_FILE = "requirements.txt"
elif Path("pyproject.toml").exists():
    REQ_FILE = "pyproject.toml"
else:
    raise FileNotFoundError("No requirements.txt or pyproject.toml found")


def issue_exist(pkg:str,version:str):
    arch="s390x"
    python = "cp311"
    title = f"[wheel-build] {pkg}=={version} ({arch}, {python})"
    search_url = f"{GITHUB_API}/search/issues"
    query = (
        f'repo:{GITHUB_REPO} '
        f'is:issue is:open '
        f'"{title}"'
    )
    resp = requests.get(
            search_url,
            headers=HEADERS,
            params={"q": query},
            timeout=10,
        )
    
    resp.raise_for_status()
    items = resp.json().get("items", [])
    if items:
        issue = items[0]
        print(f"Issue already exists: {issue['html_url']}")
        return issue["html_url"]
    return None



def write_build_issue(pkg: str, version: str):
    arch = "s390x"
    python = "cp311"
    manylinux = "manylinux_2_34"

    title = f"[wheel-build] {pkg}=={version} ({arch}, {python})"

    body = f"""### Wheel build request

    **Package:** {pkg}  
    **Version:** {version}  
    **Python:** {python}  
    **Architecture:** {arch}  
    **Manylinux:** {manylinux}

    **Detected by:** scanner  
    **Status:** queued

    This issue was auto-generated because the wheel was not found in Artifactory.
    """

    url = f"{GITHUB_API}/repos/{GITHUB_REPO}/issues"

    payload = {
        "title": title,
        "body": body,
        "labels": [
            "wheel-build",
            "queued",
            "s390x",
            "cp311",
        ],
    }

    resp = requests.post(
        url,
        headers=HEADERS,
        json=payload,
        timeout=10,
    )
    resp.raise_for_status()

    issue = resp.json()
    print(f"Created issue: {issue['html_url']}")
    return issue["html_url"]


def wheel_exists(pkg, version):
    aql = f"""
items.find({{
  "repo": {{"$eq": "{ARTI_REPO}"}},
  "path": {{"$eq": "{pkg}/{version}"}},
  "name": {{"$match": "*s390x*.whl"}},
  "type": "file"
}})
"""
    resp = requests.post(
        ARTI_URL,
        data=aql,
        headers={
            "Content-Type": "text/plain",
            "Accept": "application/json",
        },
        auth=(ARTI_USER, ARTI_TOKEN),
        timeout=10,
    )
    resp.raise_for_status()

    results = resp.json().get("results", [])
    return len(results) > 0




def parse_pyproject(path: str):
    path = Path(path)
    if not path.exists():
        print(f"{path} not found, returning empty list")
        return []

    import toml  # make sure you imported toml
    data = toml.load(path)
    deps = []

    # PEP 621 style
    project = data.get("project", {})
    for dep in project.get("dependencies", []):
        for op in ["==", ">=", "<=", "~=", ">", "<"]:
            if op in dep:
                pkg, version = dep.split(op, 1)
                deps.append((pkg.strip(), version.strip()))
                break
        else:
            deps.append((dep.strip(), None))

    # Poetry style
    poetry_deps = data.get("tool", {}).get("poetry", {}).get("dependencies", {})
    for pkg, ver in poetry_deps.items():
        if pkg.lower() == "python":
            continue
        if isinstance(ver, str):
            deps.append((pkg, ver.lstrip("=")))
        elif isinstance(ver, dict):
            version = ver.get("version")
            if version:
                deps.append((pkg, version.lstrip("=")))

    return deps  # ALWAYS returns a list



def parse_requirements(path):
    deps = []
    for line in Path(path).read_text().splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        if "==" in line:
            name, version = line.split("==", 1)
            deps.append((name.strip(), version.strip()))
    return deps


def main():
    missing = []
    if Path("requirements.txt").exists():
        deps = parse_requirements("requirements.txt")
    elif Path("pyproject.toml").exists():
        deps = parse_pyproject("pyproject.toml")
    else:
      raise FileNotFoundError("No requirements.txt or pyproject.toml found")

    for pkg, version in deps:
        print(f"Checking {pkg}=={version}")
        if not wheel_exists(pkg, version):
            missing.append({"name": pkg, "version": version})
            if not issue_exist(pkg,version):
               write_build_issue(pkg, version)

    Path("output").mkdir(exist_ok=True)
    Path(OUTPUT_FILE).write_text(json.dumps(missing, indent=2))

    print("Missing wheels:")
    print(json.dumps(missing, indent=2))


if __name__ == "__main__":
    main()
