#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  typedef long long ll;
  typedef vector<int> poly;
  const int p=998244353;
  namespace internal{
    vector<bool> ip;
    poly primes;
    bool init=false;
    inline int add(int x,int y){
      int s=x+y; if(s>=p)s-=p; return s;
    }
    inline void self_add(int &x,int y){
      if((x+=y)>=p)x-=p;
    }
    inline poly mul(poly a,poly b){
      poly s(a.size());
      for(int i=0;i<a.size();i++)
        s[i]=(ll)a[i]*b[i]%p;
      return s;
    }
    inline void init_primes(int n){
      init=true,ip.resize(n+1,true);
      ip[0]=ip[1]=false;
      for(int i=2;i<=n;i++){
        if(ip[i])primes.emplace_back(i);
        for(int j:primes){
          if(1ll*i*j>n)break;
          ip[i*j]=false;
          if(!(i%j))break;
        }
      }
    }
    inline void clear_primes(){
      vector<bool>().swap(ip),poly().swap(primes);
    }
    inline poly zeta(poly a){
      int n=a.size()-1;
      if(!init||ip.size()<=n)
        clear_primes(),init_primes(n);
      for(int i=2;i<=n;i++)
        if(ip[i])for(int j=1;i*j<=n;j++)
          self_add(a[j*i],a[j]);
      return a;
    }
    inline poly reversed_zeta(poly a){
      int n=a.size()-1;
      if(!init||ip.size()<=n)
        clear_primes(),init_primes(n);
      for(int i=2;i<=n;i++)
        if(ip[i])for(int j=n/i;j;j--)
          self_add(a[j],a[j*i]);
      return a;
    }
    inline poly mobius(poly a){
      int n=a.size()-1;
      if(!init||ip.size()<=n)
        clear_primes(),init_primes(n);
      for(int i=2;i<=n;i++)
        if(ip[i])for(int j=n/i;j;j--)
          self_add(a[j*i],p-a[j]);
      return a;
    }
    inline poly reversed_mobius(poly a){
      int n=a.size()-1;
      if(!init||ip.size()<=n)
        clear_primes(),init_primes(n);
      for(int i=2;i<=n;i++)
        if(ip[i])for(int j=1;i*j<=n;j++)
          self_add(a[j],p-a[j*i]);
      return a;
    }
  }
  void setN(int n){internal::init_primes(n);}
  inline poly gcd_convolution(poly a,poly b){
    return internal::reversed_mobius(internal::mul(internal::reversed_zeta(a),internal::reversed_zeta(b)));
  }
  inline poly lcm_convolution(poly a,poly b){
    return internal::mobius(internal::mul(internal::zeta(a),internal::zeta(b)));
  }
}