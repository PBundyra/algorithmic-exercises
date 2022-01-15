#include <bits/stdc++.h>

using namespace std;
int n, m, k;

// weight, key;
typedef pair<int, int> node_t;

// no_left_vertices
vector<int> no_vertices;
vector<node_t> nodes;
map<int, set<int>> vertices;
priority_queue<node_t, vector<node_t>, greater<>> que;


template<typename T>
void print_queue(T q) { // NB: pass by value so the print uses a copy
    while (!q.empty()) {
        std::cout << q.top().first << " " << q.top().second << ' ' <<
                  no_vertices.at(q.top().second) << '\n';
        q.pop();
    }
    std::cout << '\n';
}

void input() {
    cin >> n >> m >> k;

    int weight;
    int id = 1;
    node_t guard = {0, 0};
    nodes.push_back(guard);
    vertices.emplace(0, set<int>());
    no_vertices.push_back(0);

    for (int i = 0; i < n; ++i) {
        cin >> weight;
        node_t node = {weight, id};
        nodes.push_back(node);
        vertices.emplace(id, set<int>());
        no_vertices.push_back(0);
        id++;
    }

    int n1, n2;
    for (int i = 0; i < m; ++i) {
        cin >> n1 >> n2;
        no_vertices.at(n1)++;
        vertices.at(n2).emplace(n1);
    }

    for (auto &node: nodes) {
        if (no_vertices.at(node.second) == 0 && node.second != 0) {
            que.push(node);
        }
    }
}

void exec() {
    int max = 0;
    for (int i = 0; i < k; ++i) {
        node_t v = que.top();
        que.pop();
        if (v.first > max)
            max = v.first;
        for (auto &w: vertices.at(v.second)) {
            no_vertices.at(w)--;
            if (no_vertices.at(w) == 0)
                que.push(nodes.at(w));
        }
    }
    cout << max << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    exec();
    return 0;
}