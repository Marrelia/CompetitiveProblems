#include <iostream>

const int N = 5e5 + 9, M = 30;

int trie[N][26], tot;
int maxPos[M], pt;
int word[N];
char opr[N * 3]; int cnt;

void add(std::string& s) {
  int u = 0;
  for (int i = 0; i < s.length(); ++i) {
	int ch = s[i] - 'a';
	if (!trie[u][ch]) trie[u][ch] = ++tot;
	u = trie[u][ch];
	maxPos[i] = u;
  }
  ++word[u];
}

std::string maxS;

void dfs(int u) {
  for (int i = 0; i < word[u]; ++i) opr[++cnt] = 'P';
  int tmp = -1;
  for (int i = 0; i < 26; ++i) {
	if (!trie[u][i]) continue;
	if (trie[u][i] == maxPos[pt]) {
	  tmp = i; ++pt;
	  continue;
	}
	opr[++cnt] = char(i + 'a');
	dfs(trie[u][i]);
	opr[++cnt] = '-';
  }
  if (tmp != -1) {
	opr[++cnt] = char(tmp + 'a');
	dfs(trie[u][tmp]);
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
	std::string s;
	std::cin >> s;
	if (s.length() > maxS.length()) maxS = s;
	add(s);
  }
  add(maxS);
  --word[maxPos[maxS.length() - 1]];

  dfs(0);
  printf("%d\n", cnt);
  for (int i = 1; i <= cnt; ++i) printf("%c\n", opr[i]);
  return 0;
}