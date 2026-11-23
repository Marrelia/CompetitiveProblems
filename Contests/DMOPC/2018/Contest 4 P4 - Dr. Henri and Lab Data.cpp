#include <algorithm>
#include <iostream>

constexpr int N = 2e5 + 9;

typedef long long ll;

struct Num {
  int x, id;
} a[N];

struct Query {
  int l, r, k, id;
  ll ans;
} q[N];

int n, m;
ll t[N];

int lowbit(const int &x) {
  return x & (-x);
}

void add(int idx, const ll &k) {
  while (idx <= n) {
    t[idx] += k;
    idx += lowbit(idx);
  }
}

ll query(int idx) {
  ll res = 0;
  while (idx > 0) {
    res += t[idx];
    idx -= lowbit(idx);
  }
  return res;
}

bool cmp1(const Num &A, const Num &B) {
  return A.x < B.x;
}

bool cmp2(const Query &A, const Query &B) {
  return A.k < B.k;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i].x);
    a[i].id = i;
    add(i, a[i].x);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].k);
    q[i].id = i;
  }
  std::sort(a + 1, a + n + 1, cmp1);
  std::sort(q + 1, q + m + 1, cmp2);

  int pt = 1;
  for (int i = 1; i <= m; ++i) {
    while (pt <= n && a[pt].x < q[i].k) {
      add(a[pt].id, -(a[pt].x << 1));
      ++pt;
    }
    q[i].ans = query(q[i].r) - query(q[i].l - 1);
  }
  std::sort(q + 1, q + m + 1,
            [](const Query &A, const Query &B) -> bool
            {
              return A.id < B.id;
            });
  for (int i = 1; i <= m; ++i) {
    printf("%lld\n", q[i].ans);
  }
  return 0;
}