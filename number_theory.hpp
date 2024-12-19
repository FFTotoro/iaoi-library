#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  typedef long long ll;
#define st first
#define nd second
  vector<int> get_primes(int n){
    vector<bool> b(n+1);
    vector<int> p;
    for(int i=2;i<=n;i++){
      if(!b[i])p.emplace_back(i);
      for(int j:p){
        if(1ll*i*j>n)break;
        b[i*j]=true;
        if(!(i%j))break;
      }
    }
    return p;
  }
  inline ll safe_mulll(ll a,ll b,ll mod){
    ll r=0;
    while(b){
      if(b&1)(r+=a)%=mod;
      (a<<=1)%=mod; b>>=1;
    }
    return r;
  }
  inline int pow_mod(int a,int b,int mod){
    int r=1;
    while(b){
      if(b&1)r=r%mod*a%mod;
      a=a%mod*a%mod; b>>=1;
    }
    return r;
  }
  inline ll pow_modll(ll a,ll b,ll mod){
    ll r=1;
    while(b){
      if(b&1)r=r%mod*a%mod;
      a=a%mod*a%mod; b>>=1;
    }
    return r;
  }
  inline int inv_p(int x,int mod){
    return pow_mod(x,mod-2,mod);
  }
  inline ll inv_pll(ll x,ll mod){
    return pow_modll(x,mod-2,mod);
  }
  pair<int,int> exgcd(int a,int b){
    if(!b)return make_pair(1,0);
    auto [x,y]=exgcd(b,a%b);
    int t=x; x=y; y=t-a/b*y;
    return make_pair(x,y);
  }
  pair<ll,ll> exgcdll(ll a,ll b){
    if(!b)return make_pair(1,0);
    auto [x,y]=exgcdll(b,a%b);
    ll t=x; x=y; y=t-a/b*y;
    return make_pair(x,y);
  }
  inline int inv_cp(int x,int mod){
    if(gcd(x,mod)>1)return -1;
    return (exgcd(x,mod).st%mod+mod)%mod;
  }
  inline ll inv_cpll(ll x,ll mod){
    if(gcd(x,mod)>1)return -1;
    return (exgcdll(x,mod).st%mod+mod)%mod;
  }
  inline ll crt(vector<pair<ll,ll> > a){
    ll p=1,s=0;
    for(auto [r,m]:a)p*=m;
    for(auto [r,m]:a){
      ll m2=p/m,i=inv_cpll(m2,m);
      s+=r*m2*i;
    }
    return s;
  }
  inline ll crt_mod(vector<pair<ll,ll> > a,ll mod){
    ll p=1,s=0;
    for(auto [r,m]:a)p*=m;
    for(auto [r,m]:a){
      ll m2=p/m,i=inv_cpll(m2,m);
      (s+=r*m2%mod*i%mod)%=mod;
    }
    return s;
  }
  inline double lagrange(vector<pair<int,int> > a,int k){
    double c=0;
    for(int i=0;i<a.size();i++){
      double s1=a[i].nd;
      for(int j=0;j<a.size();j++)
        if(i!=j)s1*=1.0*(k-a[j].st)/(a[i].st-a[j].st);
      c+=s1;
    }
    return c;
  }
  inline long double lagrange(vector<pair<ll,ll> > a,ll k){
    long double c=0;
    for(int i=0;i<a.size();i++){
      long double s1=a[i].nd;
      for(int j=0;j<a.size();j++)
        if(i!=j)s1*=1.0*(k-a[j].st)/(a[i].st-a[j].st);
      c+=s1;
    }
    return c;
  }
  inline int lagrange_mod(vector<pair<int,int> > a,int k,int mod){
    int c=0;
    for(int i=0;i<a.size();i++){
      int s1=a[i].nd%mod,s2=1;
      for(int j=0;j<a.size();j++)
        if(i!=j)s1=s1*(k-a[j].st)%mod,
          s2=s2*(a[i].st-a[j].st)%mod;
      (c+=s1*inv_cp((s2%mod+mod)%mod,mod)%mod+mod)%=mod;
    }
    return c;
  }
  inline ll lagrange_modll(vector<pair<ll,ll> > a,ll k,ll mod){
    ll c=0;
    for(int i=0;i<a.size();i++){
      ll s1=a[i].nd%mod,s2=1;
      for(int j=0;j<a.size();j++)
        if(i!=j)s1=s1*(k-a[j].st)%mod,
          s2=s2*(a[i].st-a[j].st)%mod;
      (c+=s1*inv_cpll((s2%mod+mod)%mod,mod)%mod+mod)%=mod;
    }
    return c;
  }
#undef st
#undef nd
}
