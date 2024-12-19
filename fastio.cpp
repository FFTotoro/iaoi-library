#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  typedef long long ll;
  inline int read(){
    int x=0; char c=getchar(); bool f=false;
    while(!isdigit(c)){
      if(c=='-')f=true;
      c=getchar();
    }
    while(isdigit(c)){
      x=(x<<1)+(x<<3)+(c^48);
      c=getchar();
    }
    return f?-x:x;
  }
  inline void write(int x){
    if(x<0){putchar('-'); write(-x); return;}
    if(x/10)write(x/10);  putchar(x%10+48);
  }
  inline ll readll(){
    ll x=0; char c=getchar(); bool f=false;
    while(!isdigit(c)){
      if(c=='-')f=true;
      c=getchar();
    }
    while(isdigit(c)){
      x=(x<<1)+(x<<3)+(c^48);
      c=getchar();
    }
    return f?-x:x;
  }
  inline void writell(ll x){
    if(x<0){putchar('-'); write(-x); return;}
    if(x/10)writell(x/10);  putchar(x%10+48);
  }
}
