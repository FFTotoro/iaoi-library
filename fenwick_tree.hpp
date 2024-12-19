#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  template<typename T> class fenwick_tree{
    private:
      vector<T> t;
    public:
      fenwick_tree(int n=2e5){
        t.resize(n);
      }
      inline int lowbit(int x){
        return x&-x;
      }
      inline void add(int p,T d){
        t[p++]+=d;
        while((p+=lowbit(p))<=t.size())t[p-1]+=d;
      }
      inline T pre_sum(int p){
        T s=t[p++];
        while((p-=lowbit(p))>0)s+=t[p-1];
        return s;
      }
      inline T sum(int l,int r){
        return pre_sum(r)-(l?pre_sum(l-1):0);
      }
  };
}
