#include <iostream>

typedef long long ll;

using std::cin;
using std::cout;

constexpr int max_n = 70;

ll f[max_n];

ll dfs(int cur) {
  if (f[cur] != 0)
    return f[cur];
  ll res = 1;
  for (int i = 1; i + i <= cur; ++i) {
    res += dfs(cur - 2 * i);
  }
  return f[cur] = res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  cin >> n;
  f[0] = 1;
  cout << dfs(n) << '\n';

  return 0;
}