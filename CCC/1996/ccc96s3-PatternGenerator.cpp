#include <iostream>

typedef long long ll;

using std::cin;
using std::cout;

constexpr int max_n = 35;

int n, k;
int a[max_n];

void dfs(int digit, int rem1) {
  if (digit == n) {
    for (int i = 0; i < n; ++i)
      cout << a[i];
    cout << '\n';
    return;
  }
  if (rem1 > 0) {
    a[digit] = 1;
    dfs(digit + 1, rem1 - 1);
  }
  if (n - digit > rem1) {
    a[digit] = 0;
    dfs(digit + 1, rem1);
  }
}

void solve() {
  cin >> n >> k;
  cout << "The bit patterns are\n";
  dfs(0, k);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    solve();
    if (T)
      cout << '\n';
  }

  return 0;
}