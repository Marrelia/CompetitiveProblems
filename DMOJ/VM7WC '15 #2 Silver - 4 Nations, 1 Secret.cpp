#include <iostream>

typedef unsigned long long ull;

const int N = 2.5e4 + 9;
const ull base = 131;

int n;
char s[N << 1];
ull h1[N << 1], h2[N << 1], p[N << 1];

bool check(int x, int idx) {
  int l1 = idx - x, r1 = idx;
  int l2 = idx, r2 = idx + x;
  return h2[l1] - h2[r1 + 1] * p[x + 1] == h1[r2] - h1[l2 - 1] * p[x + 1];
}

int main() {
  scanf("%d", &n);
  scanf("%s", s + 1);
  for (int i = n; i >= 1; --i) {
    s[i << 1] = s[i];
  }
  n = (n << 1) + 1;
  for (int i = 1; i <= n; i += 2) {
    s[i] = '#';
  }

  p[0] = 1;
  for (int i = 1; i <= n; ++i) {
    h1[i] = (h1[i - 1] * base) + s[i];
    h2[n - i + 1] = (h2[n - i + 2] * base) + s[n - i + 1];
    p[i] = p[i - 1] * base;
  }

  int ans = 1, ansIdx = 1, ansLen = 0;
  for (int i = 1; i <= n; ++i) {
    int l = 0, r = std::min(i - 1, n - i);
    while (l < r) {
      int mid = (l + r + 1) >> 1;
      if (check(mid, i))
        l = mid;
      else
        r = mid - 1;
    }

    if (i & 1 && ans < ((l + 1) / 2) * 2) {
      ans = ((l + 1) / 2) * 2;
      ansIdx = i;
      ansLen = l;
    } else if (!(i & 1) && ans < (l / 2) * 2 + 1) {
      ans = (l / 2) * 2 + 1;
      ansIdx = i;
      ansLen = l;
    }
  }

  for (int i = ansIdx - ansLen; i <= ansIdx + ansLen; ++i) {
    if (s[i] != '#')
      printf("%c", s[i]);
  }
  puts("");
  printf("%d\n", ans);
  return 0;
}