#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

#define fi first
#define se second

typedef long long ll;
typedef std::pair<int, int> pii;

constexpr int MAX_N = 2e3 + 9, MAX_M = 3e2 + 9;

constexpr ll INF = 1e15;

constexpr ll MOD = 998244353;

int n;
int a[MAX_N][MAX_N], lca[MAX_N][MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; ++j) {
      std::cin >> a[i][j];
      a[j][i] = a[i][j];
    }
  }

  for (int i = 1; i <= n; ++i) {
    lca[i][i] = i;
    for (int j = i + 1; j <= n; ++j) {
      lca[i][j] = lca[j][i] = a[i][j] ^ (a[1][i] ^ a[1][j]);
    }
  }

  std::priority_queue<pii> pq;
  for (int i = 1; i <= n; ++i) {
    int cnt = 0;
    for (int j = 1; j <= n; ++j)
      cnt += (lca[i][j] == i);
    pq.emplace(cnt, i);
  }

  std::vector<int> det;
  std::vector<pii> edge;
  while (!pq.empty()) {
    int u = pq.top().se;
    pq.pop();
    for (int i = det.size() - 1; i >= 0; --i) {
      if (lca[det[i]][u] == det[i]) {
        edge.emplace_back(det[i], u);
        break;
      }
    }
    det.push_back(u);
  }

  for (const auto &i : edge) {
    std::cout << i.fi << ' ' << i.se << '\n';
  }

  return 0;
}