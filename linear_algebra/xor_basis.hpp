#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  class linear_basis{
    typedef long long ll;
    private:
      vector<ll> a;
    public:
      linear_basis(int b){
        a.resize(b);
      }
      void insert(ll x){
        for(int i=a.size()-1;~i;i--)
          if(x>>i&1){
            if(a[i])x^=a[i];
            else{a[i]=x; break;}
          }
      }
      ll query(){
        ll c=0;
        for(int i=a.size()-1;~i;i--)
          c=max(c,c^a[i]);
        return c;
      }
      void merge(linear_basis x){
        for(int i=a.size()-1;~i;i--)
          this->insert(x.a[i]);
      }
  };
}
