#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  variant<vector<bool>,bool> twosat(int n,vector<pair<int,int> > e){
    vector<vector<int> > g(n<<1);
    for(auto &[u,v]:e){
      if(u<0)u=n-u; if(v<0)v=n-v;
      g[(u>n?u-n:u+n)-1].emplace_back(v-1);
      g[(v>n?v-n:v+n)-1].emplace_back(u-1);
    }
    int o=0,r=-1;
    vector<int> d(n<<1,-1),l(n<<1),c(n<<1,-1);
    stack<int> s;
    function<void(int)> tarjan=[&](int u){
      d[u]=l[u]=o++,s.emplace(u);
      for(int i:g[u])
        if(d[i]<0)tarjan(i),l[u]=min(l[u],l[i]);
        else if(c[i]<0)l[u]=min(l[u],d[i]);
      if(d[u]==l[u]){
        r++; while(s.top()!=u)
          c[s.top()]=r,s.pop();
        c[u]=r,s.pop();
      }
    };
    for(int i=0;i<n<<1;i++)
      if(d[i]<0)tarjan(i);
    for(int i=0;i<n;i++)
      if(c[i]==c[i+n])return false;
    vector<bool> b(n);
    for(int i=0;i<n;i++)
      b[i]=c[i]<c[i+n];
    return b;
  }
}
