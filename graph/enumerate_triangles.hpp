#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  typedef long long ll;
  ll enumerate_triangles(vector<int> x,vector<vector<int> > g){
    int n=g.size(); ll c=0;
    vector<vector<int> > g2(n);
    for(int u=0;u<n;u++)
      for(int v:g[u])
        if(make_pair(g[u].size(),u)>make_pair(g[v].size(),v))
          g2[v].emplace_back(u);
    vector<int> b(n,-1);
    for(int u=0;u<n;u++){
      for(int v:g2[u])b[v]=u;
      for(int v:g2[u])
        for(int i:g2[v])
          if(b[i]==u)c+=1ll*x[u]*x[v]*x[i];
    }
    return c;
  }
  int enumerate_triangles_mod(vector<int> x,vector<vector<int> > g,const int p){
    auto add=[&](int &x,int y){
      if((x+=y)>=p)x-=p;
    };
    int n=g.size(),c=0;
    vector<vector<int> > g2(n);
    for(int u=0;u<n;u++)
      for(int v:g[u])
        if(make_pair(g[u].size(),u)>make_pair(g[v].size(),v))
          g2[v].emplace_back(u);
    vector<int> b(n,-1);
    for(int u=0;u<n;u++){
      for(int v:g2[u])b[v]=u;
      for(int v:g2[u])
        for(int i:g2[v])
          if(b[i]==u)add(c,1ll*x[u]*x[v]%p*x[i]%p);
    }
    return c;
  }
}
