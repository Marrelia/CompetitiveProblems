#include <iostream>

typedef long long ll;

constexpr int max_n = 1e5 + 9;

int n;
int a[max_n];
int b[max_n];
ll inv;

void merge_sort(int l, int r) {
  if (l == r)
    return;
  int mid = (l + r) >> 1;
  merge_sort(l, mid);
  merge_sort(mid + 1, r);

  // merge
  int pt1 = l, pt2 = mid + 1, j = l;
  while (pt1 <= mid && pt2 <= r) {
    if (a[pt1] <= a[pt2]) {
      inv += pt2 - mid - 1;
      b[j++] = a[pt1++];
    } else {
      b[j++] = a[pt2++];
    }
  }
  while (pt1 <= mid) {
    b[j++] = a[pt1++];
    inv += r - mid;
  }
  while (pt2 <= r)
    b[j++] = a[pt2++];
  for (int i = l; i <= r; ++i)
    a[i] = b[i];
}

int main() {
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);

  merge_sort(1, n);

  // cout << inv << '\n';
  printf("%.2lf\n", 1.0 * inv / n + 1);

  return 0;
}