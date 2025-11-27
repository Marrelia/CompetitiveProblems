#include <iostream>

#define fi first
#define se second

using std::cin;
using std::cout;

typedef long long ll;
typedef std::pair<int, int> pii;

constexpr int max_n = 1e6 + 9;

int n;
int a[max_n];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  cin >> n;
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    int x;
    cin >> x;
    if (a[x + 1]) --a[x + 1], --ans;
    ++a[x], ++ans;
  }
  
  cout << ans << '\n';
  
  return 0;
}