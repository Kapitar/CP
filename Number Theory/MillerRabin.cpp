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

// p - 1 = 2^n * m
bool miller(int p) {
    int n = 0;
    int m = p - 1;
    while (m % 2 == 0) {
        m /= 2;
        n++;
    }
    int a = uniform_int_distribution<int>(1, p)(rnd);

    int x = binpow(a, m, p);
    for (int i = 0 ; i <= n ; i++) {
        if (x == 1 or x == p - 1) {
            return true;
        }
        x = (x * x) % p;
    }
    return false;
}

bool isPrime(int n) {
    if (n == 1) {
        return false;
    }

    if (n <= 1'000'000'000) {
        for (int i = 2 ; i * i <= n ; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    bool flag = false;
    for (int i = 0 ; i < 10 ; i++) {
        flag |= miller(n);
    }
    return flag;
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