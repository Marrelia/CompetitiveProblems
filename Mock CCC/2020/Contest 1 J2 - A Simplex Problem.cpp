#include <iostream>

int k, c, m;
int x, y;

int main() {
  scanf("%d%d%d", &c, &m, &k);
  int ans = 0;
  for (x = 0; x <= k; ++x) {
    y = k - x;
    ans = std::max(ans, x * c + y * m);
  }
  printf("%d\n", ans);
  return 0;
}