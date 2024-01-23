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

struct LinearSieve {
    vector<int> sieve;
    vector<int> primes;

    LinearSieve() = default;
    explicit LinearSieve(int n) {
        n += 10;
        sieve.assign(n + 1, {});
        primes.clear();
        buildLinearSieve(n);
    }

    void buildLinearSieve(int n) {
        for (int i = 2 ; i <= n ; i++) {
            if (sieve[i] == 0) {
                sieve[i] = i;
                primes.push_back(i);
            }
            for (auto el : primes) {
                if (el > i) break;
                if (el * i > (int) n) break;
                sieve[el * i] = el;
            }
        }
    }

    vector<int> factorize(int n) {
        vector<int> facts;
        while(n > 1) {
            facts.emplace_back(sieve[n]);
            n /= sieve[n];
        }

        return facts;
    }
};

LinearSieve sieve(100);

void solve() {
    int n;
    cin >> n;
    vector<int> facts = sieve.factorize(n);
    for(auto el : facts)cout << el << " ";
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