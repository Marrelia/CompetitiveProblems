#include <iostream>

constexpr int N = 2e5 + 9;

int n, m;
int s[N];
long long t[N];

int lowbit(const int x) {
  return x & (-x);
}

void add(const int idx, const int k) {
  for (int i = idx; i <= m; i += lowbit(i)) t[i] += k;
}

long long query(int idx) {
  long long res = 0;
  while (idx > 0) {
    res += t[idx];
    idx -= lowbit(idx);
  }
  return res;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &s[i]);
    s[i] = (s[i - 1] + s[i]) % m;
  }

  long long cnt = 0;
  for (int i = 1; i <= n; ++i) {
    cnt += query(m) - query(s[i] + 1);
    add(s[i] + 1, 1);
  }

  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += 1ll * i * s[i];
  }
  for (int i = 1; i < n; ++i) {
    ans -= 1ll * (n - i) * s[i];
  }
  ans += 1ll * cnt * m;
  printf("%lld\n", ans);

  return 0;
}