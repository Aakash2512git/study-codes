/*
The test cases are generated so that the answer will fit in a 32-bit integer.

 

Example 1:

Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.


we are multiplying from both side cause we could have found 0 from either side resulting pro 1 from each side so need to check from both side

L-> -2,-2, 2,-6
   [-2,0,-1,-3] 
    -6,3,3,-3<-R
*/


class Solution {
public:
    int maxProduct(vector<int>& nums) {
          
          double pre=1,suf=1;
          double n=nums.size();
          double max_pro=INT_MIN;

          for(int i=0;i<n;i++){
             if(pre==0){
                pre=1;
             }
             if(suf==0){
                suf=1;
             }
              
              pre=pre*nums[i];
              suf=suf*nums[n-i-1];
             
            
             max_pro=max(max_pro,max(pre,suf));


          }

          return max_pro;
        
    }
};