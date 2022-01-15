#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

namespace {
    void read_input(long long int &n, long long int &m,
                    vector<long long int> &items) {
        string s;
        getline(cin, s);
        n = atoi(s.c_str());
        getline(cin, s);
        stringstream ss(s);
        long long int input;
        while (ss >> input) {
            items.push_back(input);
        }
        getline(cin, s);
    }

    void preprocess(const long long int n, const vector<long long int> items,
                    vector<long long int> &sums,
                    vector<long long int> &l0, vector<long long int> &l1,
                    vector<long long int> &r0,
                    vector<long long int> &r1) {
        long long int temp = 0;
        for (long long int i = n - 1; i >= 0; --i) {
            temp += items[i];
            sums.push_back(temp);

            if (items[i] % 2 == 0) {
                r0.push_back(items[i]);
                r1.push_back(-1);
            } else {
                r0.push_back(-1);
                r1.push_back(items[i]);
            }
        }

        for (long long int i = 0; i < n; ++i) {
            if (items[i] % 2 == 0) {
                l0.push_back(items[i]);
                l1.push_back(-1);
            } else {
                l0.push_back(-1);
                l1.push_back(items[i]);
            }
        }

        reverse(sums.begin(), sums.end());
        reverse(r1.begin(), r1.end());
        reverse(r0.begin(), r0.end());

        for (long long int i = n - 2; i >= 0; --i) {
            if (r1[i] == -1 && r1[i + 1] > 0) r1[i] = r1[i + 1];
            if (r0[i] == -1 && r0[i + 1] > 0) r0[i] = r0[i + 1];
        }
        for (long long int i = 1; i < n; ++i) {
            if (l0[i] == -1 && l0[i - 1] > 0) l0[i] = l0[i - 1];
            if (l1[i] == -1 && l1[i - 1] > 0) l1[i] = l1[i - 1];
        }
    }

    void
    generate_output(const long long int n, const vector<long long int> items,
                    const vector<long long int> sums,
                    const vector<long long int> l0,
                    const vector<long long int> l1,
                    const vector<long long int> r0,
                    const vector<long long int> r1) {
        string s;
        while (getline(cin, s)) {
            long long int k = atoi(s.c_str()), res = -1;
//            cout << k << " res: ";
            if (sums[n - k] % 2 == 1) res = sums[n - k];
            else {
                long long int cand1 = -1, cand2 = -1;
                if (n != k && l0[n - k - 1] != -1 && r1[n - k] != -1)
                    cand1 = sums[n - k] + l0[n - k - 1] - r1[n - k];
                if (n != k && l1[n - k - 1] != -1 && r0[n - k] != -1)
                    cand2 = sums[n - k] + l1[n - k - 1] - r0[n - k];
                res = max(cand1, cand2);
            }
            cout << res << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long int n, m;
    vector<long long int> items, l0, l1, r0, r1, sums;
    read_input(n, m, items);
    preprocess(n, items, sums, l0, l1, r0, r1);
    generate_output(n, items, sums, l0, l1, r0, r1);

    return 0;
}

