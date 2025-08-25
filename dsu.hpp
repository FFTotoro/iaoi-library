#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  class dsu{
    private:
      vector<int> a,s;
    public:
      dsu(int n):a(n),s(n,1){
        iota(a.begin(),a.end(),0);
      }
      int leader(int x){
        return a[x]==x?x:a[x]=leader(a[x]);
      }
      int size(int x){
        return s[leader(x)];
      }
      void merge(int x,int y){
        x=leader(x),y=leader(y);
        if(x==y)return;
        if(s[x]>s[y])swap(x,y);
        s[y]+=s[x],a[x]=y;
      }
      bool same(int x,int y){
        return leader(x)==leader(y);
      }
  };
}
