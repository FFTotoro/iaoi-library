#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  template<typename T,T(*op)(T,T)> class sparse_table{
    private:
      vector<vector<T> > s;
    public:
      sparse_table(vector<T> a){
        int k=__lg(a.size());
        s.resize(a.size(),vector<T>(k+1));
        for(int i=0;i<a.size();i++)
          s[i][0]=a[i];
        for(int i=1;i<=k;i++)
          for(int j=0;j+(1<<i)<=a.size();j++)
            s[j][i]=op(s[j][i-1],s[j+(1<<i-1)][i-1]);
      }
      inline T query(int l,int r){
        int k=__lg(r-l+1);
        return op(s[l][k],s[r-(1<<k)+1][k]);
      }
  };
}
