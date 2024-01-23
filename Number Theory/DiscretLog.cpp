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

int binpow(int a, int b, int mod) {
    if (b == 0) return 1;
    if (b % 2 == 0) {
        int x = binpow(a, b / 2, mod) % mod;
        return (x * x) % mod;
    }
    return (binpow(a, b - 1, mod) * a) % mod;
}

int get_log(int a, int b, int n) {
    int wow = n;

    ll g = gcd(a, n);

    while (g != 1) {
        n /= g;
        g = gcd(n, a);
    }

    unordered_map<int, int> mp;
    int K = (int) sqrtl(wow) + 2;
    mp.reserve(K);
    for (int i = K ; i >= 1 ; i--) {
        mp[binpow(a, i * K, n)] = i;
    }

    vector<int> pref1(K + 1);
    pref1[0] = 1;
    for (int i = 1 ; i <= K ; i++) {
        pref1[i] = (pref1[i - 1] * a) % n;
    }

    for (int i = 0 ; i <= K ; i++) {
        int val = (b * pref1[i]) % n;
        if (mp.find(val) != mp.end()) {
            int meow = K * mp[val] - i;
            if (meow >= wow) continue;
            if (binpow(a, meow, wow) != b % wow) {
                continue;
            }
            return meow;
        }
    }

    return -1;
}

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