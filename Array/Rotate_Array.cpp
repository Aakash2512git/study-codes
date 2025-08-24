class Solution {
public:
//7654321

/*
Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

*/
    void rotate(vector<int>& nums, int k) {
       k=k%nums.size(); 

        if(nums.size()<=1){
            return;
        }
        
         reverse(nums.begin(),nums.end());
         reverse(nums.begin(),nums.begin()+k);
         reverse(nums.begin()+k,nums.end());


    }
};