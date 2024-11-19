#include <iostream>
#include <set>

typedef unsigned long long ULL;
typedef long long LL;

const int N = 4e5 + 9;
const ULL P1 = 131;
const LL mod = 1e9 + 7;
const LL P2 = 13131;

int cnt[26];
int ACnt[26];
ULL h1[N];
LL h2[N];
ULL p1[N];
LL p2[N];
std::string a, b;

int ans;
std::set< std::pair< ULL, LL > > sta;

bool check() {
  for (int i = 0; i < 26; ++i) {
    if (cnt[i] != ACnt[i])
      return false;
  }
  return true;
}

LL m(LL x) {
  return (x % mod + mod) % mod;
}

std::pair< ULL, LL > get(const int l, const int r) {
  return {h1[r] - h1[l - 1] * p1[r - l + 1],
          m(h2[r] - m(h2[l - 1] * p2[r - l + 1]))};
}

int main() {
  std::cin >> a >> b;
  const int lenA = a.length(), lenB = b.length();
  if (lenB < lenA) {
    puts("0");
    return 0;
  }

  p1[0] = p2[0] = 1;
  h1[0] = h2[0] = b[0] - 'a' + 1;
  for (int i = 1; i < lenB; ++i) {
    h1[i] = (h1[i - 1] * P1) + b[i] - 'a' + 1;
    p1[i] = p1[i - 1] * P1;
    h2[i] = (m(h2[i - 1] * P2) + b[i] - 'a' + 1) % mod;
    p2[i] = (p2[i - 1] * P2) % mod;
  }
  p1[lenB] = p1[lenB - 1] * P1;
  p2[lenB] = (p2[lenB - 1] * P2) % mod;

  for (int i = 0; i < lenA - 1; ++i) {
    ++cnt[b[i] - 'a'];
    ++ACnt[a[i] - 'a'];
  }
  ++ACnt[a[lenA - 1] - 'a'];

  for (int i = lenA - 1; i < lenB; ++i) {
    if (i - lenA >= 0) {
      --cnt[b[i - lenA] - 'a'];
    }
    ++cnt[b[i] - 'a'];
    if (check()) {
      sta.insert(get(i - lenA + 1, i));
    }
  }
  printf("%zu\n", sta.size());
  return 0;
}