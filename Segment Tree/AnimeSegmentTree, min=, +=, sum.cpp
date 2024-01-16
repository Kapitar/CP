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

struct node {
    int sum;
    int maxx;
    int second_max;
    int cnt_max;
    int add;

    node(int sum = 0, int maxx = 0, int second_max = 0, int cnt_max = 0, int add = 0) : sum(sum), maxx(maxx),
                                                                                        second_max(second_max),
                                                                                        cnt_max(cnt_max), add(add) {}

    node operator+(const node &b) const {
        node c;
        c.sum = sum + b.sum;
        if (maxx > b.maxx) {
            c.maxx = maxx;
            c.second_max = max(second_max, b.maxx);
            c.cnt_max = cnt_max;
        } else if (maxx < b.maxx) {
            c.maxx = b.maxx;
            c.second_max = max(b.second_max, maxx);
            c.cnt_max = b.cnt_max;
        } else {
            c.maxx = maxx;
            c.second_max = max(second_max, b.second_max);
            c.cnt_max = cnt_max + b.cnt_max;
        }
        return c;
    }
};

node NEUTRAL(0, -INF, INF);

// min=, sum
struct AnimeSegmentTree {
    int tree_size = 1;
    vector<node> t;

    void init(int n) {
        while (tree_size < n) tree_size <<= 1;
        t.assign(2 * tree_size - 1, {});
    }

    explicit AnimeSegmentTree(int n) {
        init(n);
    }

    explicit AnimeSegmentTree(vector<int> &a) {
        init((int) a.size());
        build(0, 0, tree_size - 1, a);
    }

    void build(int v, int l, int r, vector<int> &a) {
        if (l == r) {
            t[v].sum = a[l];
            t[v].maxx = a[l];
            t[v].cnt_max = 1;
            t[v].second_max = -INF;
            return;
        }

        int mid = (l + r) >> 1;
        build(2 * v + 1, l, mid, a);
        build(2 * v + 2, mid + 1, r, a);
        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }

    void updatePushSum(int v, int l, int r, int x) {
        t[v].maxx += x;
        t[v].second_max += x;
        t[v].sum += x * (r - l + 1);
        t[v].add += x;
    }

    void updatePush(int v, int l, int r, int x) {
        if (t[v].maxx < x) return;
        t[v].sum = t[v].sum - t[v].cnt_max * t[v].maxx + t[v].cnt_max * x;
        t[v].maxx = x;
    }

    void push(int v, int l, int r) {
        int mid = (l + r) >> 1;

        updatePushSum(2 * v + 1, l, mid, t[v].add);
        updatePushSum(2 * v + 2, mid + 1, r, t[v].add);
        t[v].add = 0;

        updatePush(2 * v + 1, l, mid, t[v].maxx);
        updatePush(2 * v + 2, mid + 1, r, t[v].maxx);
    }

    node get(int v, int l, int r, int lq, int rq) {
        if (lq <= l && r <= rq) return t[v];
        if (max(l, lq) > min(r, rq)) return NEUTRAL;

        push(v, l, r);
        int mid = (l + r) >> 1;
        return get(2 * v + 1, l, mid, lq, rq) + get(2 * v + 2, mid + 1, r, lq, rq);
    }

    void min_equal(int v, int l, int r, int lq, int rq, int x) {
        if (max(l, lq) > min(r, rq) || t[v].maxx <= x) return;
        if (lq <= l && r <= rq && t[v].second_max < x) return updatePush(v, l, r, x);

        push(v, l, r);
        int mid = (l + r) >> 1;
        min_equal(2 * v + 1, l, mid, lq, rq, x);
        min_equal(2 * v + 2, mid + 1, r, lq, rq, x);
        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }

    void change_segment(int v, int l, int r, int lq, int rq, int x) {
        if (max(l, lq) > min(r, rq)) return;
        if (lq <= l && r <= rq) return updatePushSum(v, l, r, x);


        push(v, l, r);
        int mid = (l + r) >> 1;
        change_segment(2 * v + 1, l, mid, lq, rq, x);
        change_segment(2 * v + 2, mid + 1, r, lq, rq, x);
        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }

    node get(int l, int r) {
        return get(0, 0, tree_size - 1, l, r);
    }

    void min_equal(int l, int r, int x) {
        min_equal(0, 0, tree_size - 1, l, r, x);
    }

    void change_segment(int l, int r, int x) {
        change_segment(0, 0, tree_size - 1, l, r, x);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> v(n, 0);
    for (auto &el : v) cin >> el;
    int q;
    cin >> q;
    AnimeSegmentTree t(v);
    while (q--) {
        int c;
        cin >> c;
        if (c == 3) {
            int l, r;
            cin >> l >> r;
            --l;
            --r;
            int a = t.get(l, r).sum;
            cout << a << "\n";
        } else if (c == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            --l;
            --r;
            t.min_equal(l, r, x);
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            r--;
            t.change_segment(l, r, x);
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