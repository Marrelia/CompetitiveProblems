#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#define f first
#define s second

using namespace std;

typedef pair< int, int > PII;

const int N = 1e3 + 9;

int n, m;
int map[N][N];
unordered_map< int, vector< PII > > pts;
bool vis[N][N];

bool dfs(int x, int y) {
  if (x == n && y == m)
    return true;
  if (!pts.count(map[x][y]) || vis[x][y])
    return false;
  vis[x][y] = true;
  for (const auto &pt : pts[map[x][y]]) {
    if (dfs(pt.f, pt.s))
      return true;
  }

  return false;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      cin >> map[i][j];
      if (!pts.count(i * j))
        pts[i * j] = vector< PII >();
      pts[i * j].emplace_back(i, j);
    }

  cout << (dfs(1, 1) ? "yes" : "no");
  return 0;
}