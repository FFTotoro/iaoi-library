#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace std;
namespace IAOI_lib{
  class bipar_edge_coloring{
    private:
      vector<int> d;
      vector<vector<int> > a;
    public:
      bipar_edge_coloring(int n,int m){
        d.resize(n+m);
        a.resize(n+m,vector<int>(n+m,-1));
      }
      int add_edge(int u,int v){
        d[u]++,d[v]++;
        int c1=0,c2=0;
        while(~a[u][c1])c1++;
        while(~a[v][c2])c2++;
        a[u][c1]=v,a[v][c2]=u;
        if(c1!=c2)
          for(int c3=c2,i=v;~i;i=a[i][c3],c3^=c1^c2)
            swap(a[i][c1],a[i][c2]);
        return c1;
      }
      pair<int,vector<vector<int> > > color(){
        return make_pair(*max_element(d.begin(),d.end()),a);
      }
  };
  class associative_bipar_edge_coloring{
    private:
      vector<int> d;
      vector<__gnu_pbds::gp_hash_table<int,int> > a;
    public:
      associative_bipar_edge_coloring(int n,int m):d(n+m),a(n+m){}
      int add_edge(int u,int v){
        d[u]++,d[v]++;
        int c1=0,c2=0;
        while(a[u].find(c1)!=a[u].end())c1++;
        while(a[v].find(c2)!=a[v].end())c2++;
        if(a[u][c1]=v,a[v][c2]=u;c1!=c2)
          for(int c3=c2,i=v;~i;i=a[i].find(c3)!=a[i].end()?a[i][c3]:-1,c3^=c1^c2){
            bool f1=a[i].find(c1)==a[i].end(),f2=a[i].find(c2)==a[i].end();
            if(f1)a[i][c1]=a[i][c2],a[i].erase(c2);
            else if(f2)a[i][c2]=a[i][c1],a[i].erase(c1);
            else swap(a[i][c1],a[i][c2]);
          }
        return c1;
      }
      pair<int,vector<__gnu_pbds::gp_hash_table<int,int> > > color(){
        return make_pair(*max_element(d.begin(),d.end()),a);
      }
  };
}
