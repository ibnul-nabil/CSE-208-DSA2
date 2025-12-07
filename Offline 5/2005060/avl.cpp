#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
using namespace std;


class Node {

public :
    int key ;
    Node *left;
    Node *right;
    Node *parent;
    int bf;
};

class AVL{

private :
    Node* root;

    Node* getNewNode(int data){
        Node* temp=new Node;

        temp->key=data;
        temp->left=nullptr;
        temp->right=nullptr;
        temp->parent= nullptr;
        temp->bf = 0;

        return temp;
    }
    void clear(Node* t){
        if (t==nullptr){
            return;
        }
        clear(t->left);
        clear(t->right);
        delete t;

    }
    Node* getMin(Node *t){
        if (t->left != nullptr){
            return getMin(t->left);
        }
        else{
            return t;
        }
    }
    void Transplant (Node *u , Node *v){

        if (u->parent ==  nullptr){
            root = v;
        }
        else if( u == u->parent->left){
            u->parent->left = v;
        }
        else {
            u->parent->right = v; 
        }

        if (v != nullptr){
            v->parent = u->parent;
        }

    }

    void rightRotation(Node *a){
        Node *p= a->parent;
        Node *b=a->left;
        a->left= b->right;
        if (b->right!= nullptr){
            b->right->parent= a;
        }
        b->right=a;
        a->parent=b;
        b->parent=p;
        //parent update
        if (p!= nullptr){
            if (p->left == a){
                p->left=b;
            }
            else {
                p->right= b;
            }
        }else this->root = b;

        //update bf
        a->bf = a->bf +1 - min(0 , b->bf);
        b->bf = b->bf +1 + max(0 , a->bf);
    }
    void leftRotation(Node *a){
        Node *p= a->parent;
        Node *b=a->right;
        a->right= b->left;
        if (b->left!= nullptr){
            b->left->parent= a;
        }
        b->left=a;
        a->parent=b;
        b->parent=p;
        //parent update
        if (p!= nullptr){
            if (p->left == a){
                p->left=b;
            }
            else {
                p->right= b;
            }
        }else this->root = b;

        //update bf
        a->bf = a->bf -1 - max(0 , b->bf);
        b->bf = b->bf -1 + min(0 , a->bf);

    }
    void updateBalanceFactor(Node* t) {
		if (t->bf < -1 || t->bf > 1) {
			rebalance(t);
			return;
		}

		if (t->parent != nullptr) {
			if (t == t->parent->left) {
				t->parent->bf -= 1;
			} 

			if (t == t->parent->right) {
				t->parent->bf += 1;
			}

			if (t->parent->bf != 0) {
				updateBalanceFactor(t->parent);
			}
		}
	}
    void rebalance(Node* t) {
		if (t->bf > 0) {
			if (t->right->bf < 0) {
				rightRotation(t->right);
				leftRotation(t);
			} else {
				leftRotation(t);
			}
		} else if (t->bf < 0) {
			if (t->left->bf > 0) {
				leftRotation(t->left);
				rightRotation(t);
			} else {
				rightRotation(t);
			}
		}
	}

   
    
public :
    AVL(){
        root=nullptr;
    }
    ~AVL(){
        clear(root);
    }
    //FIND
    bool Find(int data){
        if (root==nullptr){
            return false ;
        }
        Node* current=root;
        while (current!=nullptr){
            if (data < current->key){
                current=current->left;
            }
            else if (data > current->key){
                current=current->right;
            }
            else{
                return true;
            }
        }
        return false;
    }
   
    //DELETE
    void Delete(int data){
        
        
        if (root==nullptr){
            cout <<"Tree is empty\n";
            return ;
        }
        if (!Find(data)){
            cout << "missing that data\n";
            return;
        }
       
        
        
        Node* current =this->root;
        
        while(current!=nullptr){
            
            if (data < current->key){
                current=current->left;
            }
            else if (data > current->key){
                current=current->right;
            }
            else{
                break;
            }
        }
        Node *p = current->parent;
        Node *new_curr;
        if (current->left== nullptr && current->right==nullptr){
            new_curr = current->parent;

            if (current->key < current->parent->key){
                current->parent->left = nullptr;
            }
            else {
                current->parent->right = nullptr;
            }
        }
        else if (current->left == nullptr){
            new_curr = current->right; 
            Transplant(current, current->right);
            
        }
        else if ( current->right ==  nullptr){
            new_curr= current->left;
            Transplant(current, current->left);
           
        }
        else {
            Node *y = getMin(current->right);
            if (y->parent != current){
                Transplant(y,y->right);
                y->right = current->right;
                y->right->parent = y;

            }
            Transplant(current, y);
            y->left = current->left;
            y->left->parent = y;
            new_curr = y;
        }
        delete current;
        //updateBalanceFactor(new_curr);
        
        
        
    }
    //INSERT
    void Insert(int data){
        if (root ==  nullptr){
            root = getNewNode(data);
            return ;
        }

        Node* current=root;
        Node* parent;
        while(current!=nullptr){
            parent=current;
            if (data < current->key){
                current=current->left;
            }
            else{
                current=current->right;
            }
        }

        Node* child=getNewNode(data);
        child->parent = parent;
        if (data < parent->key){
            parent->left=child;
        }
        else{
            parent->right=child;
        }
        updateBalanceFactor(child);


    }

    

    //printing the current state 
    void currentState(Node* t){
        if(root ==nullptr){
            return;
        } 
        cout << t->key << "";
        if (t->left!=nullptr && t->right==nullptr){
            cout << "(";
            currentState(t->left);
            cout  << ",)";
            //cout <<")()";

        }
        else if (t->left!=nullptr){
            cout << "(";
            currentState(t->left);
            cout <<",";
        }
        
     
        
        if (t->right!=nullptr && t->left==nullptr){
            cout  << "(,";
            //cout <<"()(";
            currentState(t->right);
            cout <<")";

        }
        else if (t->right!=nullptr){
            cout <<"";
            currentState(t->right);
            cout <<")";
    
        }
    }
    //inorder traversal
    void inOrder(Node* t){
        if(root ==nullptr){
            cout <<"Tree is empty, so no in order traversal ";
            return;
        } 
       
        if (t->left!=nullptr){
            inOrder(t->left);
        }
        cout << t->key << " ";

        if (t->right!=nullptr){
            inOrder(t->right);
        }     
    }
    //printing 
    void print(int i){
        if (i==1){
            inOrder(root);
        }
        
        else {
            currentState(root);
        }
        cout << "\n";
    }
};


void menu(){
    
   freopen("out_avl.txt","w",stdout);

    ifstream in;
    in.open("in.txt");

    AVL avl;

    string s1;

    double time = 0;
    while (in>>s1){
         
        int x;
        if (s1=="I"){
            
            in >>x;
            avl.Insert(x);
            avl.print(2);
    
                
        }
        else if(s1=="D"){
            in >> x;   
            avl.Delete(x);     
            avl.print(2);  
                 
        }
        else if(s1=="F"){
            in >> x;

            bool t=avl.Find(x);
            if (t){
                cout << "found\n";
            }
            else {
                cout << "not found\n";
            }

        }
        else if (s1=="T"){
            avl.print(1);
            
        }
        
    }
    in.close();

}



int main(){
    
    
    menu();

    return 0 ;

}