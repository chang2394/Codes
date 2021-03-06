/*
    ***  AutoGenerated Header file ***
    * *  Creation Date : 18-08-2015
    * *  Last Modified : Tue Aug 18 23:43:41 2015
    * *  Created By : chang
    * *  Time Complexity : O(V+E)
    * *  Description : Code for finding bridges in a graph (valid[edge_no] = false if edge is a bridge)
    * *  Reference : "http://www.geeksforgeeks.org/bridge-in-a-graph"
    * *  Problem : Codeforces gym-100712 (Problem H: BRIDGES) 
*/

#include <cstdio>
#include <iostream>
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cstring>
#include <bitset>
#include <deque>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include <cmath>

#define  each(v,c)  for(typeof((c).begin()) v = (c).begin(); v != (c).end(); ++v)
#define  sync(x)    ios_base::sync_with_stdio(x)
#define  sz(a)      ((int)(a.size()))
#define  all(a)     (a).begin(), (a).end()
#define  pb         push_back
#define  mp         make_pair
#define  fi         first
#define  se         second
using namespace std;

#define debug(a,n)    cerr << "["; for(int i = 0; i < n; ++i) cerr << a[i] << " ";cerr << "\b]\n";
#define dbg(args...)  {debug1,args; cerr<<endl;}
#define pause()       cin.get();cin.get();

struct debugger {
    template<typename T> debugger& operator , (const T& v) {
        cerr<<v<<" "; return *this;
    }
} debug1;

template <typename T1, typename T2>
inline ostream& operator << (ostream& os, const pair<T1, T2>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template<typename T>
inline ostream &operator << (ostream & os,const vector<T>& v) {
    bool first = true; os << "[";
    for (typename vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii; first = false;
    }
    return os << "]";
}

typedef long long LL;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef vector<int> vi;
const int inf = 0x7fffffff;

const int ND = 112345;
const int ED = 212345;

int head[ND], to[ED], from[ED], nxt[ED];
bool valid[ED], visited[ND]; 

int low[ND], disc[ND];
int eg_no, longest_path,tym, n, m;

int rnk[ND], dsp[ND];
vi childs[ND];

void init(){
    eg_no = longest_path = tym = 0;
    for(int i = 0; i < ND; ++i){
        childs[i].clear();
        head[i] = -1;
        visited[i] = false;
    }
}

void addEdge(int x,int y){
    to[eg_no] = y, nxt[eg_no] = head[x];
    from[eg_no] = x, valid[eg_no] = true;
    head[x] = eg_no++;
}

void dfs(int x,int f){
    disc[x] = low[x] = tym;
    visited[x] = true;
    ++tym;

    for(int i = head[x]; i >= 0; i = nxt[i]){
        int y = to[i];
        if (!visited[y]){
            dfs(y,x);
            low[x] = min(low[x],low[y]);
        } 
        else if (y != f)
            low[x] = min(low[x],disc[y]);
    }
}

int findBridge(){
    int ans = 0;
    for(int i = 0; i < eg_no; i += 2){
        int x = from[i];
        int y = to[i];
        if (disc[y] < disc[x])
            swap(x,y);
        // condition for an edge to be a bridge
        if (low[y] > disc[x]){
            valid[i] = valid[i^1] = false, ++ans;
        }
    }
    return ans;
}

int find(int x){
    if (x != dsp[x])
        dsp[x] = find(dsp[x]);
    return dsp[x];
}

void merge(int x,int y){
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rnk[x] > rnk[y]) 
        dsp[y] = x;
    else 
        dsp[x] = y;
    rnk[y] += (rnk[x] == rnk[y]);
}

int maxDist(int x){
    int res1 = 0;
    int res2 = 0;
    visited[x] = true;
    for(int y : childs[x]){
        for(int i = head[y]; i >= 0; i = nxt[i]){
            int z = find(to[i]);
            if (visited[z] or valid[i]) continue;
            int temp = maxDist(z);
            if (temp > res1)
                res2 = res1, res1 = temp;
            else    
                res2 = max(res2,temp);
        }
    }
    
    longest_path = max(longest_path,res1+res2);
    return (res1 + 1);
}

void solve(){
    init();
    cin >> n >> m;
    
    for(int i = 0; i < m; ++i){
        int x,y;
        cin >> x >> y;
        x -= 1, y -= 1;
        addEdge(x,y);
        addEdge(y,x);
    }
    
    for(int i = 0; i < n; ++i){
        if (!visited[i])
            dfs(i,-1);
    }

    int total_bridges = findBridge();
    for(int i = 0; i < n; ++i)
        rnk[i] = 0, dsp[i] = i;

    for(int i = 0; i < eg_no; i += 2){
        if (valid[i])
            merge(to[i],from[i]);
    }

    for(int i = 0; i < n; ++i){
        int x = find(i);
        childs[x].push_back(i);       
    }

    memset(visited,false,sizeof(visited));
    maxDist(find(0)); 
    cout << total_bridges-longest_path << "\n";  
}

int main()
{
    int t;
    cin >> t;
    while(t--)
        solve();
    return 0;
}
