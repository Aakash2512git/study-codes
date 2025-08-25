/*Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,4,7,5,3,6,8,9]*/



class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
         
         map<int,vector<int>>mp;

         for(int i=0;i<mat.size();i++){
               
               for(int j=0;j<mat[0].size();j++){

                  mp[i+j].push_back(mat[i][j]);// diagonals i,j value will be same 
               }
         }
          vector<int>res;
          bool flip=true;
         for(auto &i:mp){
           
            if(flip){
                reverse(i.second.begin(),i.second.end());
            }

            for(int j=0;j<i.second.size();j++)
                res.push_back(i.second[j]);

                flip=!flip;

         }


         return res;

    }
};