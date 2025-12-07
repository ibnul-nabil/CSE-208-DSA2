#include<bits/stdc++.h>
#include"minHeap.h"
using namespace std;



//PRIM'S ALGORITHM

//Relaxing the edges of a node 
void relaxEdges(int node , vector <pair <int , int >> adj[] ,vector <int> &visited , minHeap &pq){
    visited[node]=1; 

    //extracting the edges the node 
    for(auto i : adj[node]){
        Edge e;
        e.a=node;  e.b=i.first ;  e.weight=i.second;

        if (visited[i.first]==1) continue;  //already in the heap


        int indx = pq.Find(e);
        //not in the heap -> inseting into the heap
        if (indx == -1 ){
            pq.Insert(e);
        }
        //edge is in the heap   
        else {
            Edge prv = pq.getEdge(indx);
            //if the new edge weight is smaller , update it in the heap
            if (prv.weight > e.weight){
                pq.DecreaseKey(prv,e);
            }
            
        } 
    }
}
//prim's algorithm
double MST_PRIM(int source, int nodes ,
                vector <pair <int , int >> adj[] ,
                vector <int> &visited , minHeap &pq ,
                vector <pair <int, int>> &MST_Edges){

    int E=nodes-1; // total edge in MST
    double cost =0;
    int edge_count =0;

    
    relaxEdges(source,adj, visited, pq);

    while ( !pq.isEmpty() /*and edge_count != E*/){
        Edge e = pq.ExtractMin();
        MST_Edges.push_back({e.a,e.b});
        int destination = e.b;
        cost+=e.weight;
        edge_count++;

        relaxEdges(destination,adj,visited,pq);

    }
    return cost ;

}

int main(){

    //freopen("in.txt","r",stdin);
    //freopen("prim.txt","w",stdout);

    int n , m;
    cin >> n >> m;

    vector <pair <int , int >> adj[n];

    vector <int> visited(n,0);

    minHeap pq(n);

    for(int i=0;i<m;i++){
        int a, b, w;
        cin >> a  >> b >> w;

        adj[a].push_back({b,w});
        adj[b].push_back({a,w});
    }

    vector<pair <int, int >> MST_edges;

    double cost = MST_PRIM(0,n,adj, visited, pq, MST_edges);
    cout  << "Prim's Algorithms\n";
    cout  << "Total weight = " <<  cost  << endl;
    cout  << "Root node " << 0 << endl;
    for (auto i  : MST_edges){
        cout  << i.first << " " << i.second << endl;
    }



    return 0;
}