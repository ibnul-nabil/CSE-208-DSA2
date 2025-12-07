#include<bits/stdc++.h>
using namespace std;



const long long INF = 1e9;
const int N = 1e5+5;

long long cost[101][101];


void FloydWarshall(int n){

    for (int k = 1 ; k <= n ; k++){
        for (int i = 1 ; i <= n ; i++){
            for (int j = 1 ; j <= n ; j++){
                cost[i][j] = min(cost[i][j] , cost[i][k] + cost[k][j]);
            }
        }
    }

}

bool negCycle(int n){
    for (int i = 1 ; i <= n ;i++){
        if (cost[i][i] < 0) return true;
    }
    return false;
}

int main(){
    int n , m;
    cin >> n >> m;



    for(int i = 1 ;i <= n ;i++){
        for(int j = 1 ;j <= n ;j++){
            if (i==j) cost[i][j] = 0;
            else cost[i][j]=INF;
        }
    }

    for (int i = 0 ;i < m; i++){
        int a, b, w;
        cin >> a  >> b >> w ;
        cost[a][b] = w;
    }

    FloydWarshall(n);

    if (!negCycle(n)){

        cout  << "Shortest distance matrix\n";

        for(int i = 1 ;i <= n ;i++){
            for(int j = 1 ;j <= n ;j++){
                if (cost[i][j] != INF ) cout  << cost[i][j] << " ";
                else cout  << "INF ";
            }
             cout  << endl;
         }
    }

    else {
        cout  << "Has negative cycle\n";
    }



    return 0;
}
