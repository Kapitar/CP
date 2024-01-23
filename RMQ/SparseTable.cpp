//#pragma GCC optimize("Ofast, unroll-loops")

#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <queue>
#include <cmath>
#include <algorithm>
#include <map>
#include <stack>
#include <cassert>
#include <unordered_map>
#include <bitset>
#include <random>
#include <unordered_set>
#include <chrono>

using namespace std;

# define int long long
# define m2(v) (v << 1)
# define all(a) a.begin(), a.end()
# define rall(a) a.rbegin(), a.rend()
# define sz(a) (int) a.size()

using ld = long double;
using ll = long long;
using ull = unsigned long long;
using str = string;
using pi = pair<int, int>;

const int INF = 2e9 + 7;
const ld PI = 3.1415926535897932384626433832795;
const int MOD = 998244353;
const ld eps = 1e-12;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
bool chmin(T &a, const T &b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}

template<typename T>
bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template<typename T = int>
struct SparseTable {
    vector<vector<T>> t;
    vector<int> logs;

    void init_logs(int n) {
        logs.resize(n + 1);
        for (int i = 2 ; i <= n ; i++) {
            logs[i] = logs[i / 2] + 1;
        }
    }

    T func(T a, T b) {
        return gcd(a, b);
    }

    explicit SparseTable(vector<T> &v) {
        int n = sz(v);
        init_logs(n);

        t.resize(logs[n] + 1, vector<T>(n));
        t[0] = v;

        for (int l = 1 ; l <= logs[n] ; l++) {
            for (int i = 0 ; i + (1 << l) <= n ; i++) {
                t[l][i] = func(t[l - 1][i], t[l - 1][i + (1 << (l - 1))]);
            }
        }
    }

    T get(int l, int r) {
        int q = logs[r - l + 1];
        return func(t[q][l], t[q][r - (1 << q) + 1]);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &el : a)
        cin >> el;
    SparseTable st(a);
    int q;
    cin >> q;
    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << st.get(--l, --r) << " ";
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(16);

#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif

    int t = 1;
//    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}