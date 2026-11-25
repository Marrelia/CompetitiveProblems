#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <set>

#define fi first
#define se second

typedef long long ll;
typedef std::pair<int, int> pii;

constexpr int MAX_N = 2e3 + 9, MAX_M = 3e2 + 9;

constexpr ll INF = 1e15;

constexpr ll MOD = 998244353;

std::mt19937 rnd(time(nullptr));

int n;
int a[MAX_N][MAX_N];

// the order that we will check the roots in
int crt[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    crt[i] = i;
    for (int j = i; j <= n; ++j) {
      std::cin >> a[i][j];
      a[j][i] = a[i][j];
    }
  }

  // shuffle the crt array
  std::shuffle(crt + 1, crt + n + 1, rnd);

  std::vector<pii> cand;
  {
    int rt = crt[1];
    for (int i = 1; i <= n; ++i) {
      for (int j = i + 1; j <= n; ++j) {
        int val = a[rt][i] ^ a[rt][j] ^ a[i][j];
        if (val == i || val == j)
          cand.push_back({i, j});
      }
    }
  }

  for (int cur = 2; cur <= n && cand.size() != n - 1; ++cur) {
    int rt = crt[cur];
    int m = 0;
    for (auto [i, j] : cand) {
      int val = a[rt][i] ^ a[rt][j] ^ a[i][j];
      if (val == i || val == j)
        cand[m++] = {i, j};
    }
    cand.resize(m);
  }

  for (const auto &i : cand)
    std::cout << i.fi << ' ' << i.se << '\n';

  return 0;
}

/*
Consider when we use node i as the root
dis(j) as the xor value from root to node j
Then we can choose candidate edge (x, y) for this tree
if dis(x) ^ dis(y) ^ a(x, y) = x or y, then we say it's a candidate

do this multiple times, and take the intersection among all the edges,
when the # of edges left become n-1, output it

See also I.cpp for normal solution
*/