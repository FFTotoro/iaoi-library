#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  template<typename T> inline T read(){
    T x=0; char c=getchar();
    bool f=false;
    while(!isdigit(c)){
      if(c=='-')f=true;
      c=getchar();
    }
    while(isdigit(c))x=x*10+c-48,c=getchar();
    return f?-x:x;
  }
  template<typename T> inline void write(T x){
    if(x<0){putchar('-'),write(-x); return;}
    if(x/10)write(x/10);
    putchar(x%10+48);
  }
}
