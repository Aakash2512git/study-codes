/*

Input: arr[] = [1, 3, 4, 5], k = 3
Output: 5
Explanation: We can add +2 to the second element and +1 to the third element to get the array [1, 5, 5, 5]. After sorting, the array remains [1, 5, 5, 5]. Since the length is even, the median is (5 + 5) / 2 = 5.
*/


class Solution {
  public:
   bool possible(vector<int>& arr, int k,long mid){
       
       long med=0;
       
       long n=arr.size();
       long half=n/2;
       
       
       if(n%2==0){
           
           med+=max(0L,2*mid-arr[half]-arr[half-1]);
       }
       else
       {
          med+=max(0L,mid-arr[half]); 
       }
       
       for(int i=half+1;i<n;i++){
           med+=max(0L,mid-arr[i]);
       }
       return med<=k;
   }
  
    int maximizeMedian(vector<int>& arr, int k) {
        // code here
        sort(arr.begin(),arr.end());
        
        
        long  start=0;
        long end=arr[arr.size()-1]+k;
        long ans=0;
        
        while(start<=end){
            
            long mid=start+(end-start)/2;
            
            if(possible(arr,k,mid)){
                
                ans=mid;
                start=mid+1;
            }
            else
            {
                end=mid-1;
            }
            
            
        }
        
        return ans;
        
    }
};
