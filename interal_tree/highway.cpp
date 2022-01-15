#include <bits/stdc++.h>

using namespace std;

class Node {
public:
    int white_cnt; // how many whites nodes in subtrees
    char color; // C(black) B(white) M(mixed)
    int l, r; // node's interval
};

class Highway {
public:
    vector <Node> tree;
    int size;

    Highway(const int &n, const Node &init_node)
            : tree(n, init_node), size(n) {
        add_intervals(1, 1, tree.size() / 2);
    }

    void add_intervals(const int &v, const int &l, const int &r) {
        if (v >= size) return;
        tree[v].l = l;
        tree[v].r = r;
        if (v < size / 2) {
            add_intervals(2 * v, l, (l + r) / 2);
            add_intervals(2 * v + 1, (l + r) / 2 + 1, r);
        }
    }

    void update(const int &v, const int &a, const int &b, const char &c) {
        if (tree[v].r < a or tree[v].l > b) return;

        else if (tree[v].l >= a and tree[v].r <= b) {
            tree[v].color = c;
            tree[v].white_cnt = (c == 'B') ? tree[v].r + 1 - tree[v].l
                                           : 0;
        } else {
            if (tree[v].color != 'M') push_down(v);

            update(2 * v, a, b, c);
            update(2 * v + 1, a, b, c);

            if (tree[2 * v].color == tree[2 * v + 1].color and
                tree[2 * v].color != 'M')
                tree[v].color = tree[2 * v].color;
            else
                tree[v].color = 'M';

            tree[v].white_cnt =
                    tree[2 * v].white_cnt + tree[2 * v + 1].white_cnt;
        }
    }

    void push_down(const int &v) {
        if (v >= size / 2) return;

        tree[2 * v].color = tree[v].color;
        tree[2 * v + 1].color = tree[v].color;

        if (tree[v].color == 'B') {
            const int val = tree[v].white_cnt / 2;
            tree[2 * v].white_cnt = val;
            tree[2 * v + 1].white_cnt = val;
        } else {
            tree[2 * v].white_cnt = 0;
            tree[2 * v + 1].white_cnt = 0;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, l, r;
    char c;
    cin >> n >> m;
    int next_n = pow(2, ceil(log(n) / log(2)));
    Node init_node;
    init_node.color = 'C';
    init_node.white_cnt = 0;
    Highway highway(2 * next_n, init_node);
    for (int i = 0; i < m; ++i) {
        cin >> l >> r >> c;
        highway.update(1, l, r, c);
        cout << highway.tree[1].white_cnt << "\n";
    }
    return 0;
}