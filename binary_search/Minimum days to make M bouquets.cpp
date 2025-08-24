/*
You have a row of flowers, where each flower blooms after a specific day. The array arr[] represents the blooming schedule: arr[i] is the day the flower at position i will bloom. To create a bouquet, you need to collect k adjacent bloomed flowers. Each flower can only be used in one bouquet.

Your goal is to find the minimum number of days required to make exactly m bouquets. If it is not possible to make m bouquets with the given arrangement, return -1.

Examples:
Input: m = 3, k = 2, arr[] = [3, 4, 2, 7, 13, 8, 5]
Output: 8
Explanation: We need 3 bouquets and each bouquet should have 2 flowers. After day 8: [x, x, x, x, _, x, x], we can make first bouquet from the first 2 flowers, second bouquet from the next 2 flowers and the third bouquet from the last 2 flowers.*/



class Solution {
  public:
   bool canMake(vector<int>& arr, int k, int mid,int m){// just to calculate bokeee is equal to m
       int bokee=0;
       int count=0;
       
       for(int i=0;i<arr.size();i++){
           
             if(arr[i]>mid){
                 count=0;
             }
             else
             {
                 count++;
             }
             
             if(count==k){
                 count=0;
                 bokee++;
             }
           
       }
      return bokee>=m; 
       
   }
  
    int minDaysBloom(vector<int>& arr, int k, int m) {
        // Code here
       int start_day=0;
       int end_day=*max_element(arr.begin(),arr.end());// starting with max days
       int min_day=-1;
       
       while(start_day<=end_day){
           
           int mid=start_day+(end_day-start_day)/2;
           
           if(canMake(arr,k,mid,m)){
               min_day=mid;
               end_day=mid-1;
               
           }
           else
           {
               start_day=mid+1;
           }
           
       }
        
       return min_day; 
        
    }
};