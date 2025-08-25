#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  cout<<"Number of subtasks: ";
  int n; cin>>n;
  vector<int> a(n),s(n);
  for(int i=0;i<n;i++){
    cout<<"Number of testcases in subtask "<<i<<": ",cin>>a[i];
    cout<<"Score of subtask "<<i<<": ",cin>>s[i];
  }
  cout<<"Time Limit (ms): ";
  int tl; cin>>tl;
  cout<<"Memory Limit (MB): ";
  int ml; cin>>ml;
  freopen("config.yml","w",stdout);
  for(int i=0;i<n;i++){
    for(int j=0;j<a[i];j++){
      cout<<setfill('0')<<setw(2)<<i+1<<'-'<<setfill('0')<<setw(2)<<j+1<<".in: \n";
      cout<<"  timeLimit: "<<tl<<'\n';
      cout<<"  memoryLimit: "<<(ml<<10)<<'\n';
      cout<<"  score: "<<s[i]<<'\n';
      cout<<"  subtaskId: "<<i<<'\n'<<endl;
    }
  }
  return 0;
}