#include<bits/stdc++.h>
#include<random>
using namespace std;

#define forn(n) for (int i = 0 ; i < n ; i++) 

typedef long long ll ;



typedef std::mt19937 rng_type;
std::uniform_int_distribution<rng_type::result_type> udist(1, 26);

rng_type rng;


int main (){

    freopen("word.txt","w", stdout);

    std::random_device rd; 
    rng_type gen(rd()); 

    std::uniform_int_distribution<int> distribution(5, 10); 

    vector<string> strings;

    forn(1000){
        int len = distribution(gen);
    
        string str=""; 
        for (int j = 0 ; j<len ; j++){
            int curr = udist(gen);
            char x = 'a'+curr-1;
            str+=x; 
            
        }

        //cout  << str << endl;
        strings.push_back(str);
    }

   
   
    
    return 0;
}