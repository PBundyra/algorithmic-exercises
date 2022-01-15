#include <bits/stdc++.h>

using namespace std;

const int BASE = 41;
const int BASE2 = 37;
const int MAXN = 3 * 10e5 + 3;
const int MOD = 10007;
const int MOD2 = 7919;
int n, m;
string s;
int powers[MAXN];
int powers2[MAXN];
int h1[MAXN];
int h2[MAXN];

int mod(const int &a, const int &b) { return (a % b + b) % b; }

void calc_powers() {
    powers[0] = 1;
    for (int i = 1; i < n; ++i)
        powers[i] = mod(BASE * powers[i - 1], MOD);
    powers2[0] = 1;
    for (int i = 1; i < n; ++i)
        powers2[i] = mod(BASE2 * powers2[i - 1], MOD2);
}

int len(const int &a, const int &b) {
    assert(a <= b);
    return b - a + 1;
}

void calc_hashes() {
    h1[n - 1] = (int) s[n - 1];
    h1[n] = 0;
    for (int i = n - 2; i >= 0; --i)
        h1[i] = mod((int) s[i] + h1[i + 1] * BASE, MOD);
    h2[n - 1] = (int) s[n - 1];
    h2[n] = 0;
    for (int i = n - 2; i >= 0; --i)
        h2[i] = mod((int) s[i] + h2[i + 1] * BASE2, MOD2);
}

int get_hash(const int &i, const int &j) {
    assert(i <= j);
    int res = mod(h1[i] -
                  h1[j + 1] * powers[len(i, j)], MOD);
    assert(res >= 0);
    return res;
}

int get_hash2(const int &i, const int &j) {
    assert(i <= j);
    int res = mod(h2[i] -
                  h2[j + 1] * powers2[len(i, j)], MOD2);
    assert(res >= 0);
    return res;
}

int find_prefix_len(const int &a, const int &b, const int &c, const int &d) {
    int l = 0, r = min(len(a, b), len(c, d));


    while (l != r) {
        int mid = (l + r) / 2;

        if (get_hash(a, a + mid) == get_hash(c, c + mid) &&
            get_hash2(a, a + mid) == get_hash2(c, c + mid)) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return r;
}

void compare(const int &a, const int &b, const int &c, const int &d) {
    int prefix_len = find_prefix_len(a, b, c, d);

    if ((prefix_len == len(a, b) && prefix_len == len(c, d)))
        cout << "=\n";
    else if (prefix_len == len(a, b))
        cout << "<\n";
    else if (prefix_len == len(c, d))
        cout << ">\n";
    else if (s[a + prefix_len] < s[c + prefix_len])
        cout << "<\n";
    else
        cout << ">\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s;
    calc_powers();
    calc_hashes();
    int a, b, c, d;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c >> d;
        compare(--a, --b, --c, --d);
    }
    return 0;
}