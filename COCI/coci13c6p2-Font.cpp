#include <iostream>

typedef long long ll;

using std::cin;
using std::cout;

constexpr int max_n = 35;

int n;
std::string s[max_n];
int cnt[26], tot;
ll pow2[max_n];

void modify_str(int id, int k) {
  for (const auto &ch : s[id]) {
    if (cnt[ch - 'a'] == 0)
      ++tot;
    cnt[ch - 'a'] += k;
    if (cnt[ch - 'a'] == 0)
      --tot;
  }
}

ll dfs(int u) {
  if (tot == 26) {
    return 1 << (n - u);
  } else if (u == n)
    return 0;
  ll res = 0;
  res += dfs(u + 1);
  modify_str(u, 1);
  res += dfs(u + 1);
  modify_str(u, -1);
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  cin >> n;

  for (int i = 0; i < n; ++i)
    cin >> s[i];

  cout << dfs(0) << '\n';

  return 0;
}