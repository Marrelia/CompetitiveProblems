#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>

#define fi first
#define se second

using std::cin;
using std::cout;

typedef long long ll;
typedef std::pair<int, int> pii;
typedef std::pair<ll, int> pli;

constexpr int MAX_N = 1e5 + 9, MAX_M = 1e6 + 9;

constexpr ll INF = 1e18;

constexpr ll MOD = 998244353;

const double Pi = acos(-1);

// Chtholly Tree
// ciallo (∠·ω )⌒★
struct Node {
  int l, r;
  mutable ll v;

  Node(const int &il, const int &ir, const ll &iv) : l(il), r(ir), v(iv) {}

  bool operator<(const Node &o) const { return l < o.l; }
};
std::set<Node> odt;

// quick power a^b mod p
ll qpow(ll a, ll b, ll p) {
  ll res = 1 % p;
  a %= p;
  while (b) {
    if (b & 1)
      res = res * a % p;
    a = a * a % p;
    b >>= 1;
  }
  return res;
}

// Split operation
auto split(int x) {
  auto it = odt.lower_bound(Node(x, 0, 0));
  if (it != odt.end() && it->l == x)
    return it;
  --it;
  int l = it->l, r = it->r;
  ll v = it->v;
  odt.erase(it);
  odt.insert(Node(l, x - 1, v));
  return odt.insert(Node(x, r, v)).first;
}

// Assign [l,r] to v
void assign(int l, int r, ll v) {
  auto itr = split(r + 1), itl = split(l);
  odt.erase(itl, itr);
  odt.insert(Node(l, r, v));
}

// add [l,r] by v
void add(int l, int r, ll v) {
  auto itr = split(r + 1), itl = split(l);
  for (; itl != itr; ++itl)
    itl->v += v;
}

// find kth minimum number in [l,r]
ll find(int l, int r, int k) {
  auto itr = split(r + 1), itl = split(l);
  std::vector<std::pair<ll, int>> tmp;
  for (; itl != itr; ++itl)
    tmp.push_back({itl->v, itl->r - itl->l + 1});

  // sort by value
  std::sort(tmp.begin(), tmp.end());
  auto it = tmp.begin();

  // find until reach k is <= current size
  while (it != tmp.end() && k > it->se) {
    k -= it->se;
    ++it;
  }
  if (it != tmp.end())
    return it->fi;
  // if not find, return -1, which is not possible in this problem
  return -1;
}

// get the sum of powers
ll get_sum(int l, int r, ll x, ll y) {
  auto itr = split(r + 1), itl = split(l);
  ll res = 0;
  for (; itl != itr; ++itl)
    res = (res + qpow(itl->v, x, y) * (itl->r - itl->l + 1)) % y;
  return res;
}

int n, m;
ll seed, vmax;
ll a[MAX_N];

// These rnd are from the problem statement
ll rnd() {
  ll ret = seed;
  seed = (seed * 7 + 13) % 1000000007;
  return ret;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> n >> m >> seed >> vmax;
  for (int i = 1; i <= n; ++i)
    a[i] = (rnd() % vmax) + 1;

  // initialize chtholly tree
  // use n+1 = -1 so that a[n] != a[n + 1]
  a[n + 1] = -1;
  for (int i = 1, l = 1; i <= n + 1; ++i) {
    if (a[i] != a[l])
      odt.insert(Node(l, i - 1, a[l])), l = i;
  }
  odt.insert({n + 1, n + 1, -1});

  for (int i = 1; i <= m; ++i) {
    int op = (rnd() % 4) + 1;
    int l = (rnd() % n) + 1;
    int r = (rnd() % n) + 1;
    if (l > r)
      std::swap(l, r);

    ll x, y;
    if (op == 3)
      x = (rnd() % (r - l + 1)) + 1;
    else
      x = (rnd() % vmax) + 1;
    if (op == 4)
      y = (rnd() % vmax) + 1;

    // operations
    if (op == 1)
      add(l, r, x);
    else if (op == 2)
      assign(l, r, x);
    else if (op == 3)
      std::cout << find(l, r, x) << '\n';
    else
      std::cout << get_sum(l, r, x, y) << '\n';
  }
  return 0;
}
