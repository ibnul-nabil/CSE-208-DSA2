#include<bits/stdc++.h>
using namespace std;


typedef std::mt19937 rng_type;
std::uniform_int_distribution<rng_type::result_type> udist(60, 200);
rng_type rng;

int fact (int n){
    int result = 1;
    for(int i = 1 ;i<=n ;i++){
        result *= i;
    }
    return result;
}
int nCr (int n , int r){
    return fact(n)/(fact(r)*fact(n-r));
}


const int maxSize = 21;

class Graph{

private:
    int v;
    vector<pair<int , int >> adj[maxSize];
    

public:


    int cost [maxSize][maxSize];

    Graph(int v){
        this->v= v;

        for(int i = 0 ;i < v;i++){
            cost[i][i]=0;
        }

    }
    void addEdge(int a, int b, int w){
        adj[a].push_back({b,w});
    }
    void print(){
    //    for (int i = 0 ; i < v; i++){
    //     for(auto j : adj[i]){
    //         cout  << i  << "->(" << j.first << "," << j.second << ")  ,"; 
    //     }
    //     cout  << endl;
    //    }
    //    cout  << endl;

        for(int i = 0 ;i <v;i++){
            for(int j=0 ;j< v ;j++){
                cout  << cost[i][j] << " ";
            }
            cout  << endl;
        }
    }

};

void Create_Random_Graph( Graph &grph , int v){
    

    std::random_device rd; 
    rng_type gen(rd());
    

    int e = nCr(v,2);

    for(int i = 0; i < v ;i++){
        for(int j = i+1 ; j < v ;j++){
            int curr = udist(gen);
                grph.cost[i][j]= curr;
                grph.cost[j][i]= curr;
        }
    }

    for(int i = 0 ;i<v;i++){
        for(int j = 0 ;j<v ;j++){
            if (j == i) continue;
            for (int k = 0 ; k< v ;k++){
                if (k == j || k==i) continue;

                if (grph.cost[i][j] > grph.cost[i][k]+grph.cost[k][j]){
                    grph.cost[i][j] = grph.cost[i][k]+grph.cost[k][j]-1; 
                }
            }
        }
    }

    for(int i= 0 ;i<v ;i++){
        for(int j = i+1 ; j <v ;j++){
            grph.addEdge(i, j , grph.cost[i][j]);
        }
    }
    
    
}

int n;
int ans = 100000;
int Visited ;
int dp[6][1<<6];

int k = 1;
int tsp(Graph &g, int mask , int pos){
    
    if (mask == Visited){
        
        return g.cost[pos][0];
    }

    //if (dp[pos][mask] != -1) return dp[pos][mask];
    
    ans= 100000;
    for(int i = 0 ; i < n; i++){
       
        if ( ((1<<i) & mask) == 0){
            
            int result  = tsp(g , (mask | (1<<i)) , i) + g.cost[pos][i];
            //cout <<   <<  result <<  endl;
            ans =  min(ans, result);
        }
        
    }
    //cout  <<  ans <<  endl;
    //return dp[pos][mask] = ans;
    return ans ;

}

int main(){
    cin >> n;
    Graph g(n);
    
    Create_Random_Graph(g,n);
    g.print();

    Visited = (1 << n ) -1 ;

    // for(int i = 0 ; i < n;i++){
    //     for(int j =0 ;j< 1<<n ;j++){
    //         dp[i][j] = -1;
    //     }
    // }

    cout  << tsp(g,1,0);

    //  for(int i = 0 ; i < n;i++){
    //     for(int j =0 ;j< 1<<n ;j++){
    //         cout <<  dp[i][j] << " ";
    //     }
    //     cout  << endl;
    // }

   
     
  

   

    return 0;
}