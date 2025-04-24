#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  template<typename T,T(*op)(T,T)> class sparse_table{
    private:
      vector<vector<T> > s;
    public:
      sparse_table(vector<T> a){
        int k=__lg(a.size());
        s.resize(k+1,vector<T>(a.size()));
        for(int i=0;i<a.size();i++)
          s[0][i]=a[i];
        for(int i=1;i<=k;i++)
          for(int j=0;j+(1<<i)<=a.size();j++)
            s[i][j]=op(s[i-1][j],s[i-1][j+(1<<i-1)]);
      }
      inline T query(int l,int r){
        int k=__lg(r-l+1);
        return op(s[k][l],s[k][r-(1<<k)+1]);
      }
  };
}
