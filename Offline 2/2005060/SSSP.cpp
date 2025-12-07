#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int N = 1e5+5;

int parent[N];
long long dis[N];

struct Edge{
    int a , b , w;
};

void print_path(int source, int destination);

void BellmanFord(int source , int destination , int nodes, vector <Edge> &edges){

    for (int i = 0 ; i < nodes; i++){
        parent[i]=-1;
        dis[i] =  INF;
    }

    dis[source] = 0;

    parent[source] =  source;

    for (int i = 0 ; i < nodes-1 ;i++){
        for(auto e : edges){
            if (dis[e.a]+e.w < dis[e.b]){
                dis[e.b] = dis[e.a]+e.w;
                parent[e.b] = e.a;
            }
        }
    }

    bool negCycle = false ;
    for(auto e : edges){
        if (dis[e.a]+e.w < dis[e.b]){
            negCycle = true;
            break;
        }
    }
    
    if (!negCycle){
        cout <<  dis[destination] << endl;
        print_path(source, destination);
    }
    else{
        cout  << "Negative weight cycle present\n";

    }

}

long long Dijkstra(int source , int destination , vector <pair  <int , int >> adj[],int nodes){

    vector<bool> visited(nodes , false);

    for (int i=0; i< nodes ;i++) {
        parent[i]=-1;
        dis[i] = INF;
    }

    priority_queue <pair  <int , int >> pq; // {-distance , to}
    pq.push({0,source});
    dis[source] = 0;
    visited[source] = true;
    parent[source] = source;


    while (!pq.empty()){
        int now = pq.top().second;
        int ssd = pq.top().first;

        dis[now] = (-1)*ssd;
        visited[now] = true;

        
        pq.pop();

        if (now == destination){
            return dis[now];
        }

        for (auto i :  adj[now]){
            int to = i.first;
            int w = i.second;
            if (visited[to])  continue;

            if (dis[now] + w < dis[to]){
                dis[to] = dis[now] + w;
                pq.push({-dis[to],to});
                parent[to] = now;
            } 
        }
    }
}



void print_path(int source, int destination){
    vector <int> path;

    int s = source;
    int d = destination;
    path.push_back(d);
    while (parent[d]!= d){
        path.push_back(parent[d]);
        d = parent[d];
    }
    reverse(path.begin(),path.end());
    int len = path.size();
    for (int i=0 ;i < len ;i++){
        if (i!=len-1){
            cout  << path[i] << "->";
        }
        else cout  << path[i] << endl;
    }
}




int main(){

    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    // total nodes and edges
    int n , m;
    cin >> n >> m;

    //adjacency list for Dijkstra's Algo
    vector <pair <int , int  >> adj_d[n];
    //Edge list for Bellman Ford Algo
    vector<Edge> edges;


    //making the lists
    for (int i=0 ; i < m ; i++ ){
        int u, v, w;
        cin >>  u >>  v >> w;
        Edge e;
        e.a = u; e.b = v ; e.w=w;
        edges.push_back(e);
        if ( w < 0) w = -1*w;
        adj_d[u].push_back({v,w});
    }

    int source , destination; 
    cin >> source  >>  destination ;


    cout  << "Bellman Ford Algorithm:\n";
    BellmanFord(source, destination , n , edges);

    cout << "\n\n";

    cout << "Dijkstra Algorithm:\n";
    cout  << Dijkstra(source, destination, adj_d, n) <<  endl;;
    print_path(source,destination);

    
    return 0;
}