//
// Created by BarretShen on 11/4/2024.
//
#include <iostream>
#include <unordered_map>

int n;
std::unordered_map<int, int> q;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
	int x;
	scanf("%d", &x);
	if (!q.count(x)) printf("-1 ");
	else printf("%d ", q[x]);
	q[x] = i;
  }
  return 0;
}