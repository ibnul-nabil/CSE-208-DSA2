#include<bits/stdc++.h>
using namespace std;


long long fac(long long n){
    if (n==0) return 1;

    long long res= 1;
    for(int i=2; i<=n;i++){
        res*=i;
    }
    return res;

}
long long nCr(long long n , long long  r){
    return fac(n)/(fac(n-r)*fac(r));
}

class Node{

public:
    int key;
    Node* parent;
    Node* child;
    Node* sibling;
    int degree;
};

class Binomial_heap{

private:

    Node* head;
    

    Node* getNewNode(int data){
        Node* temp = new Node;
        temp->key = data;
        temp->parent = nullptr;
        temp->child = nullptr;
        temp->sibling = nullptr;
        temp->degree = 0;
        return temp;
    }
    //making x the child of y
    void Link(Node* x, Node* y){
        x->parent = y;
        x->sibling = y->child;
        y->child = x;
        y->degree++;
    }
    Node* Merge(Node* it1 , Node* it2){
        Node* root = nullptr;
        
        
        if (it1== nullptr){
            return it2;
        }
        else if( it2 == nullptr){
            return it1;
        }

        //cout  << "in merger : two heads " <<it1->key << "  " <<  it2->key << endl;
 
        if (it1->degree < it2->degree){
            root = it1;
            it1 = it1->sibling;
        }
        else{
            root = it2;
            it2 = it2->sibling;
        }
        Node* now = root;
        while (it1 != nullptr && it2 != nullptr ){
            if (it1->degree < it2->degree){
                now->sibling = it1;
                it1 = it1->sibling;
            }
            else {
                now->sibling = it2;
                it2 = it2->sibling;
            }
            now = now->sibling;
        }
        while (it1 != nullptr){
            now->sibling = it1;
            now = it1;
            it1 = it1->sibling;

        }
        while (it2 != nullptr){
            now->sibling = it2;
            now = it2;
            it2 = it2->sibling;
        }

        now =  root->sibling;
       
        return root;

    }
    //Union
    Node* Union(Node* h1 , Node* h2){
        //merging 2 heaps
        Node* new_root = nullptr; 
        new_root = Merge(h1,h2);    
        

        if (new_root == nullptr){
            return nullptr;
        }
        
        
        Node* curr = new_root;
        Node* prev = nullptr;
        Node* next ;

        
        next = curr->sibling;

        while (next != nullptr){
            if ((curr->degree != next->degree) ||
                (next->sibling!= nullptr && next->sibling->degree==curr->degree)){
                    prev = curr;
                    curr = next;
                    
            }
            else if (curr->key <= next->key){
                curr->sibling = next->sibling;
                Link(next, curr);
            }
            else {
                if (prev == nullptr){
                    new_root = next;
                }
                else {
                    prev->sibling = next;
                }
                Link(curr , next);  
                curr = next;


            }
            next= curr->sibling;
            
        }
        //cout  << "new root after union " << new_root->key << endl;
        return new_root;
    }

    
    Node* FindMin(Node *t){
        Node* minimum = t;
        while (t!= nullptr){
            if (t->key < minimum->key){
                minimum = t;
            }
            t=t->sibling;
        }
        return minimum;
    }

   

