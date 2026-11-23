#include <iostream>

const int N = 1.5e5 + 9;

int n, m = N;
int s[N];

int t[N << 1];

int lowbit(int x) {
  return x & -x;
}

void add(int idx, int k) {
  while (idx <= m) {
    t[idx] += k;
    idx += lowbit(idx);
  }
}

int query(int r) {
  int res = 0;
  while (r > 0) {
    res += t[r];
    r -= lowbit(r);
  }
  return res;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    if (x == 2)
      x = -1;
    s[i] = s[i - 1] + x;
  }
  for (int i = 1; i <= n; ++i)
    s[i] += N, m = std::max(m, s[i]);
  s[0] = N;
  add(s[0], 1);
  long long res = 0;
  for (int i = 1; i <= n; ++i) {
    res += query(m) - query(s[i] - 1);
    add(s[i], 1);
  }
  printf("%lld\n", 1ll * n * (n + 1) / 2 - res);
  return 0;
}