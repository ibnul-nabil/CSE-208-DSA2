#include<bits/stdc++.h>
#include<random>
using namespace std;

#define forn(n) for (int i = 0 ; i < n ; i++) 


#define P 31

typedef long long ll ;

typedef std::mt19937 rng_type;



bool is_prime(int n){
    if (n == 1) return false;
    if (n == 2 ) return true;

    for (int i = 2; i*i <= n+1; i++){
        if (n%i == 0 ){
            return false;
        }
    }

    return true;

}

int next_prime(int n){
    for (int i = n ; ;i++){
        if (is_prime(i)){
            return i;
        }
    }
}

// polynomial rolling hash 
unsigned long long hash_str1(string str)
{
    unsigned long long p_pow = 1;
    unsigned long long hash_val = 0 ;
    forn(str.length()){
        hash_val += (str[i]-'a'+1)*p_pow;
        p_pow *= P;
    }
    return hash_val;
}

unsigned long long hash_str2(string str)
{
    unsigned p = 37;
    unsigned long long hash_val = 0 ;
    forn(str.length()){
        hash_val = hash_val*p + str[i];
    }
    return hash_val;
}


unsigned aux_hash(string str){
    unsigned hash_val = 0;
    forn(str.length()){
        hash_val += str[i];
    } 
    return hash_val;
}

class object{

public:
    string key;
    int value;
};

class double_hashing{
private:
    int size;
    vector<object> table;
   
    int collision;
   
public:
    double_hashing(int n){
        this->size = next_prime(n);
        this->collision = 0;
       
        table.resize(size);
       
        forn(size){
            table[i].key = "0";
            table[i].value = -1;

        }
    }

    void Insert(object &obj , unsigned long long (*hash_function)(string)){

        unsigned long long hash_val = hash_function(obj.key) % size;
        unsigned long long indx = hash_val % size;
        int i = 0;

        while (i <= size){
            if (table[indx].key == "0"){
                table[indx] = obj;
                return ;
            }
            else {
                collision++;
                i++;
                indx = (hash_val + i*aux_hash(obj.key)) % size;
                
            }
        }
  

    }

    int Find(const string k , unsigned long long (*hash_function)(string) , int &probe){
        unsigned hash_val = hash_function(k) % size;
        unsigned indx = hash_val % size ;
        int i = 0;

        while ( i <= size){
            probe++;
            if (table[indx].key == k ){
                
                return table[indx].value;
            }
            else {
                if (table[indx].key == "0"){ 
                    return 0;
                }
                else{
                    ++i;
                    indx = (hash_val + i*aux_hash(k)) % size;
                }
            }
            

        }

        return false;
    }

    int getCollision(){ return collision; }
    int getSize(){ return size; }

    void print(){
    
        for(int i = 0 ; i<table.size() ; i++ ){
            if (table[i].key!= "0") cout   << "( "<< table[i].key  << " ," << table[i].value << " )" <<  " , ";
            //else cout  <<  i << " : null\n" ;
        }
        cout << endl;
    }
    
};

class custom_probe{
    private:
    int size;
    vector<object> table;
   
    int collision;
   
public:
    custom_probe(int n){
        this->size = next_prime(n);
        this->collision = 0;
       
        table.resize(size);
       
        forn(size){
            table[i].key = "0";
            table[i].value = -1;


        }
    }

    void Insert(object &obj , unsigned long long (*hash_function)(string)){

        unsigned long long hash_val = hash_function(obj.key) % size;
        unsigned long long indx = hash_val % size;
        int i = 0;
        do {
            if (table[indx].key == "0"){
                table[indx] = obj;
                return ;
            }
            else {
                collision++;
                i++;
                indx = (hash_val + i*aux_hash(obj.key) + 2*i*i) % size;
                
            }

        }while(i<= size);

    }

