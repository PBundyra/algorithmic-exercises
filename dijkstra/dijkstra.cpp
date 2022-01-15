#include <bits/stdc++.h>

using namespace std;

int MAXN = 1e5 * 2 + 1;
int INF = 1e9 + 1;
int n;

struct island {
    int ind;
    int x;
    int y;
};

vector<vector<int>> graph(MAXN);
vector<island> islands(MAXN), by_x, by_y;

auto calc_dist(const int &u, const int &v) {
    return min(abs(islands[u].x - islands[v].x),
               abs(islands[u].y - islands[v].y));
}

auto dijkstra() {
    vector<int> dist(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> que;

    dist[0] = 0;
    que.push(make_pair(0, 0));

    while (!que.empty()) {
        int v = que.top().second;
        que.pop();

        for (auto neigh: graph[v])
            if (dist[v] + calc_dist(v, neigh) < dist[neigh]) {
                dist[neigh] = dist[v] + calc_dist(v, neigh);
                que.push(make_pair(dist[neigh], neigh));
            }
    }
    cout << dist[n - 1] << '\n';
}

auto set_neighs() {
    island prev, next;
    for (int i = 0; i < n - 1; ++i) {
        prev = by_x[i];
        next = by_x[i + 1];
        graph[prev.ind].push_back(next.ind);
        graph[next.ind].push_back(prev.ind);
    }

    for (int i = 0; i < n - 1; ++i) {
        prev = by_y[i];
        next = by_y[i + 1];
        graph[prev.ind].push_back(next.ind);
        graph[next.ind].push_back(prev.ind);
    }
}

void input() {
    cin >> n;

    island islnd;
    for (int i = 0; i < n; ++i) {
        islnd.ind = i;
        cin >> islnd.x >> islnd.y;
        islands[i] = islnd;
        by_x.push_back(islnd);
        by_y.push_back(islnd);
    }

    sort(by_x.begin(), by_x.end(), [](const island &u, const island &v) {
        return u.x == v.x ? u.y < v.y : u.x < v.x;
    });
    sort(by_y.begin(), by_y.end(), [](const island &u, const island &v) {
        return u.y == v.y ? u.x < v.x : u.y < v.y;
    });

    set_neighs();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    dijkstra();
    return 0;
}

