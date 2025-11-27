#include <iostream>
#include <algorithm>

typedef long long ll;

using std::cin;
using std::cout;

int cnt[3];
int dsp[3][3];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::string s;
  cin >> s;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == 'L') ++cnt[0];
    else if (s[i] == 'M') ++cnt[1];
    else ++cnt[2];
  }
  
  for (int i = 0; i < cnt[0]; ++i) {
    if (s[i] == 'M') ++dsp[0][1];
    else if (s[i] == 'S') ++dsp[0][2];
  }
  for (int i = cnt[0]; i < cnt[1] + cnt[0]; ++i) {
    if (s[i] == 'L') ++dsp[1][0];
    else if (s[i] == 'S') ++dsp[1][2];
  }
  for (int i = cnt[1] + cnt[0]; i < s.length(); ++i) {
    if (s[i] == 'L') ++dsp[2][0];
    else if (s[i] == 'M') ++dsp[2][1];
  }
  int ans = dsp[0][1] + dsp[0][2] + std::max(dsp[2][1], dsp[1][2]);
  cout << ans << '\n';
  return 0;
}