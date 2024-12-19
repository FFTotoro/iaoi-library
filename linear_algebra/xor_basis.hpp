#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  typedef long long ll;
  class linear_basis{
    private:
      vector<ll> a;
    public:
      linear_basis(int b){
        a.resize(b);
      }
      inline void insert(ll x){
        for(int i=a.size()-1;~i;i--)
          if(x>>i&1){
            if(a[i])x^=a[i];
            else{a[i]=x; break;}
          }
      }
      inline ll query(){
        ll c=0;
        for(int i=a.size()-1;~i;i--)
          c=max(c,c^a[i]);
        return c;
      }
      inline void merge(LinearBasis x){
        assert(a.size()==x.a.size());
        for(int i=a.size()-1;~i;i--)
          this->insert(x.a[i]);
      }
  };
}
