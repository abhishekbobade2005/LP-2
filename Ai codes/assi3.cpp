#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 1e9

// ===================== DIJKSTRA =====================
void dijkstra(int V, vector<vector<pair<int,int>>> &adj, int source) {

    vector<int> dist(V, INF);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while(!pq.empty()) {

        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if(d > dist[u]) continue;

        for(auto edge : adj[u]) {

            int v = edge.first;
            int weight = edge.second;

            if(dist[v] > d + weight) {

                dist[v] = d + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\n=== Shortest Distances from Airport " << source << " ===\n";

    for(int i = 0; i < V; i++)
        cout << "Airport " << i << " : " << dist[i] << endl;
}

// ===================== FLIGHT SCHEDULING =====================
struct Flight {

    int id;
    int price;
};

bool comparePrice(Flight a, Flight b) {

    return a.price > b.price;
}

void scheduleFlights(vector<Flight> flights) {

    sort(flights.begin(), flights.end(), comparePrice);

    int n = flights.size();
    int daySlots = n / 2;

    cout << "\n=== Flight Schedule Based on Ticket Price ===\n";

    cout << "\n--- Day Slots (High Price Flights) ---\n";

    for(int i = 0; i < daySlots; i++) {

        cout << "Flight " << flights[i].id
             << " | Price: " << flights[i].price
             << " | Time: Day\n";
    }

    cout << "\n--- Night Slots (Low Price Flights) ---\n";

    for(int i = daySlots; i < n; i++) {

        cout << "Flight " << flights[i].id
             << " | Price: " << flights[i].price
             << " | Time: Night\n";
    }
}

// ===================== SELECTION SORT =====================
struct FlightTime {

    string id;
    int time;
};

void selectionSortFlights(vector<FlightTime> &flights) {

    int n = flights.size();

    for(int i = 0; i < n - 1; i++) {

        int minIndex = i;

        for(int j = i + 1; j < n; j++) {

            if(flights[j].time < flights[minIndex].time)
                minIndex = j;
        }

        swap(flights[i], flights[minIndex]);
    }

    cout << "\n=== Flights Sorted by Departure Time ===\n";

    for(auto f : flights) {

        cout << f.id << " : " << f.time << " hrs\n";
    }
}

// ===================== MAIN =====================
int main() {

    // ---------- GRAPH INPUT ----------
    int V, E;

    cout << "Enter number of airports: ";
    cin >> V;

    cout << "Enter number of routes: ";
    cin >> E;

    vector<vector<pair<int,int>>> adj(V);

    cout << "Enter routes (source destination distance):\n";

    for(int i = 0; i < E; i++) {

        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int source;

    cout << "Enter source airport for shortest path: ";
    cin >> source;

    dijkstra(V, adj, source);

    // ---------- FLIGHT SCHEDULING ----------
    int n;

    cout << "\nEnter number of flights: ";
    cin >> n;

    vector<Flight> flights(n);

    cout << "Enter ticket prices:\n";

    for(int i = 0; i < n; i++) {

        flights[i].id = i + 1;
        cin >> flights[i].price;
    }

    scheduleFlights(flights);

    // ---------- SELECTION SORT ----------
    int m;

    cout << "\nEnter number of flights for departure sorting: ";
    cin >> m;

    vector<FlightTime> times(m);

    cout << "Enter flight ID and departure time (0-24 hours)\n";
    cout << "Format example: f1 3\n";

    for(int i = 0; i < m; i++) {

        cin >> times[i].id >> times[i].time;

        if(times[i].time < 0 || times[i].time > 24) {

            cout << "Invalid time! Enter between 0 and 24.\n";
            i--;
        }
    }

    selectionSortFlights(times);

    return 0;
}