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

struct FenwickTree {
    int tree_size;
    vector<int> t;

    void init(int n) {
        tree_size = n;
        t.assign(n + 1, {});
    }

    explicit FenwickTree(int n) {
        init(n);
    }

    explicit FenwickTree(vector<int> &a) {
        init((int) a.size());
        for (int i = 0 ; i < a.size() ; i++) change(i, a[i]);
    }

    int sum(int i) {
        int ans = 0;
        for (++i ; i > 0 ; i = (i & (i - 1))) ans += t[i];
        return ans;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void change(int i, int x) {
        for (++i ; i <= tree_size ; i = (i | (i - 1)) + 1) t[i] += x;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &el : a) cin >> el;
    FenwickTree f(a);

    int q;
    cin >> q;
    while (q--) {
        char c;
        cin >> c;
        if (c == 's') {
            int l, r;
            cin >> l >> r;
            cout << f.sum(--l, --r) << " ";
        } else {
            int i, x;
            cin >> i >> x;
            i--;
            f.change(i, -f.sum(i, i) + x);
        }
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