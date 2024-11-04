//
// Created by BarretShen on 11/3/2024.
//
#include <cstring>
#include <iostream>

const int N = 15;

/*
 * 0 up
 * 1 down
 * 2 left
 * 3 right
 */
int d[4][N][N];
int n, m;

int main() {
  int round = 0;
  while (scanf("%d%d", &n, &m) == 2) {
	if (++round > 1) puts("\n**********************************\n");
	printf("Problem #%d\n\n", round);
	memset(d, 0, sizeof d);
	for (int i = 1; i <= m; ++i) {
	  char opt[2];
	  int x, y;
	  scanf("%s%d%d", opt, &x, &y);
	  if (opt[0] == 'H') d[3][x][y] = d[2][x][y + 1] = 1;
	  if (opt[0] == 'V') d[1][y][x] = d[0][y + 1][x] = 1;
	}
	for (int i = 1; i <= n; ++i) {
	  for (int j = 1; j <= n; ++j) {
		d[0][i][j] *= d[0][i - 1][j] + 1;
		d[2][i][j] *= d[2][i][j - 1] + 1;
	  }
	}
	for (int i = n; i >= 1; --i) {
	  for (int j = n; j >= 1; --j) {
		d[1][i][j] *= d[1][i + 1][j] + 1;
		d[3][i][j] *= d[3][i][j + 1] + 1;
	  }
	}

	// side length of the square
	bool flag = false;
	for (int len = 1; len <= n; ++len) {
	  int ans = 0;
	  // coordinate of top-left vertex
	  for (int i = 1; i <= n - len; ++i) {
		for (int j = 1; j <= n - len; ++j) {
		  int x = i + len, y = j + len;
		  if (d[0][x][y] >= len && d[2][x][y] >= len && d[1][i][j] >= len &&
			  d[3][i][j] >= len)
			++ans;
		}
	  }
	  if (ans) {
		flag = true;
		printf("%d square (s) of size %d\n", ans, len);
	  }
	}
	if (!flag) puts("No completed squares can be found.");
  }

  return 0;
}
