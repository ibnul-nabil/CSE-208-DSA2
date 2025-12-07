#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;


const ll INF = 1e9;


ll capacity[501][501];
vector<pair<int , int>>  trc;

bool make_graph(int x,int nodes , vector <int> &w , vector <int> &r , vector <vector <int>> table , vector <int> adj[]){

    trc.clear();
    bool is_successful = true;

    int total_nodes = (((nodes-1)*(nodes-2)) / 2 ) + nodes-1 + 2;
    
    for (int i = 1 ; i <= total_nodes ; i++){
        for (int j = 1 ; j <= total_nodes ; j++){
            capacity[i][j] = 0 ;
        }
    }

    

    vector<pair <pair<int, int>, int>> v; 
    

    int cap = 1;

    // s -> match nodes
    for (int i = 1; i <= nodes ; i++){
        for (int j = i+1 ; j <= nodes ; j++){
            if (i == x || j == x) continue;
            capacity[1][++cap] = table[i][j];
            v.push_back({{i,j},cap});
            capacity[cap][1] = 0;
            adj[1].push_back(cap);
            adj[cap].push_back(1);
           
        }
    }

    // team nodes -> t 
    map <int, int > mp;
    for (int i = 1 ; i <= nodes ; i++){
        if (i == x) continue;

        if (w[x]+r[x] - w[i] < 0 ) {
            is_successful = false;
        }

        capacity[++cap][total_nodes] = w[x]+r[x] - w[i];
        
        trc.push_back({cap, i});
        mp[i] = cap;
        capacity[total_nodes][cap] = 0;
        adj[cap].push_back(total_nodes);
        adj[total_nodes].push_back(cap);
        
    }

    // match -> team
    for (int i = 0 ; i < v.size() ;i++){
        int a = v[i].first.first;
        int b = v[i].first.second;

        int node = v[i].second;

        capacity[node][mp[a]] = INF;
        capacity[node][mp[b]] = INF;

        adj[node].push_back(mp[a]);
        adj[node].push_back(mp[b]);
        adj[mp[a]].push_back(node);
        adj[mp[b]].push_back(node);
    }
    return  is_successful;

}



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

    int n;
    cin >> n;

    vector<int> w(n+1);
    vector<int> l(n+1);
    vector<int> r(n+1);
  
    vector <vector <int>>  table(n+1);

    map<int, string > mp;
    for (int i = 1 ; i <= n; i++){
        string name ;
        cin >> name ;
        mp[i] = name;
        cin >> w[i] >> l[i] >> r[i] ;

        table[i].push_back(-1);
        for (int j = 1 ; j <= n ; j++){
            int x;
            cin >> x;
            table[i].push_back(x);
        } 
    }

   
    int total_nodes = (((n-1)*(n-2)) / 2 ) + (n-1) + 2;


    for (int i = 1 ; i <= n ;i++ ){
        
        vector <int> adj[total_nodes+1];

        
        
        ll flow = 0;

        bool state = make_graph( i, n , w, r, table , adj);
        
        for (int i =1 ;i <= total_nodes ;i++){
            flow += capacity[1][i];
        }
        ll maxflow = max_flow(1 , total_nodes , total_nodes ,adj);
        //cout << i << ") " << "flow  : " <<  flow << "  maximum flow : " << maxflow << " -> ";
        if ( !state ||  maxflow < flow ) {
            cout << mp[i]  <<  " is eliminated.\n" ;

            vector<int> p(total_nodes+1);
            bfs(1, total_nodes , total_nodes, p, adj);
             
            vector<int> l;
            for(int i =0 ;i<n-1 ;i++ ){
                if (p[trc[i].first] != -1) l.push_back(trc[i].second);
            }

            // for (auto i : l) cout  << i << " " ;
            // cout << endl;

            cout  <<  "They can win at most "   << w[i] << "+" << r[i] << " = " << w[i]+r[i] <<  " games.\n";

            int t_game=0;
            for (int i = 0 ;i<l.size() ;i++){
                cout  <<  mp[l[i]] << ", ";
                t_game += w[l[i]];

            }
            cout  << " have won a total of " << t_game << " games.\n";

            int t_each = 0;
            int len = l.size();
            for (int i = len-1 ; i >= 0 ;i--){
                for (int j = i-1 ; j >= 0 ;j--){
                    t_each += table[l[i]][l[j]];
                }
                l.pop_back();
            }
            cout  << "They play each other " << t_each << " times. \n";
            cout  << "So on average, each of the teams in this group wins " << (t_game+t_each) << "/" << len << " = " << 1.0*(t_game+t_each)/len << " games\n\n"; 

        }
       
    }

    return 0;
}