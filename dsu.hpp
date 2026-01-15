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
      vector<vector<int> > groups(){
        vector<int> id(a.size(),-1);
        int c=0;
        for(int i=0;i<a.size();i++)
          if(i==leader(i))id[i]=c++;
        vector<vector<int> > v(c);
        for(int i=0;i<a.size();i++)
          v[id[leader(i)]].emplace_back(i);
        return v;
      }
  };
}
