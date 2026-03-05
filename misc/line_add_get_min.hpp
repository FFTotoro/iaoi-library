#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
namespace IAOI_lib{
  class line_add_get_min{
    private:
      typedef long long ll;
      typedef pair<int,ll> line;
      typedef tree<line,null_type,greater<>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
      const ll I=LLONG_MAX;
      ordered_set t;
      bool useless(line x,line y,line z){
        return (__int128)(y.second-x.second)*(y.first-z.first)>=(__int128)(z.second-y.second)*(x.first-y.first);
      }
      ll get_val(ordered_set::iterator it,ll x){
        if(it==t.end())return I;
        return (ll)it->first*x+it->second;
      }
    public:
      void add(int k,ll b){
        auto it=t.insert(line(k,b)).first;
        if(it!=t.begin()&&next(it)!=t.end()){
          auto il=prev(it),ir=next(it);
          if(useless(*il,*it,*ir))return (void)t.erase(it);
        }
        while(it!=t.begin()){
          auto il=prev(it);
          if(il==t.begin())break;
          auto ill=prev(il);
          if(useless(*ill,*il,*it))it=t.erase(il);
          else break;
        }
        while(it!=t.end()){
          auto ir=next(it);
          if(ir==t.end())break;
          auto irr=next(ir);
          if(irr==t.end())break;
          if(useless(*it,*ir,*irr))it=prev(t.erase(ir));
          else break;
        }
      }
      ll get_min(ll x){
        if(t.empty())return I;
        auto it=t.node_begin();
        while(it!=t.node_end()){
          ll vl=*it==t.begin()?I:get_val(prev(*it),x),
            vm=get_val(*it,x),vr=get_val(next(*it),x);
          if(vl>vm&&vm>vr)it=it.get_r_child();
          else if(vl<vm&&vm<vr)it=it.get_l_child();
          else break;
        }
        return get_val(*it,x);
      }
  };
}
