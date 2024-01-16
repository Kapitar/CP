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

const int INF = 1e18;
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

struct node {
    int x, ind;
    int add;

    node(int x = 0, int ind = -1, int add = 0) : x(x), ind(ind), add(add) {}

    node operator+(const node &b) const {
        node c;
        c.x = min(x, b.x);
        c.ind = (x < b.x ? ind : b.ind);
        return c;
    }
};

node NEUTRAL(INF, INF, INF);

// min, +=
struct SegmentTree {
    int tree_size = 1;
    vector<node> t;

    void init(int n) {
        while (tree_size < n) tree_size <<= 1;
        t.assign(2 * tree_size - 1, {});
    }

    explicit SegmentTree(int n) {
        init(n);
    }

    explicit SegmentTree(vector<int> &a) {
        init((int) a.size());
        build(0, 0, tree_size - 1, a);
    }

    void build(int v, int l, int r, vector<int> &a) {
        if (l == r) {
            t[v].x = a[l];
            t[v].ind = l;
            return;
        }

        int mid = (l + r) >> 1;
        build(2 * v + 1, l, mid, a);
        build(2 * v + 2, mid + 1, r, a);
        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }

    void updatePush(int v, int l, int r, int x) {
        t[v].x += x;
        t[v].add += x;
    }

    void push(int v, int l, int r) {
        if (t[v].add == 0) return;

        int mid = (l + r) >> 1;
        updatePush(2 * v + 1, l, mid, t[v].add);
        updatePush(2 * v + 2, mid + 1, r, t[v].add);

        t[v].add = 0;
    }

    node get(int v, int l, int r, int lq, int rq) {
        if (lq <= l && r <= rq) return t[v];
        if (max(l, lq) > min(r, rq)) return NEUTRAL;

        push(v, l, r);
        int mid = (l + r) >> 1;
        return get(2 * v + 1, l, mid, lq, rq) + get(2 * v + 2, mid + 1, r, lq, rq);
    }

    void change_element(int v, int l, int r, int i, int x) {
        if (l == r) return updatePush(v, l, r, x);

        push(v, l, r);
        int mid = (l + r) >> 1;
        if (i <= mid) {
            change_element(2 * v + 1, l, mid, i, x);
        } else {
            change_element(2 * v + 2, mid + 1, r, i, x);
        }
        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }

    void change_segment(int v, int l, int r, int lq, int rq, int x) {
        if (lq <= l && r <= rq) return updatePush(v, l, r, x);
        if (max(l, lq) > min(r, rq)) return;

        push(v, l, r);
        int mid = (l + r) >> 1;
        change_segment(2 * v + 1, l, mid, lq, rq, x);
        change_segment(2 * v + 2, mid + 1, r, lq, rq, x);
        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }

    node get(int l, int r) {
        return get(0, 0, tree_size - 1, l, r);
    }

    void change_element(int i, int x) {
        change_element(0, 0, tree_size - 1, i, x);
    }

    void change_segment(int l, int r, int x) {
        change_segment(0, 0, tree_size - 1, l, r, x);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &el : a) cin >> el;

    SegmentTree segtree(a);

    int q;
    cin >> q;
    while (q--) {
        char c;
        cin >> c;
        if (c == 'm') {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << segtree.get(l, r).x << " ";
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            r--;
            segtree.change_segment(l, r, x);
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