#include <array>
#include <iostream>
#include <unordered_map>

using namespace std;

#define ar array
#define fi first
#define se second

typedef long long ll;
typedef pair< int, int > pi;

namespace SOLVE {
  const int MAX_N = 2e5 + 9;

  int n;
  ar< int, MAX_N > a;
  unordered_map< int, int > cnt;

  void solve() {
    cnt.clear();
    cin >> n;
    int ans = 0, lm0 = -1;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      ans += a[i] > 0;
      if (lm0 == -1 && a[i] == 0)
        lm0 = i;
    }
    if (lm0 == -1) {
      std::cout << ans << '\n';
      return;
    }
    int pt = 1;
    bool flag = true;
    for (int i = lm0 + 1; i <= n; ++i)
      if (a[i] > 0)
        ++cnt[a[i]];
    while (cnt[pt])
      ++pt;
    for (int i = lm0 - 1; i >= 1; --i) {
      if (a[i] < pt) {
        flag = false;
        break;
      }
      ++cnt[a[i]];
      while (cnt[pt])
        ++pt;
    }
    ans += flag;
    cout << ans << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int Kase = 1;
  cin >> Kase;
  while (Kase--) {
    SOLVE::solve();
  }
  return 0;
}