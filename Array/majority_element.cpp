/*
The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 

Example 1:

Input: nums = [3,2,3]
Output: 3



*/



class Solution {
public:
    int majorityElement(vector<int>& nums) {

        int count_ele=0;
        int ele;

        for(int i=0;i<nums.size();i++){
                 if(count_ele==0){
                   ele=nums[i];
               }

               if(ele==nums[i]){
                   count_ele++;
               }
               else
               {
                count_ele--;
               }

               
        }

        return ele;
        
    }
};

