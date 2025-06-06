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
        if(i!=r&&a[i][c])
          for(int j=c,w=a[i][c];j<m;j++)
            self_add(a[i][j],p-1ll*w*a[r][j]%p);
      r++;
    }
    return r;
  }
  inline int det(vector<vector<int> > a,const int p){
    auto self_add=[&](int &x,int y){
      if((x+=y)>=p)x-=p;
    };
    int n=a.size(),dt=1;
    for(int c=0;c<n;c++){
      int s=-1;
      for(int i=c;i<n;i++)
        if(a[i][c]){s=i; break;}
      if(s<0)return 0;
      if(c!=s)swap(a[c],a[s]),dt=p-dt;
      int x=internal::pow_mod(a[c][c],p-2,p);
      dt=1ll*dt*a[c][c]%p;
      for(int i=c;i<n;i++)
        a[c][i]=1ll*a[c][i]*x%p;
      for(int i=c+1;i<n;i++)
        if(a[i][c])
          for(int j=c,w=a[i][c];j<n;j++)
            self_add(a[i][j],p-1ll*w*a[c][j]%p);
    }
    return dt;
  }
  inline int det_arbitrary_mod(vector<vector<int> > a,const int p){
    auto self_add=[&](int &x,int y){
      if((x+=y)>=p)x-=p;
    };
    int n=a.size(),s=1;
    for(int i=0;i<n;i++)
      for(int j=i+1;j<n;j++){
        while(a[i][i]){
          int d=a[j][i]/a[i][i];
          for(int k=i;k<n;k++)
            self_add(a[j][k],p-1ll*a[i][k]*d%p);
          swap(a[i],a[j]),s=p-s;
        }
        swap(a[i],a[j]),s=p-s;
      }
    for(int i=0;i<n;i++)
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
  inline int pfaffian(vector<vector<int> > a,const int p){
    auto self_add=[&](int &x,int y){
      if((x+=y)>=p)x-=p;
    };
    int n=a.size(),pf=1;
    for(int c=0;c<n;c+=2){
      int s=-1;
      for(int i=c;i<n;i++)
        if(a[i][c+1]){s=i; break;}
      if(s<0)return 0;
      if(c!=s){
        swap(a[c],a[s]);
        for(int i=0;i<n;i++)
          swap(a[i][c],a[i][s]);
        pf=p-pf;
      }
      int x=internal::pow_mod(a[c][c+1],p-2,p);
      pf=1ll*pf*a[c][c+1]%p;
      for(int i=c+1;i<n;i++)
        a[c][i]=1ll*a[c][i]*x%p,a[i][c]=1ll*a[i][c]*x%p;
      for(int j=c+2;j<n;j++)
        if(a[c+1][j])
          for(int i=c+1,w=a[c+1][j];i<n;i++)
            self_add(a[i][j],1ll*w*a[i][c]%p);
      for(int i=c+2;i<n;i++)
        if(a[i][c+1])
          for(int j=c+1,w=a[i][c+1];j<n;j++)
            self_add(a[i][j],p-1ll*w*a[c][j]%p);
    }
    return pf;
  }
}