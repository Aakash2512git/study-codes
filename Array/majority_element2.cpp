/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

 

Example 1:

Input: nums = [3,2,3]
Output: [3]


we will take two counter if element matches with any of them +1 other wise -1 for both


*/


class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        
        int ele1=-1,ele2=-1;
        int count1=0,count2=0;

        for(auto num:nums){
            
            if(num==ele1){
                count1++;
            }
            else if(num==ele2){
                count2++;
            }
            else if(count1==0){
                ele1=num;
                count1=1;
            }
            else if(count2==0){
                ele2=num;
                count2=1;
            }
            else
            {
                count1--;
                count2--;
            }

        }

        count1=0;
        count2=0;
        for(auto num:nums){

          if(num==ele1){
            count1++;
          }
          else if(num==ele2){
            count2++;
          }

        }
       vector<int>v;
        if(count1>nums.size()/3){
            v.push_back(ele1);
        }
        if(count2>nums.size()/3){
            v.push_back(ele2);
        }

        return v;
    }
};