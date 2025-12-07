#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;


const ll INF = 1e9;


ll capacity[501][501];

ll bfs(int s, int t, int nodes ,vector<int> &parent, vector <int> adj[]){
    for (int i = 1; i <= nodes ; i++ ){
        parent[i] = -1;
    }  

    queue<pair <int , ll >> q;
    q.push({s, INF});

    while (! q.empty()){
        int now = q.front().first;
        ll flow = q.front().second;

        q.pop();

        for (int next : adj[now]){
            if (parent[next] == -1 && capacity[now][next] > 0){

                parent[next] = now;
                ll new_flow = min (flow, capacity[now][next]);
                if (next == t) return new_flow;
                q.push({next, new_flow});
            }
        }
    } 
    parent[s] = -1;
    return 0;

}

ll max_flow(int s, int t , int nodes , vector <int> adj[] ){
   
    vector<int>  parent(nodes+1);
    
    ll maxflow = 0;

    ll next_flow ;

    while ((next_flow = bfs(s, t, nodes ,parent , adj))){
        maxflow += next_flow;

        int now = t;
        while ( now != s){
            int par = parent[now];
            capacity[par][now] -= next_flow;
            capacity[now][par] += next_flow;
            now = par ;
        }


    }
    return maxflow ;

}


int main(){

    int n , m;
    cin >> n >> m;

    vector <int> adj[n+1];
    for(int i =1 ; i<=n;i++){
        for (int j = 1 ; j<=n;j++){
            capacity[i][j] = 0;
        }
    }
    for(int i =1 ; i <=m ; i++){
        int a , b, w;
        cin >> a >> b >> w;
        capacity[a][b]= w;
        adj[a].push_back(b);
    }

    cout  << max_flow(1, n, n , adj);

    return 0;
}