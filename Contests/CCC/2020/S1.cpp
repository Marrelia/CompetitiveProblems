#include <algorithm>
#include <cmath>
#include <iostream>

#define f first
#define s second

typedef std::pair< int, int > PII;

const int N = 1e5 + 9;

int n;
PII a[N];

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0);
  std::cin >> n;
  double mx = 0;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i].f >> a[i].s;
  }
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i < n; ++i)
    mx =
      std::max(mx, 1.0 * (fabs(a[i + 1].s - a[i].s)) / (a[i + 1].f - a[i].f));
  printf("%lf\n", mx);
  return 0;
}