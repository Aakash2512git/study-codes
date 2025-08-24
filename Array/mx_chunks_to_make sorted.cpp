
/*
You are given an integer array arr of length n that represents a permutation of the integers in the range [0, n - 1].

We split arr into some number of chunks (i.e., partitions), and individually sort each chunk. After concatenating them, the result should equal the sorted array.

Return the largest number of chunks we can make to sort the array.

 

Example 1:

Input: arr = [4,3,2,1,0]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2], which isn't sorted.

The trick is focus on the max element we get while traversing 

  ** imagine this as a x-y graph 1,0,2,3,4

*/


class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
          int n=arr.size();
        int ans=0;
        int curMX=arr[0];
        for(int i=0;i<n;i++){
            curMX=max(curMX,arr[i]);
            if(curMX==i){
                ans++;
            }

        }

        return ans;
        
    }
};




/*



You are given an integer array arr of length n that represents a permutation of the integers in the range [0, n - 1].

We split arr into some number of chunks (i.e., partitions), and individually sort each chunk. After concatenating them, the result should equal the sorted array.

Return the largest number of chunks we can make to sort the array.



*/



class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n=arr.size();
        int lmax[n];
        int rmin[n];
        lmax[0]=arr[0];
        for(int i=1;i<n;i++){
            lmax[i]=max(lmax[i-1],arr[i]);
        }
        rmin[n-1]=arr[n-1];
        for(int i=n-2;i>=0;i--){
             rmin[i]=min(rmin[i+1],arr[i]);
        }
         int ans=0;
        for(int i=0;i<n-1;i++){
             if(lmax[i]<=rmin[i+1]){
                ans++;
             }

        }
       return ans+1; 
    }
};