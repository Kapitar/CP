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

//# define int long long
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

struct DSURollback {
    int components_count;
    vector<int> roots;
    vector<int> sizes;
    vector<pair<int *, int>> changes;

    DSURollback() = default;

    explicit DSURollback(int n) {
        components_count = n;
        roots.assign(n, {});
        sizes.assign(n, 1);
        iota(all(roots), 0ll);
    }

    int find_root(int v) {
        while (roots[v] != v)
            v = roots[v];
        return v;
    }

    void unite(int a, int b) {
        a = find_root(a);
        b = find_root(b);

        if (a == b) return;
        if (sizes[a] < sizes[b]) swap(a, b);
        changes.emplace_back(&components_count, components_count);
        components_count--;
        changes.emplace_back(&roots[b], roots[b]);
        roots[b] = a;
        changes.emplace_back(&sizes[a], sizes[a]);
        sizes[a] += sizes[b];
    }

    int get_current_version() {
        return sz(changes);
    }

    int get_components_count() {
        return components_count;
    }

    void rollback(int s) {
        while (sz(changes) > s) {
            *changes.back().first = changes.back().second;
            changes.pop_back();
        }
    }
};

void solve() {

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