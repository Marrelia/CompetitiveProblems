#include <iostream>

const int N = 5e3 + 9;

int pa[N * N];

int main() {
  int n, m;
  int q;
  scanf("%d%d%d", &n, &m, &q);

  for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= m; ++j)
	  ++pa[i * j];
  for (int i = 1; i <= n * m; ++i)
	pa[i] += pa[i - 1];

  int t = n * m;
  while (q--) {
	int x;
	scanf("%d", &x);
	printf("%d\n", pa[t - x + 1] - t + pa[x]);
  }
  return 0;
}