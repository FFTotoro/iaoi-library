#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  template<typename S,S(*op)(S,S),S(*e)()> class segtree{
    private:
      typedef pair<int,int> pii;
      vector<pii> B;
      vector<S> R;
      inline void pushup(int u){
        R[u]=op(R[u<<1],R[u<<1|1]);
      }
    public:
      segtree(int n){
        B.resize(n<<2),R.resize(n<<2);
        function<void(int,int,int)> build=[&](int u,int l,int r){
          if(B[u]=make_pair(l,r);l==r){R[u]=e(); return;}
          int m=l+r>>1;
          build(u<<1,l,m),build(u<<1|1,m+1,r);
          pushup(u);
        };
        build(1,0,n-1);
      }
      segtree(vector<S> a){
        B.resize(a.size()<<2),R.resize(a.size()<<2);
        function<void(int,int,int)> build=[&](int u,int l,int r){
          if(B[u]=make_pair(l,r);l==r){R[u]=a[l]; return;}
          int m=l+r>>1;
          build(u<<1,l,m),build(u<<1|1,m+1,r);
          pushup(u);
        };
        build(1,0,a.size()-1);
      }
      inline void set(int p,S x,int u=1){
        if(B[u].first==B[u].second){R[u]=x; return;}
        int m=B[u].first+B[u].second>>1;
        set(p,x,u<<1|(p>m)),pushup(u);
      }
      inline S get(int p,int u=1){
        if(B[u].first==B[u].second)return R[u];
        int m=B[u].first+B[u].second>>1;
        return get(p,u<<1|(p>m));
      }
      inline S prod(int l,int r,int u=1){
        if(B[u].first>r||B[u].second<l)return e();
        if(l<=B[u].first&&B[u].second<=r)return R[u];
        return op(prod(l,r,u<<1),prod(l,r,u<<1|1));
      }
      inline S all_prod(){return R[1];}
  };
}
