#include<bits/stdc++.h>
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
      inline int add_edge(int u,int v){
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
}
