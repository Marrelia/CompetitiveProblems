#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

#define fi first
#define se second

typedef long long ll;
typedef std::pair<int, int> pii;

constexpr int MAX_N = 1e5 + 9, MAX_M = 3e2 + 9;

constexpr ll INF = 1e15;

constexpr ll MOD = 998244353;

std::mt19937 rnd(time(nullptr));

int n;
pii a[MAX_N];

// check if in range
bool in_ran(int sx, int sy, pii d) {
  if (sx + d.fi < 1 || sx + d.fi > n)
    return false;
  if (sy + d.se < 1 || sy + d.se > n)
    return false;
  return true;
}

bool check(int sx, int sy, int fx, int fy) {
  if (sx == fx && sy == fy)
    return true;
  int dx = fx - sx, dy = fy - sy;
  for (int i = 1; i <= n; ++i) {
    if (a[i].fi == dx && a[i].se == dy)
      return true;
    int p =
        std::lower_bound(a + 1, a + n + 1, (pii){dx - a[i].fi, dy - a[i].se}) -
        a;
    if (p == n + 1)
      continue;
    if (a[i].fi + a[p].fi == dx && a[i].se + a[p].se == dy &&
        (in_ran(sx, sy, a[i]) || in_ran(sx, sy, a[p])))
      return true;
  }
  return false;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  int ax, ay, bx, by;
  std::cin >> ax >> ay >> bx >> by;
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i].fi >> a[i].se;
  std::sort(a + 1, a + n + 1);

  if (check(ax, ay, bx, by)) {
    std::cout << "Alice wins\n";
    return 0;
  }

  if (n <= 7) {
    int x = -1, y = -1;
    bool flag = false;
    for (x = 1; x <= n; ++x) {
      for (y = 1; y <= n; ++y) {
        if (!check(bx, by, x, y)) {
          flag = true;
          break;
        }
      }
      if (flag)
        break;
    }
    if (!flag)
      std::cout << "Bob wins\n";
    else
      std::cout << "tie " << x << ' ' << y << '\n';
    return 0;
  }

  int sx, sy;
  do {
    sx = rnd() % n + 1, sy = rnd() % n + 1;
  } while (check(bx, by, sx, sy));

  std::cout << "tie " << sx << ' ' << sy << '\n';

  return 0;
}

/*

The key observation is that using any zero, one or two of the n types of move,
we only have at most 1 + n + n * (n + 1) / 2 types of move
there are n^2 points in total, so if n is very large,
the number of nodes that one cannot reach is approximately half of all the nodes

When n <= 7, this ratio is still pretty big because of the n + 1 + n/2 terms
so we just brute force to check if any of the nodes works
or none of them work, which we will output Bob wins

When n is big, we can randomly choose some points and check if they work
The probability we got one correct answer in kth round is
1 - (1/2)^k, so the # of rounds will be small enough for us to pass

 */