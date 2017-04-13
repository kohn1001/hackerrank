/* Hackerrank challenge: accepted all tests - including test #7 */


#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <memory>
#include <map>
#include <set>
#include <queue>
#include <stdio.h>


using namespace std;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
const int max_int = 1 << 20; //numeric_limits<int>::max();
const int Max_nodes = 3000;
const int Max_edges = Max_nodes * Max_nodes/2;

class Graph{
public:
    Graph(int nodes = Max_nodes, int edges = Max_edges):
        nodes_(nodes+1),
        edges_(edges),
        dist_(nodes+1, max_int),
        adjList_(nodes+1),
        in_queue_(nodes+1, 0)
    {
    }
    ~Graph() {}
    void addEdge(int from, int to, int w) {

        adjList_[from].emplace_back(make_pair(w, to));
        adjList_[to].emplace_back(make_pair(w, from));
    }
    vii getNeighbours(int n) {
        return adjList_[n];
    }
    void dijkstra(int src);

private:
    vi dist_;
    vector<vii> adjList_;
    int nodes_;
    int edges_;
    int src_;
    void print(int node);
    vi in_queue_;
    queue<int> q_;
   // std::priority_queue<int, vi, greater<int>> q_;
};

void Graph::dijkstra(int src)
{
    src_ = src;
    dist_[src] = 0;
    q_.push(src); in_queue_[src_] = 1;
    while(!q_.empty()) {
        auto front = q_.front();  q_.pop();
        int d = dist_[front], u = front;
        in_queue_[u] = 0;
            for(int i = 0 ; i < (int)adjList_[u].size(); ++i) {
                auto v = adjList_[u][i];
                if(dist_[v.second] > dist_[u] + v.first) {
                    dist_[v.second] = dist_[u] + v.first;
                    if(!in_queue_[v.second]) {
                        q_.push(v.second);
                        in_queue_[v.second] = 1;
                    }
                }
            }
    }

    for(int i = 1; i < nodes_; ++i) {
        if(i == src_) {
            continue;
        }
        if(dist_[i] == max_int) {
            cout << "-1" << " ";
        }
        else{
            cout << dist_[i] << " ";
        }
    }
    cout << endl;
}



int main(){
    std::ios::sync_with_stdio(false); 
    int t;
    cin >> t;

    for(int a0 = 0; a0 < t; a0++){
        int n;
        int m;
        cin >> n >> m;
        unique_ptr<Graph> g(new Graph(n,m));
        for(int a1 = 0; a1 < m; a1++){
            int x;
            int y;
            int r;

            cin >> x >> y >> r;
            g->addEdge(x, y, r);
        }
        int s;
        cin >> s;
        g->dijkstra(s);
    }
    return 0;
}
