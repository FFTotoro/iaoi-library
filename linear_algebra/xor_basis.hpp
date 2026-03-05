#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  template<typename T> class xor_basis{
    private:
      int s;
      vector<T> a;
    public:
      xor_basis(int b):s(0),a(b){}
      int size(){return s;}
      bool insert(T x){
        for(int i=a.size()-1;~i;i--)
          if(x>>i&1){
            if(a[i])x^=a[i];
            else{a[i]=x,s++; return true;}
          }
        return false;
      }
      T kth_min(T k){
        if(k>=T(1)<<s)return -1;
        T w=0;
        for(int i=a.size()-1,p=s-1;~i;i--)
          if(a[i]){
            if(k>>p--&1)w=max(w,w^a[i]);
            else w=min(w,w^a[i]);
          }
        return w;
      }
      T kth_max(T k){
        if(k>=T(1)<<s)return -1;
        return kth_min((T(1)<<s)-k-1);
      }
      T xor_min(T x){
        for(int i=a.size()-1;~i;i--)
          x=min(x,x^a[i]);
        return x;
      }
      T xor_max(T x){
        for(int i=a.size()-1;~i;i--)
          x=max(x,x^a[i]);
        return x;
      }
      void merge(const xor_basis<T> &x){
        for(T i:x.a)insert(i);
      }
  };
}