    int Find(string k , unsigned long long (*hash_function)(string) , int &probe){
        unsigned hash_val = hash_function(k) % size;
        unsigned indx = hash_val % size ;
        int i = 0;

        do {
            probe++;
            if  (table[indx].key == k){
                return table[indx].value ;
            }
            else if (table[indx].key == "0" ) break;
            else {
                i++;
                indx = (hash_val + i*aux_hash(k) + 2*i*i) % size;    
            }
           

        }while(i <= size);

        return 0;
    }

    int getCollision(){ return collision; }
    int getSize(){ return size; }
};

class seperate_chaining{

private:
    int size;
    vector<list<object>> table;
    int collision;
public:
    seperate_chaining(int n){
        this->size = next_prime(n);
        this->collision = 0;
        table.resize(size);
    }

    void Insert(object &obj , unsigned long long (*hash_function)(string)){
        unsigned long long hash_val = hash_function(obj.key);
        unsigned long long indx = hash_val % size;

        if (table[indx].size() > 0){
            collision++;
            table[indx].push_front(obj);
        }
        else table[indx].push_front(obj);
        
    }
    int Find(string k , unsigned long long (*hash_function)(string) , int &probe){
        unsigned long long hash_val = hash_function(k);
        unsigned long long indx = hash_val % size;
        if (table[indx].size() == 0) {
            probe++;
            return 0;
        }
        for(auto it = table[indx].begin() ; it!= table[indx].end() ; it++){
            probe++;
            if (it->key == k ){
                return it->value;
            }
           

        }
        return 0;
    }
    int getCollision(){ return collision; }

    void print(){

        for(int i = 0 ;i <size ;i++){
            
                if (table[i].size() > 0) {
                    for(auto it = table[i].begin() ; it!= table[i].end() ; it++){
                        cout  << it->key << " ";
                    }
                    cout  << endl;
                }
                else cout  << "nil\n";

            
        }
        
    }
    

};



class tow_table_hash{

private :
    int size;
    vector<pair<string , double_hashing *>> sec_table;

public :
    tow_table_hash(int n){
        this->size = next_prime(n);
        sec_table.resize(size, {"0",nullptr});
        
    }

    void insert(string a, string b, int val){
        object x ;
        x.key =b;
        x.value = val;

        unsigned long long hash_val = hash_str1(a) % size;
        unsigned long long indx = hash_val % size;
        int i = 0;
        
        while (i <= size)
        {
            if (sec_table[indx].first == "0" and sec_table[indx].second == nullptr){
                sec_table[indx].first = a;
                double_hashing *y = new double_hashing(size);
                y->Insert(x , hash_str1);
                cout  << "in succ\n";
                return;
            }
            else if (sec_table[indx].first == a){
                sec_table[indx].second->Insert(x , hash_str1);
                cout  << "2nd in\n";
                return;
            }
            else {
                i++;
                indx = (hash_val + i*aux_hash(a))%size;
            }
        }
        

    }
    int find(string a, string b){
        unsigned long long hash_val = hash_str1(a) % size;
        unsigned long long indx = hash_val % size;
        int z=0;
        int i = 0;
        while (i <= size)
        {
            if (sec_table[indx].second == nullptr){
                
                return 0 ;
            }
            else if (sec_table[indx].first == a){
                return sec_table[indx].second->Find(b, hash_str1,z);
            }
            else {
                i++;
                indx = (hash_val + i*aux_hash(a))%size;
            }
        }
        
    }

