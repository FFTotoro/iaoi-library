#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  namespace internal{
    inline int pow_mod(int a,int b,int p){
      int r=1;
      while(b){
        if(b&1)r=1ll*r*a%p;
        a=1ll*a*a%p,b>>=1;
      }
      return r;
    }
  }
  inline vector<vector<int> > trans(vector<vector<int> > a){
    vector b(a[0].size(),vector<int>(a.size()));
    for(int i=0;i<a.size();i++)
      for(int j=0;j<a[0].size();j++)
        b[j][i]=a[i][j];
    return b;
  }
  inline int rank(vector<vector<int> > a,const int p){
    auto self_add=[&](int &x,int y){
      if((x+=y)>=p)x-=p;
    };
    if(a.empty()||a[0].empty())return 0;
    if(a.size()>a[0].size())a=trans(a);
    int n=a.size(),m=a[0].size(),r=0;
    for(int c=0;c<m&&r<n;c++){
      int s=-1;
      for(int i=r;i<n;i++)
        if(a[i][c]){s=i; break;}
      if(s<0)continue;
      swap(a[r],a[s]);
      int x=internal::pow_mod(a[r][c],p-2,p);
      for(int i=c;i<m;i++)
        a[r][i]=1ll*a[r][i]*x%p;
      for(int i=0;i<n;i++)
        if(i!=r&&a[i][c]){
          for(int j=c,w=a[i][c];j<m;j++)
            self_add(a[i][j],p-1ll*w*a[r][j]%p);
        }
      r++;
    }
    return r;
  }
  inline int det(vector<vector<int> > a,const int p){
    auto add=[&](int x,int y){
      int s=x+y; if(s>=p)s-=p; return s;
    };
    int n=a.size(),s=1;
    for(int i=0;i<n-1;i++){
      if(!a[i][i])
        for(int j=i+1;j<n;j++)
          if(a[j][i]){swap(a[j],a[i]),s=s?p-s:0; break;}
      if(!a[i][i])return 0;
      for(int j=i+1;j<n;j++)
        if(a[j][i]){
          int d=1ll*a[i][i]*internal::pow_mod(a[j][i],p-2,p)%p;
          s=1ll*s*internal::pow_mod(d,p-2,p)%p;
          for(int k=0;k<n;k++)
            a[j][k]=add(1ll*a[j][k]*d%p,p-a[i][k]);
        }
    }
    for(int i=0;i<n;i++)
      s=1ll*s*a[i][i]%p;
    return s;
  }
  inline int det_arbitrary_mod(vector<vector<int> > a,const int p){
    auto self_add=[&](int &x,int y){
      if((x+=y)>=p)x-=p;
    };
    int s=1;
    for(int i=0;i<a.size();i++)
      for(int j=i+1;j<a.size();j++){
        while(a[i][i]){
          int d=a[j][i]/a[i][i];
          for(int k=i;k<a.size();k++)
            self_add(a[j][k],p-1ll*a[i][k]*d%p);
          swap(a[i],a[j]),s=p-s;
        }
        swap(a[i],a[j]),s=p-s;
      }
    for(int i=0;i<a.size();i++)
      s=1ll*s*a[i][i]%p;
    return s;
  }
  pair<vector<int>,vector<vector<int> > > linear_equations(vector<vector<int> > A,vector<int> b,const int p){
    auto self_add=[&](int &x,int y){
      if((x+=y)>=p)x-=p;
    };
    int n=A.size(),m=A[0].size();
    vector<vector<int> > a(n,vector<int>(m+1));
    for(int i=0;i<n;i++)
      copy(A[i].begin(),A[i].end(),a[i].begin()),a[i][m]=b[i];
    vector<int> mp(m,-1);
    for(int c=0,r=0;c<m&&r<n;c++){
      mp[c]=-1;
      for(int i=r;i<n;i++)
        if(a[i][c]){mp[c]=i; break;}
      if(mp[c]<0)continue;
      swap(a[mp[c]],a[r]),mp[c]=r;
      int x=internal::pow_mod(a[r][c],p-2,p);
      for(int i=c;i<=m;i++)
        a[r][i]=1ll*a[r][i]*x%p;
      for(int i=0;i<n;i++)
        if(i!=r&&a[i][c])
          for(int j=c,w=a[i][c];j<=m;j++)
            self_add(a[i][j],p-1ll*w*a[r][j]%p);
      r++;
    }
    vector<int> c(m,-1);
    for(int i=0;i<m;i++)
      c[i]=~mp[i]?a[mp[i]][m]:0;
    for(int i=0;i<n;i++){
      int s=0;
      for(int j=0;j<m;j++)
        self_add(s,1ll*a[i][j]*c[j]%p);
      if(s!=a[i][m])return make_pair(vector<int>(),vector<vector<int> >());
    }
    vector<vector<int> > bs;
    for(int i=0;i<m;i++)
      if(mp[i]<0){
        vector<int> d(m); d[i]=1;
        for(int j=0;j<m;j++)
          if(~mp[j])d[j]=(p-a[mp[j]][i])%p;
        bs.emplace_back(d);
      }
    return make_pair(c,bs);
  }
}