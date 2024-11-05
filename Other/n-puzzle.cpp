// First line input the side length of the puzzle (3, 4, 5)
// second line input the starting state of the puzzle
// the space would represent by 'x'
/*
 * For example,
 * 6 2 4
 * 5 8 1
 * 3 7 x
 *
 * would input as
 * 6 2 4 5 8 1 3 7 x
 *
 * output the operation
 * u indicates to swap the space with the block above it, l is the block left to it, and so on
 */

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <string>

std::string start;

int n;
std::unordered_map<std::string, int> dist;
std::unordered_map<std::string, std::pair<char, std::string> > prev;

int f(const std::string &stat) {
  int res = 0;
  for (int i = 0; i < n * n * 4; ++i) {
	if (stat[i] == 'x' || stat[i] == ' ') continue;
	int t = 0, len = 0;
	while (stat[i + len] != ' ') {
	  t = (t << 3) + (t << 1) + stat[i + len] - '0';
	  ++len;
	}
	--t;
	res += std::abs(i / 4 / n - t / n) + std::abs((i / 4) % n - t % n);
	i += len;
  }
  return res;
}

bool check() {
  int count = 0;
  int pos = 0;
  for (int i = 0; i < n * n * 4; ++i) {
	if (start[i] == 'x' || start[i] == ' ') {
	  if (start[i] == 'x') pos = i;
	  continue;
	}
	int len1 = 0, res1 = 0;
	while (start[i + len1] != ' ') {
	  res1 = (res1 << 3) + (res1 << 1) + start[i + len1] - '0';
	  ++len1;
	}
	for (int j = 0; j < i; ++j) {
	  if (start[j] == 'x' || start[j] == ' ') continue;
	  int len2 = 0, res2 = 0;
	  while (start[j + len2] != ' ') {
		res2 = (res2 << 3) + (res2 << 1) + start[j + len2] - '0';
		++len2;
	  }
	  count += res1 < res2;
	  j += len2;
	}
	i += len1;
  }
  if (!(n & 1)) count += n - 1 - pos / 4 / n;
  return !(count & 1);
}

std::pair<int, std::string> astar() {
  if (!check()) return std::make_pair(-1, std::string());

  std::string s = {}, tmp;
  for (int i = 1; i < n * n; ++i) {
	std::string tmpS = std::to_string(i);
	s += tmpS + ' ';
	for (int k = 0; k < 3 - tmpS.length(); ++k) s += ' ';
  }
  s += "x   ";

  std::string d1 = "uldr";
  const int d2[] = {-n * 4, -4, n * 4, 4};

  std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string> >, std::greater<> > q;
  q.emplace(f(start), start);
  dist[start] = 0;
  while (!q.empty()) {
	auto [fst, snd] = q.top(); q.pop();
	if (snd == s) break;
	int idx = -1;
	for (int i = 0; i < n * n * 4; ++i) if (snd[i] == 'x') {
		idx = i;
		break;
	  }

	for (int i = 0; i < 4; ++i) {
	  const int vx = idx + d2[i];
	  if ( ((i & 1) && !(vx >= (idx / 4 / n) * 4 * n && vx < (idx / 4 / n + 1) * 4 * n)) || vx > n * n * 4 - 1 || vx < 0) continue;
	  std::string stat = snd;
	  for (int k = 0; k < 4; ++k)
		std::swap(stat[idx + k], stat[vx + k]);
	  if (!dist.count(stat) || dist[stat] > dist[snd] + 1) {
		dist[stat] = dist[snd] + 1;
		prev[stat] = std::make_pair(d1[i], snd);
		q.emplace(dist[stat] + f(stat), stat);
	  }
	}
  }

  std::pair<int, std::string> res;
  res.first = dist[s];

  while (prev.contains(s)) {
	tmp += prev[s].first;
	s = prev[s].second;
  }
  std::ranges::reverse(tmp);
  res.second = tmp;
  return res;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n * n; ++i) {
	std::string s;
	std::cin >> s;
	if (s[0] == 'x') start += "x";
	else start += s;
	for (int k = 0; k < 4 - s.length(); ++k) start += ' ';
  }

  if (const auto [fst, snd] = astar(); fst == -1) puts("unsolvable");
  else std::cout << snd << std::endl;
  return 0;
}