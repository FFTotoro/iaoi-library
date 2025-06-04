#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  typedef long long ll;
  const double PI=acos(-1);
  namespace internal{
    vector<int> t;
    inline void init(int n){
      int d=n>>1; t.clear();
      t.emplace_back(0),t.emplace_back(d);
      for(int w=2;w<=n;w<<=1){
        d>>=1;
        for(int p=0;p<w;p++) 
          t.emplace_back(t[p]|d);
      }
    }
    inline void fft(vector<complex<double> > &a,int n){
      for(int i=1;i<n;i++)
        if(t[i]>i)swap(a[i],a[t[i]]);
      for(int i=2;i<=n;i<<=1){
        complex<double> b(cos(PI/(i>>1)),sin(PI/(i>>1))),w(1,0);
        for(int l=0,r=i-1;r<=n;l+=i,r+=i){
          auto s=w;
          for(int p=l;p<l+(i>>1);p++){
            auto x=a[p]+s*a[p+(i>>1)],y=a[p]-s*a[p+(i>>1)];
            a[p]=x,a[p+(i>>1)]=y,s*=b;
          }
        }
      }
    }
  }
  inline vector<ll> convolution_ll(vector<int> x,vector<int> y){
    int l=1,n=x.size()+y.size();
    while(l<n<<1)l<<=1;
    while(x.size()<l)x.emplace_back(0);
    while(y.size()<l)y.emplace_back(0);
    internal::init(l);
    vector<complex<double> > a(x.begin(),x.end()),b(y.begin(),y.end()),c(l);
    internal::fft(a,l),internal::fft(b,l);
    for(int i=0;i<l;i++)
      c[i]=a[i]*b[i];
    internal::fft(c,l);
    reverse(c.begin()+1,c.end());
    vector<ll> s(n-1);
    for(int i=0;i<n-1;i++)
      s[i]=llround(c[i].real()/l);
    return s;
  }
}