    Node* ExtractMin(Node *t){
        // if the heap is empty
        if (this->head == nullptr){
            
            return nullptr ;
        }

        Node* min_node = FindMin(this->head);
       
        cout  << "Extract-Min returned " << min_node->key << endl;
        
        if (min_node->child == nullptr){
            
            if (min_node->sibling != nullptr ) this->head = min_node->sibling;
            else this->head = nullptr;
            return min_node;
        }
        
        Node* prev = nullptr;
        Node* now = this->head;
        Node* next = this->head->sibling;

        while (now != nullptr){
            if (now->key == min_node->key ){
                break;
            }
            prev = now;
            now = now->sibling;
            next = now->sibling;
           
        }

        if (prev != nullptr )prev->sibling = nullptr;

        
        vector<Node*> sibling_list;

        
        Node* curr = min_node->child;

        while (curr != nullptr){
            curr ->parent = nullptr;
            sibling_list.push_back(curr);
            curr = curr->sibling;
        }

        // for(auto i : sibling_list) cout  << i->key << " ";
        // cout  << endl;
        

        for (int i = sibling_list.size()-1 ; i > 0 ; i --){
            if (i-1 >= 0) sibling_list[i]->sibling = sibling_list[i-1];
        }
        sibling_list[0]->sibling= nullptr; 

        
        if (min_node->key==this->head->key) this->head = min_node->sibling;
        this->head = Union(this->head , sibling_list[sibling_list.size()-1]);
        this->head = Union(this->head , next);
        return min_node;

    }
    
   



public:
    Binomial_heap(){
        head = nullptr;
    }
    ~Binomial_heap(){
        // Node *t = ExtractMin(this->head);
        // while(1){
        //     cout  <<  t->key << endl;
        //     if (t== nullptr){
        //         break;
        //     }
        //     delete t;
        //     Node* t= ExtractMin(this->head);
        // }
    }
    void Union(Binomial_heap &h){
        if (h.head != nullptr){
            this->head = Union(this->head , h.head);
        }
    }
    void Insert(int data){
        
        Node* t= getNewNode(data);
        if (head == nullptr){

            head = t;
            //cout  << "1st insert " << head->key << endl; 
            return;
        }
        this->head = Union(this->head, t);
    }
    void FindMin(){
        Node* t = FindMin(this->head);
        if (t==nullptr){
            cout << "Empty heap\n";
        }
        else{
            cout  << "Find-Min returned " << t->key <<  endl;
        }
    }
    void ExtractMin(){
        
       Node* min = ExtractMin(this->head);
       if (min == nullptr) {
        cout  << "Empty heap\n";
        return;
       }
       cout  << "Extract-Min returned " << min->key << endl;
       delete min; 
        
    }
    
    
    void print(){
        cout  << "Printing Binomial Heap...\n";
 
        Node* curr = this->head;

        while (curr != nullptr){
            cout  << "Binomial Tree, B" << curr->degree << endl;
            queue<Node*> que;
            que.push(curr);
            long long counter = 0;
            long long level = 0;
            cout << "Level " << level << " : "; 
            while (!que.empty()){
                
                Node* temp= que.front();
                que.pop();
                counter++;
                cout  << temp->key << " ";
                if (counter == nCr(curr->degree ,level)){
                    counter = 0;
                    level++;
                    cout  << endl;
                    if (level <= curr->degree )cout << "Level " << level << " : ";

                }
                if (temp->child != nullptr){
                    Node* temp2 = temp->child ;
                    while (temp2 != nullptr){
                        
                        que.push(temp2);
                        temp2 = temp2->sibling;
                    }
                }          
            }
            cout  << endl; 
            if (curr->sibling!= nullptr)curr = curr->sibling;
            else return;

        }
    }

};

void menu(){
    ifstream in;
    in.open("in.txt");
    freopen("out.txt","w",stdout);

    

    Binomial_heap b;

    string s;
    
    
    while (getline(in , s)){
        stringstream strm(s);
        string s1;
        strm >> s1; 
        int x;
        if (s1=="I"){
            
            strm >> x;
            b.Insert(x);
        
            
        }
        else if(s1=="P"){
            b.print();        
        }
        else if(s1=="F"){
           b.FindMin();
        }
        else if (s1=="E"){
            b.ExtractMin();
        }
        else if (s1=="U"){
            Binomial_heap temp;
            vector <int> v;
            while(strm >> x){
                temp.Insert(x);
            }
            b.Union(temp);    

        }
        
    }
    

}

int main(){

    menu();

    return 0;
}