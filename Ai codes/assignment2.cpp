#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

// Directions: Up, Down, Left, Right
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int R, C;
vector<vector<char>> grid;

// Check valid move
bool isValid(int r, int c) {
    return r >= 0 && r < R && c >= 0 && c < C && grid[r][c] != '#';
}

// Find position of a character (G or P)
pair<int,int> findChar(char ch) {
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (grid[i][j] == ch)
                return {i, j};
    return {-1, -1};
}

// Print grid
void printGrid() {
    cout << "Grid:\n";
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++)
            cout << grid[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

// Manhattan heuristic
int heuristic(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) + abs(c1 - c2);
}

// Structure for A* node
struct Node {
    int r, c;
    int g, h, f;
};

// Comparator for priority queue (min-heap by f)
struct Compare {
    bool operator()(Node a, Node b) {
        return a.f > b.f;
    }
};


vector<pair<int,int>> AStar_ShortestPath(pair<int,int> start, pair<int,int> target) {
    vector<vector<int>> gCost(R, vector<int>(C, 1e9));
    vector<vector<bool>> closed(R, vector<bool>(C, false));
    vector<vector<pair<int,int>>> parent(R, vector<pair<int,int>>(C, {-1, -1}));

    priority_queue<Node, vector<Node>, Compare> pq;

    int sr = start.first, sc = start.second;
    int tr = target.first, tc = target.second;

    gCost[sr][sc] = 0;
    int h = heuristic(sr, sc, tr, tc);
    pq.push({sr, sc, 0, h, 0 + h});

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        int r = cur.r;
        int c = cur.c;

        // Already processed
        if (closed[r][c]) continue;
        closed[r][c] = true;

        // Reached target
        if (r == tr && c == tc) break;

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (isValid(nr, nc) && !closed[nr][nc]) {
                int newG = gCost[r][c] + 1;

                // Better path found
                if (newG < gCost[nr][nc]) {
                    gCost[nr][nc] = newG;
                    parent[nr][nc] = {r, c};

                    int newH = heuristic(nr, nc, tr, tc);
                    int newF = newG + newH;

                    pq.push({nr, nc, newG, newH, newF});
                }
            }
        }
    }

    // If target was never reached
    if (!closed[tr][tc]) return {};

    // Reconstruct path
    vector<pair<int,int>> path;
    pair<int,int> cur = target;

    while (!(cur.first == -1 && cur.second == -1)) {
        path.push_back(cur);
        cur = parent[cur.first][cur.second];
    }

    reverse(path.begin(), path.end());
    return path;
}

int main() {
    // Input grid size
    cout << "Enter number of rows and columns: ";
    cin >> R >> C;

    grid.resize(R, vector<char>(C));

    cout << "Enter grid (G, P, #, .):\n";
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            cin >> grid[i][j];

    printGrid();

    pair<int,int> ghost = findChar('G');
    pair<int,int> pacman = findChar('P');

    if (ghost.first == -1 || pacman.first == -1) {
        cout << "Error: G or P not found!\n";
        return 0;
    }

    // A*
    cout << "---- A* (Ghost shortest path to Pac-Man) ----\n";
    vector<pair<int,int>> shortestPath = AStar_ShortestPath(ghost, pacman);

    if (shortestPath.empty()) {
        cout << "Ghost cannot reach Pac-Man.\n\n";
    } else {
        cout << "Shortest path length = " << (int)shortestPath.size() - 1 << " moves\n";
        cout << "Path: ";
        for (auto &p : shortestPath)
            cout << "(" << p.first << "," << p.second << ") ";
        cout << "\nResult: Ghost reached Pac-Man \n\n";
    }

    return 0;
}