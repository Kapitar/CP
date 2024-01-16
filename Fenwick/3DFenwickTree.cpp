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
    int n, m, k;
    vector<vector<vector<int>>> t;

    void init() {
        t.assign(n + 1, vector<vector<int>>(m + 1, vector<int>(k + 1)));
    }

    explicit FenwickTree(int n, int m, int k) : n(n), m(m), k(k) {
        init();
    }

    int sum(int x, int y, int z) {
        if (x < 0 || y < 0 || z < 0) return 0;
        int res = 0;

        for (int i = x + 1 ; i > 0 ; i = (i & (i - 1)))
            for (int j = y + 1 ; j > 0 ; j = (j & (j - 1)))
                for (int c = z + 1 ; c > 0 ; c = (c & (c - 1)))
                    res += t[i][j][c];

        return res;
    }

    int sum(int x1, int y1, int z1, int x2, int y2, int z2) {
        int a = sum(x2, y2, z2) - sum(x1 - 1, y2, z2) - sum(x2, y1 - 1, z2) + sum(x1 - 1, y1 - 1, z2);
        int b = sum(x2, y2, z1 - 1) - sum(x1 - 1, y2, z1 - 1) - sum(x2, y1 - 1, z1 - 1) + sum(x1 - 1, y1 - 1, z1 - 1);
        return a - b;
    }

    void update(int posx, int posy, int posz, int d) {
        for (int x = posx + 1 ; x <= n ; x = (x | (x - 1)) + 1)
            for (int y = posy + 1 ; y <= m ; y = (y | (y - 1)) + 1)
                for (int z = posz + 1 ; z <= k ; z = (z | (z - 1)) + 1)
                    t[x][y][z] += d;
    }
};

void solve() {
    int n;
    cin >> n;
    FenwickTree f(n, n, n);

    while (true) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y, z, k;
            cin >> x >> y >> z >> k;
            f.update(x, y, z, k);
        } else if (t == 2) {
            int x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << f.sum(x1, y1, z1, x2, y2, z2) << "\n";
        } else {
            break;
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