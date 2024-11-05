/*
 * A tool to balance the chemical Equation
 * You would input the chemical equation with their chemical formula, separate by +, and reactants and products are seprated by ->
 * Example:
 * CO2 + H2O -> O2 + C6H12O6
 *
 * Output will be the coefficients for each chemical substances
 * For above example:
 * 6 6 6 1
 *
 * No brackets support yet, may add later on :D
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>

int a[2][150][300];
int len[2];

int mtx[300][300];

int cheNameToNum_cnt;
std::map<std::string, int> cheNameToNum;
std::string numToCheName[300];

int addStringToMap(const std::string&);
void read();
void convertToMatrix();
std::vector<int> solve(int, int);

int main() {
  read();
  convertToMatrix();
  std::vector<int> ans = solve(cheNameToNum_cnt, len[0] + len[1]);
  if (ans[0] == -1) {
	puts("No Solution");
  } else {
	for (int i = 1; i <= len[0] + len[1]; ++i)
	  printf("%d ", ans[i]);
  }
  return 0;
}

int gcd(int x, int y) {
  while (y) {
	std::swap(x, y);
	y %= x;
  }
  return x;
}

int addStringToMap(const std::string& x) {
  if (cheNameToNum.contains(x)) return cheNameToNum[x];
  cheNameToNum[x] = ++cheNameToNum_cnt;
  numToCheName[cheNameToNum_cnt] = x;
  return cheNameToNum_cnt;
}

void read() {
  std::string Input;
  std::getline(std::cin, Input);
  int w = 0; int cnt = 1; std::string cur; int num = 0;
  for (int i = 0; i < Input.size();) {
	if (Input[i] == '+') {
	  ++cnt;
	  ++i;
	} else if (Input[i] == '-' && Input[i + 1] == '>') {
	  i += 2;
	  len[w] = cnt;
	  cnt = 1;
	  w = 1;
	} else {
	  if (!isalpha(Input[i])) {
		++i;
		continue;
	  }
	  cur += Input[i++];
	  while (Input[i] <= 'z' && Input[i] >= 'a') cur += Input[i++];
	  while (Input[i] <= '9' && Input[i] >= '0') num = (num << 3) + (num << 1) + Input[i++] - '0';
	  if (!num) ++num;
	  a[w][cnt][addStringToMap(cur)] += num;
	  cur.clear();
	  num = 0;
	}
  }
  len[w] = cnt;
/*  cnt = 1;
  for (int i = 0; i <= 1; ++i) {
    for (int j = 1; j <= len[i]; ++j) {
	  for (int k = 1; k <= cheNameToNum_cnt; ++k) {
		std::cout << "(" << numToCheName[k] << "," << a[i][j][k] << ") ";
	  }
	  puts("");
	}
	puts("");
  }*/
}

void convertToMatrix() {
  for (int i = 0; i < 2; ++i) {
	for (int j = 1; j <= len[i]; ++j) {
	  for (int k = 1; k <= cheNameToNum_cnt; ++k) {
        if (i == 0) {
		  mtx[k][j] = a[i][j][k];
		} else {
		  mtx[k][j + len[0]] = -a[i][j][k];
		}
	  }
	}
  }
}

std::vector<int> solve(int n, int m) {
  int curRow = 1;
  for (int j = 1; j < m; ++j) {
	int t = -1;
	for (int i = curRow; i <= n; ++i) {
	  if (mtx[i][j] != 0) {
		t = i;
		break;
	  }
	}
	if (t == -1) continue;
    for (int i = 1; i <= m; ++i) std::swap(mtx[t][i], mtx[curRow][i]);
	for (int i = curRow + 1; i <= n; ++i) {
	  if (mtx[i][j] == 0) continue;
	  int tmp = mtx[curRow][j] * mtx[i][j] / gcd(mtx[curRow][j], mtx[i][j]);
	  int t1 = tmp / mtx[curRow][j], t2 = tmp / mtx[i][j];
	  for (int k = j; k <= m; ++k) {
		mtx[i][k] = mtx[i][k] * t2 - mtx[curRow][k] * t1;
	  }
	}
	++curRow;
  }
  if (curRow < m) return std::vector<int>{-1};
  std::vector<int> ans(m + 1);

  int t = m;
  while (mtx[n][m - 1] == 0) --n;
  int tmp = gcd(std::abs(mtx[n][m - 1]), std::abs(mtx[n][m]));
  ans[t--] = std::abs(mtx[n][m - 1]) / tmp;
  ans[t--] = std::abs(mtx[n][m]) / tmp;
  for (int i = n - 1; i >= 1 && t >= 1; --i, --t) {
	int res = 0;
	for (int j = t + 1; j <= m; ++j) {
	  res += mtx[i][j] * ans[j];
	}
	if (res != 0) {
	  ans[t] = (-res) / mtx[i][t];
	} else {
	  ans[t] = 1;
	}
  }
  return ans;
}