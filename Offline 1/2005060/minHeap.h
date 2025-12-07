#include<bits/stdc++.h>
using namespace std;

struct Edge{
    int a, b ;
    double weight;
};

class minHeap{

private:
    Edge *arr;

    int heapSize ;
    int left(int i){ return 2*i; }
    int right(int i){ return 2*i+1; }
    int parent(int i) { return i/2; }

    void BubbleUp(int i);
    void Heapify(int i);
    

public:

    minHeap(int n);
    void Insert(Edge e);
    Edge ExtractMin();
    int Find (Edge e);
    void DecreaseKey(Edge prvKey, Edge newKey);
    bool isEmpty();
    Edge getEdge(int i){ return arr[i]; }

};

minHeap :: minHeap(int n){
    arr = new Edge[n];
    heapSize=0;
}
bool minHeap :: isEmpty(){
    if (heapSize == 0) return true;
    else return false;
}
void minHeap :: BubbleUp(int i){
    int par =parent(i);

    if (par >= 1 && arr[i].weight < arr[par].weight ){
        swap(arr[i],arr[par]);
        BubbleUp(par);
    }
}
void minHeap :: Insert(Edge e){

    arr[++heapSize]=e;
    BubbleUp(heapSize);
}
void minHeap :: Heapify(int i){
    int left_child, right_child, smallest;
    left_child=left(i);
    right_child=right(i);

    if (left_child <= heapSize && arr[left_child].weight < arr[i].weight){
        smallest=left_child;
    }
    else {
        smallest=i;
    }

    if (right_child <= heapSize && arr[right_child].weight < arr[smallest].weight){
        smallest =right_child;
    }

    if (smallest != i){
        swap(arr[smallest],arr[i]);
        Heapify(smallest);
    }
    
}
Edge minHeap :: ExtractMin(){
    
    Edge e= arr[1];
    swap(arr[1],arr[heapSize--]);
    Heapify(1);
    return e;
}
int minHeap :: Find(Edge e){

    for (int i=1;i<=heapSize;i++){
        if ( arr[i].b==e.b  ){
            return i;
        }
    }
    return -1;
}
void minHeap :: DecreaseKey( Edge prvKey , Edge newKey) {
    int prv_indx = Find(prvKey);
    arr[prv_indx] = newKey ;
    BubbleUp(prv_indx);
}