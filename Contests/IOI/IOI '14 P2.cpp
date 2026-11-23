#include <algorithm>
#include <iostream>
#include <set>

#define fi first
#define se second

using std::cin;
using std::cout;

typedef long long ll;
typedef __int128 i128;
typedef std::pair<int, int> pii;
typedef std::pair<ll, int> pli;

constexpr int MAX_N = 2e6 + 9, MAX_M = 1e5 + 9;

constexpr ll INF = 1e15;

constexpr ll MOD = 1e6 + 3;

int n, q;

// Chtholly Tree (∠・ω< )⌒☆

// Node
// [l, r] intervals,
// v value
struct Node {
  int l;
  mutable int r, v;

  // initializer
  Node(const int &il, const int &ir, const int &iv) : l(il), r(ir), v(iv) {}

  // how to sort it in set
  bool operator<(const Node &A) const { return l < A.l; }
};

// use set to implement chtholly tree
std::set<Node> tr;

// split
auto split(int x) {
  auto it = tr.lower_bound(Node{x, 0, 0});
  if (it != tr.end() && it->l == x)
    return it;
  --it;
  int r = it->r;
  it->r = x - 1;
  return tr.emplace_hint(std::next(it), x, r, it->v);
}

// perform the operation based on opr
void perform(int l, int r, int opr, int k) {
  auto itr = split(r + 1), itl = split(l);

  auto pre_it = itl;
  if (itl != tr.begin())
    --pre_it;
  for (auto it = itl; it != itr;) {
    if (opr == 1)
      it->v = std::max(it->v, k);
    else
      it->v = std::min(it->v, k);
    // Merge it with the previous interval if they have same number
    // to decrease # of interval
    if (it != pre_it && pre_it->v == it->v) {
      pre_it->r = it->r;
      it = tr.erase(it);
    } else {
      pre_it = it;
      ++it;
    }
  }
  if (itr != tr.end() && itr->v == pre_it->v) {
    pre_it->r = itr->r;
    tr.erase(itr);
  }
}

void solve() {
  cin >> n >> q;
  tr.insert({1, n + 1, 0});
  while (q--) {
    int opr, l, r, k;
    cin >> opr >> l >> r >> k;
    perform(l + 1, r + 1, opr, k);
  }
  for (const auto &cur : tr) {
    for (int i = cur.l; i <= std::min(cur.r, n); ++i)
      cout << cur.v << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int num_cases = 1;
  // cin >> num_cases;
  while (num_cases--) {
    solve();
  }
}