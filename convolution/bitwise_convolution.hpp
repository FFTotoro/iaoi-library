namespace IAOI_lib{
  typedef long long ll;
  typedef vector<int> poly;
  const int p=998244353;
  namespace internal{
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
    inline poly and_fwt(int n,poly a,int x){
      auto b=a; self_add(x,p);
      for(int i=0;i<n;i++)
        for(int j=0;j<a.size();j+=1<<i+1)
          for(int k=0;k<1<<i;k++)
            self_add(b[j|k],(ll)b[j|1<<i|k]*x%p);
      return b;
    }
    inline poly or_fwt(int n,poly a,int x){
      auto b=a; self_add(x,p);
      for(int i=0;i<n;i++)
        for(int j=0;j<a.size();j+=1<<i+1)
          for(int k=0;k<1<<i;k++)
            self_add(b[j|1<<i|k],(ll)b[j|k]*x%p);
      return b;
    }
    inline poly xor_fwt(int n,poly a,int x){
      auto b=a; self_add(x,p);
      for(int i=0;i<n;i++)
        for(int j=0;j<a.size();j+=1<<i+1)
          for(int k=0;k<1<<i;k++){
            int u=(ll)add(b[j|k],b[j|1<<i|k])*x%p,
              v=(ll)add(b[j|k],p-b[j|1<<i|k])*x%p;
            b[j|k]=u,b[j|1<<i|k]=v;
          }
      return b;
    }
  }
  inline poly and_convolution(poly a,poly b){
    int n=__lg(a.size());
    return internal::and_fwt(n,internal::mul(internal::and_fwt(n,a,1),internal::and_fwt(n,b,1)),-1);
  }
  inline poly or_convolution(poly a,poly b){
    int n=__lg(a.size());
    return internal::or_fwt(n,internal::mul(internal::or_fwt(n,a,1),internal::or_fwt(n,b,1)),-1);
  }
  inline poly xor_convolution(poly a,poly b){
    int n=__lg(a.size());
    return internal::xor_fwt(n,internal::mul(internal::xor_fwt(n,a,1),internal::xor_fwt(n,b,1)),p+1>>1);
  }
}