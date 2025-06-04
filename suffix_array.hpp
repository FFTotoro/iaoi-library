#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  namespace internal{
    template<typename T> vector<T> discretization(vector<T> a){
      auto b=a; sort(b.begin(),b.end());
      b.erase(unique(b.begin(),b.end()),b.end());
      for(auto &i:a)i=lower_bound(b.begin(),b.end(),i)-b.begin();
      return a;
    }
    vector<int> sa_doubling(vector<int> s){
      int n=s.size();
      vector<int> sa(n),rk=s;
      iota(sa.begin(),sa.end(),0);
      int v=*max_element(rk.begin(),rk.end())+1;
      for(int k=1;k<n&&v<n;k<<=1){
        auto cmp=[&](int x,int y){
          if(rk[x]!=rk[y])return rk[x]<rk[y];
          int rx=x+k<n?rk[x+k]:-1,ry=y+k<n?rk[y+k]:-1;
          return rx<ry;
        };
        vector<basic_string<int> > v1(v+1),v2(v);
        for(int i=0;i<n;i++)
          v1[i+k<n?rk[i+k]+1:0]+=i;
        for(int i=0;i<=v;i++)
          for(int p:v1[i])v2[rk[p]]+=p;
        for(int i=0,c=0;i<v;i++)
          for(int p:v2[i])sa[c++]=p;
        vector<int> r(n);
        for(int i=1;i<n;i++)
          r[sa[i]]=r[sa[i-1]]+cmp(sa[i-1],sa[i]);
        swap(r,rk),v=rk[sa[n-1]]+1;
      }
      return sa;
    }
  }
  template<typename T> vector<int> suffix_array(vector<T> s){
    s=internal::discretization<T>(s);
    vector<int> s2(s.begin(),s.end());
    return internal::sa_doubling(s2);
  }
  vector<int> suffix_array(string s){
    vector<char> s2(s.begin(),s.end());
    return suffix_array<char>(s2);
  }
  template<typename T> vector<int> lcp_array(vector<T> s,vector<int> sa){
    int n=s.size();
    vector<int> rk(n),lcp(n-1);
    for(int i=0;i<n;i++)
      rk[sa[i]]=i;
    for(int i=0,h=0;i<n-1;i++){
      if(h)h--;
      if(!rk[i])continue;
      int j=sa[rk[i]-1];
      while(i+h<n&&j+h<n&&s[i+h]==s[j+h])h++;
      lcp[rk[i]-1]=h;
    }
    return lcp;
  }
  vector<int> lcp_array(string s,vector<int> sa){
    vector<char> s2(s.begin(),s.end());
    return lcp_array<char>(s2,sa);
  }
}
