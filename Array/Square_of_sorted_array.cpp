
/*
Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.

Example 1:

Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].*/


class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {

        vector<int>res;
        int i=0,j=nums.size()-1;

        while(i<=j){
           int i_=nums[i]*nums[i];
           int j_=nums[j]*nums[j];
           if(i_>j_){
              res.push_back(i_);
              i++;
           } 
           else
           {
            res.push_back(j_);
            j--;
           }


        }
        reverse(res.begin(),res.end());
        return res;
    }
};