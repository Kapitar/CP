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

int binpow(int a, int b, int p) {
    if (b == 0) return 1;
    if (b & 1) return (a * binpow(a, b - 1, p)) % p;
    int x = binpow(a, b / 2, p);
    return (x * x) % p;
}

int get_g(int p) {
    int meow = p - 1;
    int phi = p - 1;
    vector<int> fact;
    for (int i = 2 ; i * i <= meow ; i++) {
        if (meow % i == 0) {
            fact.push_back(i);
            while (meow % i == 0) meow /= i;
        }
    }

    if (meow > 1) {
        fact.push_back(meow);
    }

    for (int i = 2 ; i <= p ; i++) {
        bool ok = true;
        for (auto el : fact) {
            int val = binpow(i, phi / el, p);
            if (val == 1) {
                ok = false;
            }
        }

        if (ok) {
            return i;
        }
    }
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

// x^k = a (mod n)
int sqrtMod(int a, int k, int n) {
    if (a == 0 and k == 0) {
        return -1;
    }

    if (a == 0) {
        return 0;
    }

    int g = get_g(n);
    int x = get_log(binpow(g, k, n), a, n) % n;
    if (x == -1) {
        return -1;
    }
    return (ll) (binpow(g, x, n) % n);
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