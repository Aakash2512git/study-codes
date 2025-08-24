/*
Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.
*/


class Solution {
public:
    int maxSubArray(vector<int>& nums) {

       int max_sum=INT_MIN;
       int sum=0;
       
       int i=0,j=0;

       if(nums.size()==1){
           return nums[0];
       }

       while(i<nums.size()){
               sum+=nums[i];
                max_sum=max(max_sum,sum);
             if(sum<0){
                sum=0;

             }
             i++;

       } 
        return max_sum;
    }
};