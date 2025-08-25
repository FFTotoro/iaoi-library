#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  class general_matching{
    private:
      int n,c;
      vector<vector<int> > g;
      vector<int> o,p,pr,w,f;
      int leader(int x){
        return x==f[x]?x:f[x]=leader(f[x]);
      }
      int lca(int u,int v){
        c++,u=leader(u),v=leader(v);
        while(o[u]!=c){
          o[u]=c,u=leader(pr[p[u]]);
          if(v<n)swap(u,v);
        }
        return u;
      }
      void augment(int u){
        if(u<n)augment(p[pr[u]]),p[p[u]=pr[u]]=u;
      }
      bool blossom(int u){
        fill(pr.begin(),pr.end(),n);
        fill(w.begin(),w.end(),n);
        iota(f.begin(),f.end(),0);
        queue<int> q; q.emplace(u),w[u]=1;
        auto shrink=[&](int u,int v,int a){
          while(leader(u)!=a){
            pr[u]=v,v=p[u],f[u]=f[v]=a,u=pr[v];
            if(!w[v])w[v]=1,q.emplace(v);
          }
        };
        while(!q.empty()){
          int u=q.front(); q.pop();
          for(int i:g[u]){
            if(leader(u)==leader(i))continue;
            if(w[i]==1){
              int a=lca(u,i);
              shrink(u,i,a),shrink(i,u,a);
            }
            if(w[i]==n){
              pr[i]=u,w[i]=0;
              if(p[i]<n)w[p[i]]=1,q.emplace(p[i]);
              else{augment(i); return true;}
            }
          }
        }
        return false;
      }
    public:
      general_matching(int n_){
        c=0,g.resize(n=n_),p.resize(n+1,n);
        pr.resize(n+1),w.resize(n+1);
        o.resize(n+1),f.resize(n+1);
      }
      void add_edge(int u,int v){
        g[u].emplace_back(v);
        g[v].emplace_back(u);
      }
      pair<int,vector<pii> > solve(){
        int s=0; vector<pii> v;
        for(int i=0;i<n;i++)
          if(p[i]==n)s+=blossom(i);
        for(int i=0;i<n;i++)
          if(p[i]<i)v.emplace_back(p[i],i);
        return make_pair(s,v);
      }
  };
}
