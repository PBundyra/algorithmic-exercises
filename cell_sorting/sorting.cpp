#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    unsigned long long res;
    if (n == 1) res = 1;
    else {
        int s[n];
        int l[n][n], r[n][n];
        for (int k = 0; k < n; ++k) {
            cin >> s[k];
        }

        for (int diff = 0; diff < n; ++diff) {
            for (int i = 0; i < n; ++i) {
                int j = i + diff;
                if (j >= n) continue;
                else if (j == i) {
                    l[i][j] = 1;
                    r[i][j] = 1;
                } else if (j - i == 1) {
                    l[i][j] = (s[i] < s[i + 1]);
                    r[i][j] = (s[j - 1] < s[j]);
                } else if (j - i >= 2) {
                    l[i][j] = ((s[i] < s[i + 1]) * l[i + 1][j] +
                               (s[i] < s[j]) * r[i + 1][j]) % 1000000000;
                    r[i][j] = ((s[i] < s[j]) * l[i][j - 1] +
                               (s[j - 1] < s[j]) * r[i][j - 1]) % 1000000000;
                }
            }
        }

        res = l[0][n - 1] % 1000000000;
        res += r[0][n - 1] % 1000000000;
        res = res % 1000000000;
    }
    cout << res << '\n';
    return 0;
}