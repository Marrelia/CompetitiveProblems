#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

constexpr int MAX_N = 1e5 + 9;
constexpr int S = 1288;

int n, d;
long long x;

int a[MAX_N], b[MAX_N];

// x is 64-bit variable;
long long getNextX() {
  x = (x * 37 + 10007) % 1000000007;
  return x;
}
void initAB() {
  int i;
  for (i = 0; i < n; i = i + 1) {
    a[i] = i + 1;
  }
  for (i = 0; i < n; i = i + 1) {
    std::swap(a[i], a[getNextX() % (i + 1)]);
  }
  for (i = 0; i < n; i = i + 1) {
    if (i < d)
      b[i] = 1;
    else
      b[i] = 0;
  }
  for (i = 0; i < n; i = i + 1) {
    std::swap(b[i], b[getNextX() % (i + 1)]);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> n >> d >> x;

  initAB();

  if (d > S) {
    std::set<std::pair<int, int>> pq;
    for (int i = 0; i < n; ++i) {
      pq.insert({-a[i], i});
      int ans = 0;
      for (auto it = pq.begin(); it != pq.end(); ++it)
        if (b[i - it->second] == 1) {
          ans = -it->first;
          break;
        }
      std::cout << ans << '\n';
    }
  } else {
    std::vector<int> pos;
    for (int i = 0; i < n; ++i) {
      if (b[i] == 1)
        pos.push_back(i);
      int ans = 0;
      for (const auto &j : pos)
        ans = std::max(ans, a[i - j]);
      std::cout << ans << '\n';
    }
  }

  return 0;
}