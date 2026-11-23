#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

using std::cin;
using std::cout;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n, k;
  cin >> n >> k;
  std::vector<int> p(n + 1), d(n + 1);
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    cin >> p[i] >> d[i];
    d[i] = p[i] - d[i];
    ans += p[i]; 
  }
  
  std::sort(d.begin(), d.end(), std::greater<>());
  for (int i = 0; i < k; ++i) ans -= d[i];
  cout << ans << '\n';
  return 0;
}