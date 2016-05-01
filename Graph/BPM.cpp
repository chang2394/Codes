#define LOCAL
#ifdef LOCAL
#   define TRACE
#else
#   define NDEBUG
#endif

#include <cstdio>
#include <sstream>
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

using namespace std;

/* aliases */
using vi  = vector<int>;
using pi  = pair<int, int>;
using vs  = vector<string>;
using vpi = vector<pi>;
using ll  = long long int;

/* shortcut macros */
#define mp              make_pair
#define fi              first
#define se              second
#define mt              make_tuple
#define gt(t, i)        get<i>(t)
#define all(x)          (x).begin(), (x).end()
#define ini(a, v)       memset(a, v, sizeof(a))
#define re(i, s, n)     for(auto i = s, _##i = (n); i < _##i; ++i)
#define rep(i, s, n)    re(i, s, (n) + 1)
#define fo(i, n)        re(i, 0, n)
#define si(x)           (int)(x.size())
#define pu              push_back
#define is1(mask,i)     ((mask >> i) & 1)

/* trace macro */
#ifdef TRACE
#   define trace(v...)  {cerr << __func__ << ":" << __LINE__ << ": " ;_dt(#v, v);}
#else
#   define trace(...)
#endif

#ifdef TRACE
pi _gp(string s) {
    pi r(0, si(s) - 1);
    int p = 0, s1 = 0, s2 = 0, start = 1;
    fo(i, si(s)) {
        int x = (s1 | s2);
        if(s[i] == ' ' && start) {
            ++r.fi;
        } else {
            start = 0;
            if(s[i] == ',' && !p && !x) {
                r.se = i - 1;
                return r;
            }
            if(x && s[i] == '\\') ++i;
            else if(!x && s[i] == '(') ++p;
            else if(!x && s[i] == ')') --p;
            else if(!s2 && s[i] == '\'') s1 ^= 1;
            else if(!s1 && s[i] == '"') s2 ^= 1;
        }
    }
    return r;
}

template<typename H> void _dt(string u, H&& v) {
    pi p = _gp(u);
    cerr << u.substr(p.fi, p.se - p.fi + 1) << " = " << forward<H>(v) << " |" << endl;
}

template<typename H, typename ...T> void _dt(string u, H&& v, T&&... r) {
    pi p = _gp(u);
    cerr << u.substr(p.fi, p.se - p.fi + 1) << " = " << forward<H>(v) << " | ";
    _dt(u.substr(p.se + 2), forward<T>(r)...);
}

template<typename T> 
ostream &operator <<(ostream &o, vector<T> v) { // print a vector
    o << "{";
    fo(i, si(v) - 1) o << v[i] << ", ";
    if(si(v)) o << v.back();
    o << "}";
    return o;
}

template<typename T1, typename T2> 
ostream &operator <<(ostream &o, map<T1, T2> m) { // print a map
    o << "[";
    for(auto &p: m) {
        o << " (" << p.fi << " -> " << p.se << ")";
    }
    o << " ]";
    return o;
}

template <size_t n, typename... T>
typename enable_if<(n >= sizeof...(T))>::type
    print_tuple(ostream&, const tuple<T...>&) {} 

template <size_t n, typename... T>
typename enable_if<(n < sizeof...(T))>::type
    print_tuple(ostream& os, const tuple<T...>& tup) {
    if (n != 0)
        os << ", ";
    os << get<n>(tup);
    print_tuple<n+1>(os, tup);
}

template <typename... T>
ostream& operator<<(ostream& os, const tuple<T...>& tup) { // print a tuple
    os << "(";
    print_tuple<0>(os, tup);
    return os << ")";
}

template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { // print a pair
    return os << "(" << p.fi << ", " << p.se << ")";
}
#endif
    
/* util functions */

template<typename T>
string tostr(T x) {
    ostringstream oss;
    oss << x;
    return oss.str();
}

template<typename T1, typename T2, typename T3>
T1 modpow(T1 a, T2 p, T3 mod) {
    T1 ret = 1;

    a %= mod;
    for(; p > 0; p /= 2) {
        if(p & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
    }

    return ret;
}

#define x1 _asdfzx1
#define y1 _ysfdzy1

int dx[] {-1, 0, 1, 0, 1, 1, -1, -1};
int dy[] {0, -1, 0, 1, 1, -1, 1, -1};

/* constants */
constexpr auto PI  = 3.14159265358979323846L;
constexpr auto oo  = numeric_limits<int>::max() / 2 - 10;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/**
    left side - n
    right side - m
**/

/* code */
const int ND = 2123;
const int MD = 2123;

int head[ND], to[MD], nxt[MD];
int matchL[ND], matchR[MD];
bool seen[MD];
int n,m,nEdges = 0;

inline void init(){
    nEdges = 0;
    memset(head,-1,sizeof(head));
    memset(matchL,-1,sizeof(matchL));
    memset(matchR,-1,sizeof(matchR));
}

inline void addEdge(int x,int y){
    to[nEdges] = y, nxt[nEdges] = head[x];
    head[x] = nEdges++;
}

bool path(int x){
    for(int i = head[x]; i >= 0; i = nxt[i]){
        int y = to[i];
        if (seen[y]) continue;
        seen[y] = true;

        if (matchR[y] < 0 or path(matchR[y])){
            matchR[y] = x;
            matchL[x] = y;
            return true;
        }
    }
    return false;
}

int bpm(){
    int ans = 0;
    for(int i = 0; i < n; ++i){
        memset(seen,false,sizeof(seen));
        if (path(i)) ++ans;
    }
    return ans;
}

string ls[ND], rs[ND];
int solve() {
    int len;
    cin >> len;
    init();

    map<string,int> lmap, rmap;
    map<string,int> :: iterator it;

    for(int i = 0; i < len; ++i){
        cin >> ls[i] >> rs[i];
        lmap[ls[i]]++;
        rmap[rs[i]]++;
    }

    n = 0;
    for(it = lmap.begin(); it != lmap.end(); ++it){
        it->se = n;
        ++n;
    }

    m = 0;
    for(it = rmap.begin(); it != rmap.end(); ++it){
        it->se = m;
        ++m;
    }

    for(int i = 0; i < len; ++i){
        trace(lmap[ls[i]],rmap[rs[i]])
        addEdge(lmap[ls[i]],rmap[rs[i]]);
    }

    int res = bpm();
    trace(res,n,m);
    int ans = len-(n+m-res);
    return ans;
}

int main() {
    int tc;
    cin >> tc;
    for(int i = 1; i <= tc; ++i)
        cout << "Case #" << i << ": " << solve() << "\n";
    return 0;
}
