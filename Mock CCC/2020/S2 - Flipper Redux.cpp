#include <iostream>
#include <queue>

constexpr int N = 2e3 + 9;

int n;
int a[N][N];

int row[N], col[N];
bool cntRow[N], cntCol[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (a[i][j] == 1) {
        if (row[i] || col[j])
          continue;
        if (cntCol[j])
          col[j] = 1;
        else
          row[i] = 1, cntRow[i] = true;
      } else if (row[i]) {
        cntCol[j] = true;
      }
    }
    if (cntRow[i] == 1) {
      for (int j = 1; a[i][j] != 1; ++j) {
        cntCol[j] = true;
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (cntCol[i] && !col[i])
      col[i] = 1;
  }

  bool flag1 = false;
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (row[i])
      ++ans;
    if (col[i])
      ++ans;
    for (int j = 1; j <= n; ++j) {
      if (a[i][j] ^ row[i] ^ col[j] != 0)
        flag1 = true;
    }
  }
  if (flag1) {
    puts("-1");
  } else {
    printf("%d\n", ans);
    for (int i = 1; i <= n; ++i) {
      if (row[i])
        printf("R %d\n", i);
      if (col[i])
        printf("C %d\n", i);
    }
  }
  return 0;
}