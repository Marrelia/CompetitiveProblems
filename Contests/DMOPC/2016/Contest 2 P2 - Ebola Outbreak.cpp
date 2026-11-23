#include <iostream>
#include <vector>

const int N = 1e5 + 9;

int n, m;

std::vector< int > ans;

// disjoint set
// fa(i) is the father of point i
int fa[N];

// find the root of the tree that x is in
int find(int x) {
  if (fa[x] != x)
    return fa[x] = find(fa[x]);
  return x;
}

// Merge two tree with root x and root y
void merge(int x, int y) {
  fa[y] = x;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin >> n >> m;

  // initialize the disjoint set
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
  }

  for (int i = 1; i <= m; ++i) {
    int k;
    std::cin >> k;
    // first student in each class
    int x;
    std::cin >> x;
    // the root of x
    int rt_x = find(x);
    for (int j = 2; j <= k; ++j) {
      int y;
      std::cin >> y;
      // rt_x and find(y) cannot swap
      // if they swap we need to recalculate the root of x
      merge(rt_x, find(y));
    }
  }

  int rt_1 = find(1);
  for (int i = 1; i <= n; ++i) {
    if (rt_1 == find(i))
      ans.push_back(i);
  }
  std::cout << ans.size() << "\n";
  for (const auto &student : ans) {
    std::cout << student << " ";
  }
  return 0;
}