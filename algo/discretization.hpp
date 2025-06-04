#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  vector<int> discretization(vector<int> a){
    auto b=a; sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    for(auto &i:a)i=lower_bound(b.begin(),b.end(),i)-b.begin();
    return a;
  }
}
