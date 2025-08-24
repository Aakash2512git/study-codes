/*Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

*/


// By finding pivot means 0

class Solution {
public:

    int binary(vector<int>&nums,int start,int end ,int target){
            while(start<=end)
            {
                int mid=start+(end-start)/2;
                if(nums[mid]==target)
                  return mid;

                 if(nums[mid]<target)
                 {
                     start=mid+1;
                 } 
                 else
                 {
                     end=mid-1;
                 }
            }

            return -1;


    }

    int search(vector<int>& nums, int target) {
        int start=0;
        int end=nums.size()-1;

        while(start<end){
              
           int mid=start+(end-start)/2;

        
           if(nums[mid]<nums[end]){
                 end=mid  ;
           }
           else if(nums[mid]>nums[end]){
               start=mid+1;
           }


               

        }
   int pivot=start;
       cout<<pivot;
       int ans=-1;
        if(target>nums[nums.size()-1])
        {
              ans=binary(nums,0,pivot-1,target);
        }
        else
        {
           ans=binary(nums,pivot,nums.size()-1,target); 
        }



        return ans;
    }
};


// Second method

class Solution{
    public:
    int search(int a[], int l, int h, int key){
        // l: The starting index
        // h: The ending index, you have to search the key in this range
        
        //complete the function here
        while(l<=h)
        {int mid=(l+h)/2;
        
            if(a[mid]==key)
              return mid;
              if(a[l]<=a[mid])
              {
                  if(key>=a[l] and key<=a[mid])
                  {
                      h=mid-1;
                  }
                  else
                  {
                      l=mid+1;
                  }
              }
              else
              {
                  if(key>=a[mid] and key<=a[h])
                  {
                      l=mid+1;
                  }
                  else
                  {
                      h=mid-1;
                  }
                  
              }
              
        }
        
        
        return -1;
        
        
    }
};