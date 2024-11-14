#include <algorithm>
#include <cstdio>

constexpr int N = 1e5 + 9, M = 2e4 + 9;

int n, Q;
int t[N];

struct Query {
  int l, r, k, ans, id;
} q[N];

struct Node {
  int id, num;
} a[N];

int lowbit(int x) {
  return x & -x;
}

void add(int idx, int k) {
  while (idx <= n) {
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
    scanf("%d", &a[i].num);
    a[i].id = i;
    add(i, a[i].num);
  }
  scanf("%d", &Q);
  for (int i = 1; i <= Q; ++i)
    scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].k), q[i].id = i, ++q[i].l, ++q[i].r;
  std::sort(q + 1, q + Q + 1,
            [](Query A, Query B)
            {
              return A.k < B.k;
            });
  std::sort(a + 1, a + n + 1,
            [](Node A, Node B)
            {
              return A.num < B.num;
            });
  int pt = 1;
  for (int i = 1; i <= Q; ++i) {
    while (pt <= n && a[pt].num < q[i].k) {
      add(a[pt].id, -a[pt].num);
      ++pt;
    }
    q[i].ans = query(q[i].r) - query(q[i].l - 1);
  }
  std::sort(q + 1, q + Q + 1,
            [](Query A, Query B)
            {
              return A.id < B.id;
            });
  for (int i = 1; i <= Q; ++i)
    printf("%d\n", q[i].ans);
  return 0;
}