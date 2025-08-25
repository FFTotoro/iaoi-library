#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  template<typename C> class mf_graph{
    private:
      typedef pair<int,int> pii;
      int n;
      vector<vector<pii> > g;
      void add(int u,int v,C w){
        g[u].emplace_back(v,e.size());
        e.emplace_back(u,v,w,0);
      }
    public:
      struct edge{
        int u,v; C c,f;
        edge(int u,int v,C c,C f):u(u),v(v),c(c),f(f){}
      };
      vector<edge> e;
      mf_graph(int n):n(n),g(n){}
      void add_edge(int u,int v,C w){
        add(u,v,w),add(v,u,0);
      }
      edge get_edge(int x){return e[x<<1];}
      vector<edge> edges(){
        vector<edge> r;
        for(int i=0;i<e.size();i+=2)
          r.emplace_back(e[i]);
        return r;
      }
      C flow(int s,int t,C l=numeric_limits<C>::max()){
        C r=0;
        vector<int> d(n),p(n);
        auto dfs=[&](auto &&self,int u,C l)->C{
          if(u==t)return l;
          C r=0;
          for(int &i=p[u];i<g[u].size();i++){
            auto [v,x]=g[u][i];
            if(d[v]==d[u]+1&&e[x].c>e[x].f){
              C f=self(self,v,min(l-r,e[x].c-e[x].f));
              if(f){
                e[x].f+=f,e[x^1].f-=f,r+=f;
                if(r==l)return r;
              }
            }
          }
          return d[u]=-1,r;
        };
        while(1){
          fill(d.begin(),d.end(),-1),d[s]=0;
          queue<int> q; q.emplace(s);
          while(!q.empty()){
            int u=q.front(); q.pop();
            for(auto [i,x]:g[u])
              if(d[i]<0&&e[x].c>e[x].f)
                d[i]=d[u]+1,q.emplace(i);
          }
          if(d[t]<0)break;
          fill(p.begin(),p.end(),0);
          C f=dfs(dfs,s,l-r);
          if(!f)break;
          r+=f;
        }
        return r;
      }
  };
}
