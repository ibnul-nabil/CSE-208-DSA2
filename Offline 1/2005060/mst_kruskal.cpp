#include<bits/stdc++.h>
using namespace std;

const int N=100001;
int parent [N];
int rnk [N];

// Disjoint Set 

//initializing the DSU
void DSU(int n){
    for(int i=0;i<n;i++) {
        parent[i]=i;
        rnk[i]=0;
    }
}

int find_representative(int a){
    if (a == parent[a]) return a;
    return parent[a] = find_representative(parent[a]);
}

void Union(int a, int b){
    int u = find_representative(a);
    int v = find_representative(b);
    if (u!=v){
        if (rnk[u] < rnk[v]) swap(u,v);
        parent[v]=u;
        if (rnk[u] == rnk[v]) rnk[u]++;      
    }
}
//checking if the representative of the two elements are same or not
bool same (int a, int b){
    if (find_representative(a)==find_representative(b))  return true;
    else return false;
}


struct Edge{
    int a, b ;
    double weight;
};

bool comp(Edge a , Edge b){
    return a.weight < b.weight ;
}

//Kruskal's algorithm
double MST(vector<Edge> &e, vector<pair <int, int>> &MST_edges){
    double cost=0;
    for (auto i : e){
        if (!same(i.a,i.b)){
            Union(i.a,i.b);
            cost+=i.weight;
            MST_edges.push_back({i.a, i.b});
        }
    }
    return cost;
}


int main(){

    //freopen("in.txt","r",stdin);
    //freopen("kruskal.txt","w",stdout);

    
    int n, m;
    cin >> n >> m; 

    vector <Edge> edge(m);
    for(int i=0;i<m;i++){
        cin >> edge[i].a >> edge[i].b >> edge[i].weight;
    }

    DSU(n);

    sort(edge.begin(),edge.end(),comp);

    vector<pair <int, int >> MST_edges;

    double cost = MST(edge,MST_edges);
    cout  << "Kruskal's Algorithm:\n";
    cout  << "Total weight = " << cost << endl;
    for (auto i  : MST_edges){
        cout  << i.first << " " << i.second << endl;
    }


    return 0;
}

