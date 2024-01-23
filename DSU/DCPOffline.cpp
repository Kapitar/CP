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

struct chash {
    int operator()(pi x) const { return x.first * 31 + x.second; }
};


struct DCPOffline {
    struct segment {
        int l, r, u, v;

        segment() = default;

        segment(int l, int r, int u, int v) : l(l), r(r), u(u), v(v) {}
    };

    int cur_time;
    DSURollback dsu;
    unordered_map<pi, int, chash> edges;
    vector<segment> segments;
    vector<int> queries;
    vector<vector<pi>> tree;
    vector<int> answer;

    DCPOffline() = default;

    explicit DCPOffline(int n) {
        dsu = DSURollback(n);
        cur_time = 0;
    }

    void add_edge(int u, int v) {
        if (u > v) swap(u, v);
        edges[make_pair(u, v)] = cur_time++;
    }

    void delete_edge(int u, int v) {
        if (u > v) swap(u, v);
        segments.emplace_back(edges[make_pair(u, v)], cur_time++, u, v);
        edges[make_pair(u, v)] = -1;
    }

    void ask() {
        queries.push_back(cur_time++);
    }

    void add(int v, int l, int r, int lq, int rq, pi edge) {
        if (lq <= l && r <= rq) {
            auto [a, b] = edge;
            tree[v].emplace_back(a, b);
            return;
        }

        if (max(l, lq) > min(r, rq)) return;

        int mid = (l + r) >> 1;
        add(2 * v + 1, l, mid, lq, rq, edge);
        add(2 * v + 2, mid + 1, r, lq, rq, edge);
    }

    void dfs(int v, int l, int r) {
        int cur_version = dsu.get_current_version();
        for (auto [a, b] : tree[v]) {
            dsu.unite(a, b);
        }
        if (l != r) {
            int mid = (l + r) >> 1;
            dfs(2 * v + 1, l, mid);
            dfs(2 * v + 2, mid + 1, r);
        } else {
            answer[l] = dsu.get_components_count();
        }

        dsu.rollback(cur_version);
    }

    void run() {
        for (auto [edge, last] : edges) {
            if (last == -1) continue;
            auto [u, v] = edge;
            segments.emplace_back(last, cur_time - 1, u, v);
        }

        tree.assign(4 * (cur_time + 1), {});
        answer.assign(cur_time + 1, {});

        for (auto [l, r, u, v] : segments) {
            add(0, 0, cur_time - 1, l, r, make_pair(u, v));
        }

        dfs(0, 0, cur_time - 1);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    if (q == 0) return;

    DCPOffline dcp(n);
    for (int i = 0 ; i < q ; i++) {
        char c;
        cin >> c;
        if (c == '+') {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            dcp.add_edge(u, v);
        } else if (c == '-') {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            dcp.delete_edge(u, v);
        } else {
            dcp.ask();
        }
    }

    dcp.run();
    for (auto qu : dcp.queries)
        cout << dcp.answer[qu] << "\n";
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