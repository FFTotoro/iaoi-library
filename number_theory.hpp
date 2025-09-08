#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
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
  inline ll safe_mul(ll a,ll b,ll M){
    ll r=0;
    while(b){
      if(b&1)(r+=a)%=M;
      (a<<=1)%=M,b>>=1;
    }
    return r;
  }
  inline int pow_mod(int a,ll b,int M){
    int r=1;
    while(b){
      if(b&1)r=1ll*r%M*a%M;
      a=1ll*a%M*a%M,b>>=1;
    }
    return r;
  }
  inline ll pow_modll(ll a,ll b,ll M){
    ll r=1;
    while(b){
      if(b&1)r=(__int128)r%M*a%M;
      a=(__int128)a%M*a%M,b>>=1;
    }
    return r;
  }
  int inv_p(int x,int M){
    return pow_mod(x,M-2,M);
  }
  ll inv_pll(ll x,ll M){
    return pow_modll(x,M-2,M);
  }
  pair<int,int> exgcd(int a,int b){
    if(!b)return make_pair(1,0);
    auto [x,y]=exgcd(b,a%b);
    return make_pair(y,x-a/b*y);
  }
  pair<ll,ll> exgcdll(ll a,ll b){
    if(!b)return make_pair(1,0);
    auto [x,y]=exgcdll(b,a%b);
    return make_pair(y,x-a/b*y);
  }
  int inv_cp(int x,int M){
    return gcd(x,M)>1?-1:(exgcd(x,M).st%M+M)%M;
  }
  ll inv_cpll(ll x,ll M){
    return gcd(x,M)>1?-1:(exgcdll(x,M).st%M+M)%M;
  }
  ll crt(vector<pair<ll,ll> > a){
    ll p=1,s=0;
    for(auto [r,m]:a)p*=m;
    for(auto [r,m]:a){
      ll m2=p/m,i=inv_cpll(m2,m);
      s+=r*m2*i;
    }
    return s;
  }
  ll excrt(vector<pair<ll,ll> > e){
    auto [q,p]=e[0];
    for(int i=1;i<e.size();i++){
      auto [b,a]=e[i];
      auto [x,y]=exgcdll(p,a);
      ll d=gcd(p,a),c=b-q;
      if(c%d)return -1;
      if((x=(__int128)x*c/d%(a/d))<0)x+=a/d;
      ll m=lcm(p,a);
      if(q=(p*x+q)%m;q<0)q+=m;
      p=m;
    }
    return q%p;
  }
  long double lagrange(vector<pair<ll,ll> > a,ll k){
    long double c=0;
    for(int i=0;i<a.size();i++){
      long double s1=a[i].nd;
      for(int j=0;j<a.size();j++)
        if(i!=j)s1*=1.0*(k-a[j].st)/(a[i].st-a[j].st);
      c+=s1;
    }
    return c;
  }
  int lagrange_mod(vector<pair<int,int> > a,int k,int M){
    int c=0;
    for(int i=0;i<a.size();i++){
      int s1=a[i].nd,s2=1;
      for(int j=0;j<a.size();j++)
        if(i!=j)s1=1ll*s1*(k-a[j].st+M)%M,
          s2=1ll*s2*(a[i].st-a[j].st+M)%M;
      (c+=1ll*s1*inv_cpll(s2,M)%M)%=M;
    }
    return c;
  }
  int discrete_logarithm(int x,int y,int M){
    int b=sqrt(M),l=M/b+!!(M%b),r=M;
    vector<int> B(b+1),G(l+1);
    for(int i=B[0]=1;i<=b;i++)
      B[i]=1ll*B[i-1]*x%M;
    __gnu_pbds::gp_hash_table<int,pair<int,int> > t;
    for(int i=G[0]=1;i<=l;i++){
      G[i]=1ll*G[i-1]*B[b]%M;
      if(t.find(G[i])==t.end())t[G[i]].first=i;
      else if(!t[G[i]].second)t[G[i]].second=i;
    }
    auto check=[&](int k){return 1ll*G[k/b]*B[k%b]%M==y;};
    for(int i=0;i<=b;i++)
      if(int w=1ll*y*B[i]%M;t.find(w)!=t.end()){
        auto [r1,r2]=t[w];
        if(check(r1*b-i))r=min(r,r1*b-i);
        if(r2&&check(r2*b-i))r=min(r,r2*b-i);
      }
    return r==M?-1:r;
  }
#undef st
#undef nd
}