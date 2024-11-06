/*
 * A tool to balance the chemical Equation
 * You would input the chemical equation with their chemical formula, separate by +, and reactants and products are seprated by ->
 * Example:
 * 6 CO2 + 6 H2O -> 6 O2 + 1 C6H12O6
 *
 * Output will be the coefficients for each chemical substances
 * For above example:
 * 6 6 6 1
 *
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstring>
#include <stack>

const double eps = 1e-6;

int a[2][150][300];
int len[2];

int mtx[300][300];

int cheNameToNum_cnt;
std::map<std::string, int> cheNameToNum;
std::string numToCheName[300];

int gcd(int, int);

// add a element name to map
int addStringToMap(const std::string &);

// process a chemical formula
void process(int, int, std::string);

// read the input
void read();

// convert the input to matrix
void convertToMatrix();

// solve the equation set
std::vector<int> solve(int, int);

int main() {
  read();
  convertToMatrix();
  if (const std::vector<int> ans = solve(cheNameToNum_cnt, len[0] + len[1]); ans[0] == -1) {
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

int addStringToMap(const std::string &x) {
  if (cheNameToNum.contains(x)) return cheNameToNum[x];
  cheNameToNum[x] = ++cheNameToNum_cnt;
  numToCheName[cheNameToNum_cnt] = x;
  return cheNameToNum_cnt;
}

void process(const int x, const int y, std::string str) {
  std::stack<char> stk;
  // num of each element
  int dep = 1, cnt[300][300] = {};
  stk.push('(');
  str.push_back(')');
  for (int i = 0; i < str.length(); ++i) {
    if (str[i] == ')') {
      std::string tmp;
      while (stk.top() != '(') {
        tmp += stk.top();
        stk.pop();
      }
      stk.pop();
      std::ranges::reverse(tmp);
      for (int k = 0; k < tmp.length();) {
        std::string cur;
        int num = 0;
        cur += tmp[k++];
        while (islower(tmp[k])) cur += tmp[k++];
        while (isdigit(tmp[k])) num = (num << 3) + (num << 1) + tmp[k++] - '0';
        if (!num) ++num;
        cnt[dep][addStringToMap(cur)] += num;
      }
      int num = 0;
      ++i;
      while (isdigit(str[i])) num = (num << 3) + (num << 1) + str[i++] - '0';
      --i;
      if (!num) ++num, ++i;
      for (int k = 1; k <= cheNameToNum_cnt; ++k) {
        cnt[dep - 1][k] += cnt[dep][k] * num;
      }
      --dep;
    } else {
      stk.push(str[i]);
    }
    if (str[i] == '(') {
      ++dep;
      memset(cnt[dep], 0, sizeof cnt[dep]);
    }
  }

  for (int i = 1; i <= cheNameToNum_cnt; ++i) {
    a[x][y][i] += cnt[1][i];
  }
}

void read() {
  std::string Input;
  std::getline(std::cin, Input);
  int w = 0;
  int cnt = 1;
  std::string cur;
  for (int i = 0; i < Input.size();) {
    if (Input[i] == '+') {
      process(w, cnt, cur);
      cur.clear();
      ++cnt;
      ++i;
    } else if ((Input[i] == '-' && Input[i  + 1] == '>') || (Input[i] == '→')) {
      process(w, cnt, cur);
      cur.clear();
      if (Input[i] == '→') ++i;
      else i += 2;
      len[w] = cnt;
      cnt = 1;
      w = 1;
    } else {
      if (!isalpha(Input[i]) && !isdigit(Input[i]) && Input[i] != '(' && Input[i] != ')') {
        ++i;
        continue;
      }
      cur += Input[i++];
    }
  }
  process(w, cnt, cur);
  cur.clear();
  len[w] = cnt;
  cnt = 1;
  /*for (int i = 0; i <= 1; ++i) {
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
    for (int i = 1; i <= n; ++i) {
      if (mtx[i][j] == 0 || i == curRow) continue;
      int tmp = mtx[curRow][j] * mtx[i][j] / gcd(mtx[curRow][j], mtx[i][j]);
      int t1 = tmp / mtx[curRow][j], t2 = tmp / mtx[i][j];
      for (int k = 1; k <= m; ++k) {
        mtx[i][k] = mtx[i][k] * t2 - mtx[curRow][k] * t1;
      }
    }
    ++curRow;
  }
  if (curRow < m) return std::vector<int>{-1};
  std::vector<int> ans(m + 1);

  int t = m - 1;
  while (mtx[n][m - 1] == 0) --n;

  ans[m] = 1;
  for (int i = n; i >= 1 && t >= 1; --i, --t) {
    if (mtx[i][t] < 0) mtx[i][t] = -mtx[i][t], mtx[i][m] = -mtx[i][m];
    int tmp = std::abs(gcd(mtx[i][t], mtx[i][m]));
    mtx[i][t] /= tmp; mtx[i][m] /= tmp;
    ans[m] = ans[m] * mtx[i][t] / gcd(ans[m], mtx[i][t]);
  }

  t = m - 1;
  for (int i = n; i >= 1 && t >= 1; --i, --t) {
    ans[t] = ans[m] * (-mtx[i][m]) / mtx[i][t];
  }

  return ans;
}
