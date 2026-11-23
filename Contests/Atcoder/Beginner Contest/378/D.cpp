//
// Created by BarretShen on 11/4/2024.
//
#include <iostream>
#include <cstring>

const int N = 20;

int n, m, k;
char s[N][N];
bool vis[N][N];

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

long long dfs(int x, int y, int dep) {
  if (dep > k) return 1;
  long long res = 0;
  for (int i = 0; i < 4; ++i) {
	int vx = x + dx[i], vy = y + dy[i];
	if (vx < 1 || vx > n || vy < 1 || vy > m || s[vx][vy] == '#' || vis[vx][vy]) continue;
	vis[vx][vy] = true;
	res += dfs(vx, vy, dep + 1);
	vis[vx][vy] = false;
  }
  return res;
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; ++i) {
	scanf("%s", s[i] + 1);
  }

  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
	for (int j = 1; j <= m; ++j) {
	  if (s[i][j] == '#') continue;
	  vis[i][j] = true;
	  ans += dfs(i, j, 1);
	  vis[i][j] = false;
	}
  }
  printf("%lld\n", ans);
  return 0;
}