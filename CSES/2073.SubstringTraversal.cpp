#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

#define fi first
#define se second

typedef long long ll;
typedef std::pair<int, int> pii;
typedef std::pair<ll, int> pli;

constexpr int MAX_N = 2e5 + 9, MAX_M = 60;

constexpr ll INF = 1e15;

constexpr ll MOD = 1e9 + 9;

// [pl, pr]: position in the original string
struct Node {
  int pl, pr;
  bool rev;

  Node(int ipl, int ipr, bool irev) : pl(ipl), pr(ipr), rev(irev) {}
};

// using a single array to implement, as we guarenteed there's only up to T
// intervals
// also vector's constant is very small
std::vector<Node> odt;

int n, q;
char s[MAX_N], buf[MAX_N];

// rebuild the chtholly tree when the # of interval is greater than T
// similar idea with scapegoat tree
// rebuild time complexity: O(T + n)
void rebuild() {
  int pt = 1;
  for (const Node &i : odt) {
    int pl = i.pl, pr = i.pr;
    if (pl == n + 1)
      continue;
    if (pr == n + 1)
      --pr;
    int len = pr - pl + 1;
    if (i.rev)
      std::reverse(s + pl, s + pr + 1);
    memcpy(buf + pt, s + pl, len);
    pt += len;
  }
  memcpy(s, buf, n + 2);
  memset(buf, 0, n + 2);
  odt.clear();
  odt.push_back({1, n + 1, false});
}

// split time complexity: O(T)
int split(int x) {
  int it = 0;
  int l = 1;
  while (l + odt[it].pr - odt[it].pl < x)
    l += odt[it].pr - odt[it].pl + 1, ++it;
  if (l == x)
    return it;
  int pl = odt[it].pl, pr = odt[it].pr;
  if (odt[it].rev) {
    odt[it].pl = pr - (x - l) + 1;
    odt.insert(odt.begin() + it + 1, Node(pl, pr - x + l, true));
  } else {
    odt[it].pr = pl + x - l - 1;
    odt.insert(odt.begin() + it + 1, Node(pl + x - l, pr, false));
  }
  return it + 1;
}

int main() {
  scanf("%d%d%s", &n, &q, s + 1);

  // set T = sqrt(n / 6)
  int T = ceil(sqrt(n / 6.));

  odt.push_back({1, n + 1, false});

  while (q--) {
    int a, b;
    scanf("%d%d", &a, &b);
    // reverse time complexity: O(T)
    int itl = split(a), itr = split(b + 1);
    std::reverse(odt.begin() + itl, odt.begin() + itr);
    for (; itl != itr; ++itl)
      odt[itl].rev ^= 1;
    if (odt.size() > T)
      rebuild();
  }

  rebuild();

  puts(s + 1);

  return 0;
}

/*
  total time complexity O(3qT + mn/(2T)) >= O(m * sqrt((3/2) * n))
  when T = sqrt(n / 6)
*/