// Problem Statement

// Let there be N workers and N jobs. Any worker can be assigned to perform any job, incurring some cost that may vary depending on the work-job assignment. It is required to perform all jobs by assigning exactly one worker to each job and exactly one job to each agent in such a way that the total cost of the assignment is minimized.

// Input Format
// Number of workers and job: N
// Cost matrix C with dimension N*N where C(i,j) is the cost incurred on assigning ith Person to jth Job.

// Sample Input
// 4

// [
// 9 2 7 8
// 6 4 3 7
// 5 8 1 8
// 7 6 9 4
// ]

// Sample Output
// 13

// Constraints
// N <= 20

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> c;
vector<vector<int>> dp;

int solve(int idx,int m,int n){
  if(idx == n) return 0;
  if(dp[idx][m] != -1) return dp[idx][m];

  dp[idx][m] = INT_MAX;


  for(int i = 0; i < n ; i++){
    if((m & (1 << i)) == 0)
      dp[idx][m] = min(dp[idx][m] , c[i][idx] + solve(idx + 1 , (m ^ (1 << i)) , n));    
  }

  return dp[idx][m];
}


int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  int n;
  cin>>n;
  
  c.assign(n,vector<int>(n));
  dp.assign(n,vector<int>((1<<n),-1));

  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      cin>>c[i][j];

  solve(0,0,n);
  cout<<dp[0][0]<<"\n";

}
