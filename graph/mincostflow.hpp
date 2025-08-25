#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  template<typename Cap,typename Cost> class mcf_graph{
    private:
      typedef tuple<int,Cost,int> tpi;
      typedef pair<Cost,int> pci;
      int n;
      vector<vector<tpi> > g;
      void add(int u,int v,Cap cap,Cost cost){
        g[u].emplace_back(v,cost,e.size());
        e.emplace_back(u,v,cap,0);
      }
    public:
      struct edge{
        int u,v; Cap c,f;
        edge(int u,int v,Cap c,Cap f):u(u),v(v),c(c),f(f){}
      };
      vector<edge> e;
      mcf_graph(int n):n(n),g(n){}
      void add_edge(int u,int v,Cap cap,Cost cost){
        add(u,v,cap,cost),add(v,u,0,-cost);
      }
      edge get_edge(int x){return e[x<<1];}
      vector<edge> edges(){
        vector<edge> r;
        for(int i=0;i<e.size();i+=2)
          r.emplace_back(e[i]);
        return r;
      }
      pair<Cap,Cost> flow(int s,int t,Cap l=numeric_limits<Cap>::max()){
        Cap r=0; Cost c=0;
        vector<int> p(n);
        vector<Cost> d(n);
        Cost lcost=numeric_limits<Cost>::max();
        vector<bool> b(n);
        auto dfs=[&](auto &&self,int u,Cap l)->Cap{
          if(u==t)return l;
          b[u]=true;
          Cap r=0;
          for(int &i=p[u];i<g[u].size();i++){
            auto [v,w,x]=g[u][i];
            if(!b[v]&&d[v]==d[u]+w&&e[x].c>e[x].f){
              Cap f=self(self,v,min(l-r,e[x].c-e[x].f));
              if(f){
                c+=f*w,e[x].f+=f,e[x^1].f-=f,r+=f;
                if(r==l)return b[u]=false,r;
              }
            }
          }
          return b[u]=false,r;
        };
        while(1){
          fill(d.begin(),d.end(),lcost),d[s]=0;
          vector<bool> inq(n);
          queue<int> q; inq[s]=true,q.emplace(s);
          while(!q.empty()){
            int u=q.front(); inq[u]=false,q.pop();
            for(auto [i,w,x]:g[u])
              if(d[i]>d[u]+w&&e[x].c>e[x].f)
                if(d[i]=d[u]+w;!inq[i])inq[i]=true,q.emplace(i);
          }
          if(d[t]==lcost)break;
          fill(p.begin(),p.end(),0);
          Cap f=dfs(dfs,s,l-r);
          if(!f)break;
          r+=f;
        }
        return make_pair(r,c);
      }
  };
}
