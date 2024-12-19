#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  template<typename T> class dsu{
    private:
      vector<T> a;
      vector<int> s;
    public:
      dsu(int n=2e5){
        a.resize(n),s.resize(n,1);
        iota(a.begin(),a.end(),0);
      }
      T leader(T x){
        return a[x]==x?x:a[x]=leader(a[x]);
      }
      inline int size(T x){
        return s[leader(x)];
      }
      inline void merge(T x,T y){
        x=leader(x),y=leader(y);
        if(x==y)return;
        if(s[x]>s[y])swap(x,y);
        s[y]+=s[x],a[x]=y;
      }
      inline bool same(T x,T y){
        return leader(x)==leader(y);
      }
  };
}
