#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>

#define fi first
#define se second

using std::cin;
using std::cout;

typedef long long ll;
typedef std::pair<int, int> pii;
typedef std::pair<ll, int> pli;

constexpr int MAX_N = 4e5 + 9, MAX_M = 1e6 + 9;

constexpr ll INF = 1e18;

constexpr ll MOD = 998244353;

const double Pi = acos(-1);

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dis(0.0, 2 * Pi);

struct Point {
  long double x, y;
  ll ox, oy;

  long double val() { return x; }
} a[MAX_N];

int n;
ll ans;

ll get_dis(const Point &A, const Point &B) {
  return (A.ox - B.ox) * (A.ox - B.ox) + (A.oy - B.oy) * (A.oy - B.oy);
}

void rotate() {
  long double ang = dis(gen);
  for (int i = 1; i <= n; ++i) {
    auto &x = a[i].ox, &y = a[i].oy;
    a[i].x = x * std::cos(ang) - y * std::sin(ang);
    a[i].y = x * std::sin(ang) + y * std::cos(ang);
  }
}

void solve() {
  std::sort(a + 1, a + n + 1,
            [](Point &A, Point &B) { return A.val() < B.val(); });

  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= std::min(i + 10, n); ++j)
      ans = std::min(ans, get_dis(a[i], a[j]));
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].x >> a[i].y;
    a[i].ox = a[i].x;
    a[i].oy = a[i].y;
  }
  ans = get_dis(a[1], a[2]);
  int num_cases = 2;
  while (num_cases--) {
    rotate();
    solve();
  }
  cout << ans << '\n';
  return 0;
}
