#include <iostream>
#include <stack>

int main() {
  int T;
  std::cin >> T;
  while (T--) {
    std::string s1, s2;
    std::cin >> s1 >> s2;
    std::stack< char > stk;
    int n = s1.length(), pt = 0;
    for (int i = 0; i < n; ++i) {
      char ch = s1[i];
      while (stk.size() >= 1 && stk.top() == ch && ch != 'z') {
        ++ch;
        stk.pop();
      }
      stk.push(ch);
      if (stk.size() == 1 && stk.top() == s2[pt])
        ++pt, stk.pop();
    }
    if (!stk.empty() || pt < s2.length())
      puts("NO");
    else
      puts("YES");
  }
  return 0;
}