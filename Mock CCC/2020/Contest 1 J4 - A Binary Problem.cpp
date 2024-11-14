#include <cstring>
#include <iostream>

const int N = 1e6 + 9;

int n;
std::string s;

int pfx[N], sfx[N];

int main() {
  memset(pfx, 0x3f, sizeof pfx);
  memset(sfx, 0x3f, sizeof sfx);
  scanf("%d", &n);
  std::cin >> s;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == '1')
      pfx[i + 1] = 0;
    else
      pfx[i + 1] = pfx[i] + 1;
  }
  for (int i = s.length() - 1; i >= 0; --i) {
    if (s[i] == '1')
      sfx[i + 1] = 0;
    else
      sfx[i + 1] = sfx[i + 2] + 1;
  }
  long long ans = 0;
  for (int i = 1; i <= n; ++i)
    ans += std::min(sfx[i], pfx[i]);
  printf("%lld\n", ans);
  return 0;
}