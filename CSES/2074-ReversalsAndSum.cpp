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

// using a single array to implement, as we guarenteed there's only up to 60
// intervals also vector's constant is very small
std::vector<Node> odt;

int n, q;
ll a[MAX_N], s[MAX_N], buf[MAX_N];

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
      std::reverse(a + pl, a + pr + 1);
    memcpy(buf + pt, a + pl, len * sizeof(ll));
    pt += len;
  }
  memcpy(a, buf, (n + 2) * sizeof(ll));
  memset(buf, 0, (n + 2) * sizeof(ll));
  for (int i = 1; i <= n; ++i)
    s[i] = s[i - 1] + a[i];
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

// reverse time complexity: O(T)
void reverse(int a, int b) {
  int itl = split(a), itr = split(b + 1);
  std::reverse(odt.begin() + itl, odt.begin() + itr);
  for (; itl != itr; ++itl)
    odt[itl].rev ^= 1;
}

ll get_sum(int a, int b) {
  int itl = split(a), itr = split(b + 1);
  ll res = 0;
  for (; itl != itr; ++itl)
    res += s[odt[itl].pr] - s[odt[itl].pl - 1];
  return res;
}

int main() {
  scanf("%d%d", &n, &q);

  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
    s[i] = s[i - 1] + a[i];
  }

  // set T = sqrt(n / 6)
  int T = ceil(sqrt(n / 6.));

  odt.push_back({1, n + 1, false});

  while (q--) {
    int opr, a, b;
    scanf("%d%d%d", &opr, &a, &b);

    if (opr == 1)
      reverse(a, b);
    else
      printf("%lld\n", get_sum(a, b));

    // rebuild if more than T intervals
    if (odt.size() > T)
      rebuild();
  }

  return 0;
}

/*

Similar idea with cses2073, but just one more operation
and also record prefix sum

*/
