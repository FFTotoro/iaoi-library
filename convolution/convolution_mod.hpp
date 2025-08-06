namespace IAOI_lib{
  typedef long long ll;
  typedef vector<int> poly;
  const int g=3,ng=332748118,p=998244353;
  namespace internal{
    inline int add(int x,int y){
      int s=x+y; if(s>=p)s-=p; return s;
    }
    inline void self_add(int &x,int y){
      if((x+=y)>=p)x-=p;
    }
    inline int qpow(int a,int b){
      int r=1;
      while(b){
        if(b&1)r=1ll*r*a%p;
        a=1ll*a*a%p,b>>=1;
      }
      return r;
    }
    inline void ntt(poly &a,int l,int op){
      poly r(l);
      for(int i=1;i<l;i++)
        r[i]=(r[i>>1]>>1)|(i&1?l>>1:0);
      for(int i=0;i<l;i++)
        if(i<r[i])swap(a[i],a[r[i]]);
      for(int i=2;i<=l;i<<=1){
        int k=qpow(op>0?g:ng,(p-1)/i);
        vector<int> q(i>>1);
        for(int j=q[0]=1;j<i>>1;j++)
          q[j]=(ll)q[j-1]*k%p;
        for(int j=0;j<l;j+=i)
          for(int k=j;k<j+(i>>1);k++){
            int x=a[k],y=(ll)q[k-j]*a[k+(i>>1)]%p;
            self_add(a[k],y),a[k+(i>>1)]=add(x,p-y);
          }
      }
      if(op<0){
        int I=internal::qpow(l,p-2);
        for(int i=0;i<l;i++)
          a[i]=(ll)a[i]*I%p;
      }
    }
  }
  inline poly convolution(poly x,poly y){
    int l=1,n=x.size()+y.size();
    while(l<n<<1)l<<=1;
    while(x.size()<l)x.emplace_back(0);
    while(y.size()<l)y.emplace_back(0);
    internal::ntt(x,l,1),internal::ntt(y,l,1);
    for(int i=0;i<l;i++)
      x[i]=(ll)x[i]*y[i]%p;
    internal::ntt(x,l,-1);
    return poly(x.begin(),x.begin()+n-1);
  }
  inline poly operator *(const poly &x,const poly &y){
    return convolution(x,y);
  }
  inline poly operator *=(poly &x,const poly &y){
    return x=convolution(x,y);
  }
  inline poly pow(poly x,ll k){
    int n=x.size(),l=1;
    while(l<n<<1)l<<=1;
    while(x.size()<l)x.emplace_back(0);
    vector<int> r(l); r[0]=1;
    internal::ntt(r,l,1),internal::ntt(x,l,1);
    while(k){
      if(k&1){
        for(int i=0;i<l;i++)
          r[i]=(ll)r[i]*x[i]%p;
        internal::ntt(r,l,-1);
        fill(r.begin()+n,r.begin()+l,0);
        internal::ntt(r,l,1);
      }
      for(int i=0;i<l;i++)
        x[i]=(ll)x[i]*x[i]%p;
      internal::ntt(x,l,-1);
      fill(x.begin()+n,x.begin()+l,0);
      internal::ntt(x,l,1),k>>=1;
    }
    internal::ntt(r,l,-1);
    return poly(r.begin(),r.begin()+n);
  }
}