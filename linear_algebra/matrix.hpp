#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  typedef long long ll;
  inline vector<vector<ll> > trans(vector<vector<ll> > a){
    vector b(a[0].size(),vector<ll>(a.size()));
    for(int i=0;i<a.size();i++)
      for(int j=0;j<a[0].size();j++)
        b[j][i]=a[i][j];
    return b;
  }
  inline int rank(vector<vector<ll> > a,const int &p){
    auto pow_mod=[&](ll a,ll b){
      ll r=1;
      while(b){
        if(b&1)(r*=a)%=p;
        (a*=a)%=p,b>>=1;
      }
      return r;
    };
    if(a.empty()||a[0].empty())return 0;
    if(a.size()>a[0].size())a=trans(a);
    int r=0;
    for(int i=0;i<a.size();i++){
      for(int j=i;j<a[0].size();j++)
        if(a[i][j]){
          if(i!=j){
            for(int k=i;k<a.size();k++)
              swap(a[k][i],a[k][j]);
          }
          break;
        }
      if(!a[i][i])continue;
      int x=pow_mod(a[i][i],p-2);
      for(int j=i+1;j<a.size();j++)
        if(a[j][i]){
          int d=a[j][i]*x%p;
          for(int k=i;k<a[0].size();k++)
            (a[j][k]+=p-a[i][k]*d)%=p;
        }
      r++;
    }
    return r;
  }
  inline ll det(vector<vector<ll> > a,const int &p){
    ll s=1;
    for(int i=0;i<a.size();i++)
      for(int j=i+1;j<a.size();j++){
        while(a[i][i]){
          ll d=a[j][i]/a[i][i];
          for(int k=i;k<a.size();k++)
            (a[j][k]+=p-a[i][k]*d%p)%=p;
          swap(a[i],a[j]),s=-s;
        }
        swap(a[i],a[j]),s=-s;
      }
    for(int i=0;i<a.size();i++)
      (s*=a[i][i])%=p;
    return (s+p)%p;
  }
}
