#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
#define int long long
  class atlantis{
    typedef pair<int,int> pii;
    typedef tuple<int,int,int,int> tpi;
    private:
      struct line{
        int l,r,h,s;
        bool operator <(const line &x)const{
          return h<x.h;
        }
      };
      int n;
      vector<line> L;
      vector<pii> B;
      vector<int> X,C,S;
      void build(int u,int l,int r){
        if(B[u]=make_pair(l,r);l==r)return;
        int m=l+r>>1;
        build(u<<1,l,m),build(u<<1|1,m+1,r);
        pushup(u);
      }
      inline void pushup(int u){
        if(C[u])S[u]=X[B[u].second+1]-X[B[u].first];
        else S[u]=S[u<<1]+S[u<<1|1];
      }
      void update(int u,int l,int r,int c){
        if(X[B[u].second+1]<=l||r<=X[B[u].first])return;
        if(l<=X[B[u].first]&&X[B[u].second+1]<=r)C[u]+=c;
        else update(u<<1,l,r,c),update(u<<1|1,l,r,c);
        pushup(u);
      }
      int all_prod(){return S[1];}
    public:
      int areas_union(vector<tpi> a){
        X.resize(a.size()<<1),L.resize(a.size()<<1);
        for(int i=0;i<a.size();i++){
          auto &[xa,ya,xb,yb]=a[i];
          if(xa>xb)swap(xa,xb); if(ya>yb)swap(ya,yb);
          X[i<<1]=xa,X[i<<1|1]=xb;
          L[i<<1]=(line){xa,xb,ya,1},L[i<<1|1]=(line){xa,xb,yb,-1};
        }
        sort(L.begin(),L.end(),[](line x,line y){return x.h<y.h;});
        sort(X.begin(),X.end()),n=unique(X.begin(),X.end())-X.begin();
        B.resize(n<<2),C.resize(n<<2),S.resize(n<<3),build(1,0,n-2);
        int c=0;
        for(int i=0;i+1<a.size()<<1;i++){
          update(1,L[i].l,L[i].r,L[i].s);
          c+=all_prod()*(L[i+1].h-L[i].h);
        }
        return c;
      }
  };
#undef int
}
