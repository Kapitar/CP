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
struct BlockRMQ {
    struct SparseTable {
        vector<vector<T>> t;
        vector<int> logs;

        void init_logs(int n) {
            logs.resize(n + 1);
            for (int i = 2 ; i <= n ; i++) {
                logs[i] = logs[i / 2] + 1;
            }
        }

        T func(T a, T b) { // do not forget to change this in both places
            return (a < b ? a : b);
        }

        SparseTable() = default;

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
            if (l > r) return T(INF);
            int q = logs[r - l + 1];
            return func(t[q][l], t[q][r - (1 << q) + 1]);
        }
    };

    T func(T a, T b) { // do not forget to change this in both places
        return (a < b ? a : b);
    }

    const int K = 32;
    SparseTable sparse_table;
    vector<vector<T>> blocks;
    vector<vector<T>> pref;
    vector<vector<T>> suff;
    vector<T> global;
    vector<vector<bitset<32>>> masks;

    BlockRMQ() = default;

    explicit BlockRMQ(vector<T> &arr) {
        int n = sz(arr);
        int M = (n + K - 1) / K;
        blocks.assign(M, {});
        global.assign(M, {});
        pref.assign(M, vector<T>(K));
        suff.assign(M, vector<T>(K));
        masks.assign(M, vector<bitset<32>>(K));
        for (int i = 0 ; i < n ; i++) {
            blocks[i / K].push_back(arr[i]);
        }

        for (int i = 0 ; i < M ; i++) {
            for (int j = 0 ; j < sz(blocks[i]) ; j++) {
                if (j == 0) pref[i][j] = blocks[i][j];
                else pref[i][j] = func(blocks[i][j], pref[i][j - 1]);
            }

            for (int j = sz(blocks[i]) - 1 ; j >= 0 ; j--) {
                if (j == sz(blocks[i]) - 1) suff[i][j] = blocks[i][j];
                else suff[i][j] = func(blocks[i][j], suff[i][j + 1]);
            }

            vector<int> st;
            bitset<32> bs;
            for (int j = 0 ; j < sz(blocks[i]) ; j++) {
                while (!st.empty() and blocks[i][j] <= blocks[i][st.back()]) { // do not forget to change this
                    bs[st.back()] = false;
                    st.pop_back();
                }
                st.push_back(j);
                bs[j] = true;
                masks[i][j] = bs;
            }

            T val = blocks[i][0];
            for (int j = 0 ; j < sz(blocks[i]) ; j++) {
                val = func(val, blocks[i][j]);
            }
            global[i] = val;
        }

        sparse_table = SparseTable(global);
    }

    T get(int l, int r) {
        if (l / K == r / K) {
            int lq = l % K;
            int rq = r % K;
            bitset<32> a = masks[l / K][rq];
            a &= ((1ll << (rq + 1)) - 1 - ((1ll << lq) - 1));
            return blocks[l / K][a._Find_first()];
        }

        return func(suff[l / K][l % K],
                    func(sparse_table.get(l / K + 1, r / K - 1),
                         pref[r / K][r % K]));
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &el : a)cin >> el;
    BlockRMQ rmq(a);
    for (int i = 0 ; i + k - 1 < n ; i++) {
        cout << rmq.get(i, i + k - 1) << "\n";
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