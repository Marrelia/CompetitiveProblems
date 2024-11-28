#include <iostream>
#include <cstring>

const int N = 1e6 + 9;

int n;
int tot;
int trie[N][26];
int wordNum[N];

int add(const std::string& s) {
  int u = 0;
  int cnt = -1;
  for (int i = 0; i < s.length(); ++i) {
	int ch = s[i] - 'a';
	if (!trie[u][ch]) {
	  trie[u][ch] = ++tot;
	  if (cnt == -1)
		cnt = i + 1;
	}
	u = trie[u][ch];
  }
  if (cnt == -1) cnt = s.length();
  return cnt;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int Kase = 1; Kase <= T; ++Kase){
	memset(trie, 0, sizeof trie);
	tot = 0;
	scanf("%d", &n);
	int ans = 0;
	while (n--) {
	  std::string s;
	  std::cin >> s;
	  ans += add(s);
	}
	printf("Case #%d: %d\n", Kase, ans);
  }
  return 0;
}