#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#define fi first
#define se second

typedef long long ll;
typedef std::pair<int, int> pii;

constexpr int MAX_N = 1e6 + 9, MAX_M = 3e2 + 9;

constexpr ll INF = 1e15;

constexpr ll MOD = 998244353;

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

int l = 2;
int cnt = 500;
std::vector<int> a;
bool check() {
  if (a.size() % 3 != 0 || a.size() < l * 3)
    return false;
  for (int i = 0, j = a.size() / 3, k = a.size() / 3 * 2; k < a.size();
       ++i, ++j, ++k)
    if (a[i] != a[j] || a[j] != a[k] || a[i] != a[k])
      return false;
  return true;
}

int flip() {
  std::cout << "? flip\n";
  std::cout.flush();
  int s;
  std::cin >> s;
  --cnt;
  return s;
}

int right() {
  std::cout << "? right\n";
  std::cout.flush();
  int s;
  std::cin >> s;
  --cnt;
  return s;
}

int left() {
  std::cout << "? left\n";
  std::cout.flush();
  int s;
  std::cin >> s;
  --cnt;
  return s;
}

void print(int n) {
  std::cout << "! " << n << '\n';
  std::cout.flush();
  exit(0);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int s;
  std::cin >> s;
  while (cnt > 100) {
    if (s)
      s = flip();
    int i = 1;
    s = right();
    while (s == 1 && cnt > 100) {
      s = right();
      ++i;
    }
    if (cnt <= 100)
      break;
    s = flip();
    if (cnt <= 100)
      break;
    for (int j = 1; j <= i && cnt > 100; ++j)
      s = left();
    if (cnt <= 100)
      break;
    if (s == 1)
      print(i);
    l = i + 1;
  }

  for (; cnt > 0;) {
    s = right();
    if (cnt > 0 && rnd() & 1) {
      s = flip();
    }
  }

  a.push_back(s);
  while (!check()) {
    s = left();
    a.push_back(s);
  }

  print(a.size() / 3);

  return 0;
}

/*
Idea: use O(n^2) idea first
after we know a lower bound
use another idea
*/