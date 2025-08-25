/*
Example 1:

Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
Output: 15
Explanation: A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
1st day: 1, 2, 3, 4, 5
2nd day: 6, 7
3rd day: 8
4th day: 9
5th day: 10

*/


class Solution {
public:

    bool canMake(vector<int>& weights, int cap , int days){
         int count=0;
         int cnt_day=1;// we are alreday in day 1 if that cannot fill the ship cap then we add another day 

         for(int i=0;i<weights.size();i++){
             
             if(count+weights[i]<=cap){
                count+=weights[i];
             }
             else
             {     count=weights[i];
                   cnt_day++;
             }

         }

        return cnt_day<=days;
    }
    int shipWithinDays(vector<int>& weights, int days) {
         
         int capcity=*max_element(weights.begin(),weights.end());// max_weight should be the least capacity of ship 
         int mx_cap=accumulate(weights.begin(),weights.end(),0);// 

       
         int mn_cap=mx_cap;

         while(capcity<=mx_cap){
          
            int cap=capcity+(mx_cap-capcity)/2;


            if(canMake(weights,cap,days)){
                mn_cap=cap;
                mx_cap=cap-1;
            }
            else
            {
                capcity=cap+1;
            }

         }

       return mn_cap;
    }
};