    double_hashing* find(string a){
        unsigned long long hash_val = hash_str1(a) % size;
        unsigned long long indx = hash_val % size;

        int z=0;
        int i = 0;
        while (i <= size)
        {
            if (sec_table[indx].second == nullptr){
                
                return nullptr ;
            }
            else if (sec_table[indx].first == a){
                return sec_table[indx].second;
            }
            else {
                i++;
                indx = (hash_val + i*aux_hash(a))%size;
            }
        }

       

        
    }
    void print(double_hashing *a){
        if (a!= nullptr)a->print();
        else cout << "null\n";
    }

    

};
int main (){

    tow_table_hash t(5);
    t.insert("bd" ,"dhk" ,500);
    cout  << t.find("bd" , "dhk") << endl;
    t.insert("bd" ,"ctg" , 300);
    t.insert("uk" ,"lon" , 100);

    
    cout  << t.find("bd" , "syl") << endl;

    double_hashing *a ;
    a=t.find("bd");
    a->print();
    a=t.find("chk");
    a->print();

    


    
    /*

    freopen("out.txt","w", stdout);

    std::random_device rd; 
    rng_type gen(rd()); 

    std::uniform_int_distribution<rng_type::result_type> udist(1, 26);
    std::uniform_int_distribution<int> distribution(5, 10); 
    std::uniform_int_distribution<int> search_dist(0, 10000);


    vector<string> strings;

    forn(10000){
        int len = distribution(gen);
    
        string str=""; 
        for (int j = 0 ; j<len ; j++){
            int curr = udist(gen);
            char x = 'a'+curr-1;
            str+=x; 
            
        }
        strings.push_back(str);
    }
    vector<string> search_strings;

    forn(1000){
        int x = search_dist(gen);
        search_strings.push_back(strings[x]);
    } 

    
    
    int t = 3;
    while (t--){
        int n ;
        cin >> n ;

        seperate_chaining sp1(n);
        seperate_chaining sp2(n);

        double_hashing db_hash1(n);
        double_hashing db_hash2(n);

        custom_probe cp1(n);
        custom_probe cp2(n);
        
        int counter = 1;
        int prb = 1;
        for(int i = 0 ; i < strings.size() ;i++){
            if (counter > n) break;
            prb = 1;
            if (db_hash1.Find(strings[i], hash_str1 , prb) ){
                continue;
            }
            else {
                object obj;
                obj.key = strings[i];
                obj.value = counter;

                db_hash1.Insert(obj, hash_str1);
                db_hash2.Insert(obj, hash_str2);

                sp1.Insert(obj, hash_str1);
                sp2.Insert(obj, hash_str2);

                cp1.Insert(obj, hash_str1);
                cp2.Insert(obj, hash_str2);

                counter++;
            }
            
        }
       



        vector <int> probe(6, 1);
        vector <int> succ(6,0);
        for(auto i : search_strings){
            if(sp1.Find(i, hash_str1 , probe[0])) succ[0]++ ;
            if(sp2.Find(i, hash_str2 , probe[1])) succ[1]++;

            if (db_hash1.Find(i, hash_str1 , probe[2])) succ[2]++;
            if (db_hash2.Find(i, hash_str2 , probe[3])) succ[3]++;

            if (cp1.Find(i, hash_str1 , probe[4])) succ[4]++;
            if (cp2.Find(i, hash_str2 , probe[5])) succ[5]++;
        }

        vector<double> res_probe(6);
        forn(6){
            res_probe[i] = (probe[i]*1.0)/1000; 
            //cout <<  (probe[i]*1.0)/1000 << " " << succ[i] <<  endl;
        }

        cout << "Hash Table Size :"  << n <<  endl;
        cout << "Collision Resolution Method   " <<  "Hash 1                                 " << "Hash 2                                 \n"; 
        cout << "                              " <<  "# of Collisions  "  << "Avg Probes " << " # of Collisions  "  << "   Avg Probes \n";
        cout << "Chaining                      " <<  sp1.getCollision()   <<  "             "<< res_probe[0] << "            " << sp2.getCollision() << "            " << res_probe[1] <<  endl;
        cout << "Double Hashing                " <<  db_hash1.getCollision()    <<  "             "<< res_probe[2] << "          " << db_hash2.getCollision() << "                " << res_probe[3] <<  endl;
        cout << "Custom Probing                " <<  cp1.getCollision()    <<  "             "<< res_probe[4] << "          " << cp2.getCollision() << "                " << res_probe[5] <<  endl << endl;


    }
    */





    
    return 0;
}