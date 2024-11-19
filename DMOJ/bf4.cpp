#include <cstring>
#include <iostream>

const int N = 1e6 + 9;
const long long b = 131;
const long long mod = 1e9 + 7;

int len1, len2;
char s2[N], s1[N];
long long h2, h1[N], p;

void get_hash() {
  p = 1;
  for (int i = 1; i <= len2; ++i) {
    h2 = (((h2 * b) % mod) + s2[i]) % mod;
    p = (p * b) % mod;
  }

  for (int i = 1; i <= len1; ++i) {
    h1[i] = ((h1[i - 1] * b % mod) + s1[i]) % mod;
  }
}

long long Mod(long long x) {
  return ((x % mod) + mod) % mod;
}

int main() {
  scanf("%s%s", s1 + 1, s2 + 1);
  len1 = strlen(s1 + 1), len2 = strlen(s2 + 1);
  get_hash();
  for (int i = 1; i <= len1 - len2 + 1; ++i) {
    if (h2 == Mod(h1[i + len2 - 1] - h1[i - 1] * p)) {
      printf("%d\n", i - 1);
      return 0;
    }
  }
  puts("-1");
  return 0;
}