#include <iostream>
#include <vector>

std::string ans;

std::vector< std::vector< int > > cnt[30];
std::vector< std::string > s;
std::vector< int > c[30];
std::vector< int > pt;
std::vector< int > len, pre;

int tmp[30];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::cin >> n;
  for (int i = 0; i < 26; ++i)
    cnt[i].resize(n + 2), c[i].resize(n + 2);
  pt.resize(n + 2);
  len.resize(n + 2);
  pre.resize(n + 2);
  s.resize(n + 2);
  for (int i = 1; i <= n; ++i) {
    std::cin >> s[i];
    len[i] = s[i].length();
    pt[i] = 1;
    for (int k = 0; k < 26; ++k)
      cnt[k][i].resize(len[i] + 2);
    for (int j = 0; j < len[i]; ++j) {
      cnt[s[i][j] - 'a'][i][j + 1] = cnt[s[i][j] - 'a'][i][j] + 1;
      for (int k = 0; k < 26; ++k) {
        if (s[i][j] - 'a' != k)
          cnt[k][i][j + 1] = cnt[k][i][j];
      }
    }
    for (int j = len[i] - 1; j >= 0; --j)
      s[i][j + 1] = s[i][j];
    for (int k = 0; k < 26; ++k) {
      if (cnt[k][i][len[i]])
        ++tmp[k];
      c[k][i] = cnt[k][i][len[i]];
    }
  }

  int x = -1;
  for (int k = 25; k >= 0; --k) {
    if (tmp[k] == n) {
      x = k;
      break;
    }
  }

  while (x != -1) {
    for (int k = 0; k < 26; ++k)
      tmp[k] = 0;
    for (int i = 1; i <= n; ++i) {
      for (; pt[i] <= len[i]; ++pt[i]) {
        if (s[i][pt[i]] - 'a' == x)
          break;
      }
      for (int k = 0; k < 26; ++k) {
        c[k][i] -= cnt[k][i][pt[i]] - cnt[k][i][pre[i]];
        if (c[k][i])
          ++tmp[k];
      }
      pre[i] = pt[i];
      ++pt[i];
    }
    ans += (char)x + 'a';
    x = -1;
    for (int i = 25; i >= 0; --i)
      if (tmp[i] == n) {
        x = i;
        break;
      }
  }
  if (!ans.empty())
    std::cout << ans << std::endl;
  else
    std::cout << -1 << std::endl;
  return 0;
}