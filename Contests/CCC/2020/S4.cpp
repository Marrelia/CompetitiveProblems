#include <iostream>

const int d[6][2] = {{0, 1}, {1, 2}, {2, 0}, {1, 0}, {2, 1}, {0, 2}};

constexpr int N = 1e6 + 9;

int n;
std::string s;

int t[N][3], tot[N];
int cnt[3];

int get(int i, int len, int color) {
  int res = t[i + len - 1][color];
  if (i > 0) res -= t[i - 1][color];
  return res;
}

int main() {
  std::cin >> s;
  n = s.length();
  for (int i = 0; i < n; ++i) {
    if (i > 0) {
      t[i][0] = t[i - 1][0];
      t[i][1] = t[i - 1][1];
      t[i][2] = t[i - 1][2];
    }
    ++t[i][s[i] - 'A'];
    ++cnt[s[i] - 'A'];
  }

  int ans = 0x3f3f3f3f;
  for (int k = 0; k < 6; ++k) {
    int c1 = d[k][0], c2 = d[k][1];
    for (int i = 0; i + cnt[c1] + cnt[c2] <= n; ++i) {
      ans = std::min(cnt[c1] - get(i, cnt[c1], c1) + cnt[c2] - get(i + cnt[c1], cnt[c2], c2)
                       - std::min(get(i, cnt[c1], c2), get(i + cnt[c1], cnt[c2], c1))
        , ans);
    }
  }
  printf("%d\n", ans);
  return 0;
}