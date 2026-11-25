#include <algorithm>
#include <cstring>
#include <ctime>
#include <iostream>
#include <random>


#define fi first
#define se second

typedef long long ll;
typedef std::pair<int, int> pii;
typedef std::pair<ll, int> pli;

constexpr int MAX_N = 1e6 + 9, MAX_M = 3e2 + 9;

constexpr ll INF = 1e15;

constexpr ll MOD = 998244353;

std::mt19937 rnd(time(nullptr));
ll a[MAX_N], b[MAX_N];
int num[MAX_N];

ll d[MAX_N], ind;
ll pd[MAX_N], pind;
int cnt[MAX_N];

// binary gcd, makes it faster
static inline ll bgcd(ll a, ll b) {
  if (!a || !b)
    return a | b;
  int az = __builtin_ctzll(a), bz = __builtin_ctzll(b);
  int sh = std::min(az, bz);
  b >>= bz;
  while (a) {
    a >>= az;
    ll diff = (ll)b - (ll)a;
    az = __builtin_ctzll(diff);
    b = std::min(a, b);
    a = diff < 0 ? -diff : diff;
  }
  return b << sh;
}

int main() {

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%lld", &a[i]);
  memcpy(b, a, sizeof a);
  std::sort(a, a + n);
  int m = 0;
  for (int i = 0, cnt = 0; i <= n; ++i) {
    if (i > 0 && a[i] != a[i - 1]) {
      num[m++] = cnt;
      cnt = 1;
    } else {
      ++cnt;
    }
  }
  m = std::unique(a, a + n) - a;

  // You can choose any number as long as it doesn't wrong answer or TLE
  // Be aware that probability of getting wrong answer is (1-2^-S)^100
  // 100 is # of test cases in cf
  // *in theory
  int S = 12;
  ll ans = 1;
  while (S--) {
    ll x = b[rnd() % n];
    if (x <= ans)
      continue;

    // Get the divisors
    ind = 0;
    for (ll i = 1; i <= x / i; ++i) {
      if (x % i == 0) {
        d[ind++] = i;
        if (x / i != i)
          d[ind++] = x / i;
      }
    }

    // Get all the prime divisors
    pind = 0;
    ll tmp = x;
    for (ll i = 2; i * i <= x; ++i) {
      if (x % i == 0) {
        pd[pind++] = i;
        while (x % i == 0)
          x /= i;
      }
    }
    if (x > 1)
      pd[pind++] = x;
    x = tmp;

    std::sort(d, d + ind);

    memset(cnt, 0, sizeof(int) * ind);
    // Mark the divisor that is the gcd between current number and selected
    // number
    for (int i = 0; i < m; ++i)
      cnt[std::lower_bound(d, d + ind, bgcd(a[i], x)) - d] += num[i];

    // use a dp kind idea to do that
    // if a % b == 0, then for b, we also need to include # of multiples of a
    // time complexity d(A) * w(A), where d(n) means # of divisor of n,
    // w(n) means # of different prime factors of n
    // In cp, d(n) is often approximate to n^1/3
    // w(A) is at most 11 for A <= 1e12, so it should pass easily
    for (int i = 0; i < pind; ++i) {
      for (int j = ind - 1; j >= 0; --j) {
        if (d[j] > x / pd[i] + 1)
          continue;
        int pos = std::lower_bound(d, d + ind, d[j] * pd[i]) - d;
        if (pos != ind && d[j] * pd[i] == d[pos])
          cnt[j] += cnt[pos];
      }
    }

    // update the answer
    for (int i = 0; i < ind; ++i)
      if (cnt[i] + cnt[i] >= n)
        ans = std::max(ans, d[i]);
  }

  printf("%lld\n", ans);

  return 0;
}

/*
TLE hell bro

3875ms
O(S(nlogn + d(A) * w(A) * logn + sqrt(A)))
*/