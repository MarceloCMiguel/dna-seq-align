/*
ALGORITMO SMITH-WATERMAN
Entrada: Duas sequencias de DNA a[i] e b[j], de tamanhos n e m respectivamente
Saída: score máximo de alinhamento 
*/


#include <iostream>
#include <vector>
#include<string.h>
#include <algorithm>
#include <random>
using namespace std;

#define P 100

struct SubstringValue{
    string substring;
    int score;
};

int w_score(char a,char b){
    if (a==b){
        return 2;
    }
    else if((a=='-')|| (b =='-')){
        return -1;
    }
    else{
        return -1;
    }
}

string create_substring(string seq,int index, int random_size){

    string substring;
    while((substring.size() < random_size) && (index < seq.size())){

        substring.push_back(seq[index]);
        index++;
    }
    return substring;
}

int calculate_score(string sa, string sb){
    int score = 0;
    for (int i = 0; i < sa.size();i++){
        if (sa[i] == sb[i]){
            score+=2;
        }
        else if ((sa[i]=='-')|| (sb[i] =='-')){
            score -=1;
        }
        else{
            score -=2;
        }
    }
    return score;
}




int main(){
    int n;
    int m;
    cin>>n>>m;
    cout<<"n: "<<n<<endl;
    cout<<"m: "<<m<<endl;
    string a;
    string b;
    cin>> a;
    
    cin>> b;
    cout<<"Seq a: "<<a<<endl;
    cout<<"Seq b: "<<b<<endl;
    cout<<endl;
    default_random_engine generator(123);
    uniform_int_distribution<int> distribution_k(1,m);
    // gerando numeros algumas vezes para garantir aleatoriedade
    for(int i = 0; i <5; i++){
        distribution_k(generator);    
    }
    int k;
    k = distribution_k(generator);
    // tamanho de K n pode ser maior que o tamanho da outra substring a
    while (k > a.size()){
        k = distribution_k(generator);
    }
    cout<<endl;
    cout<<"k: "<<k<<endl;
    uniform_int_distribution<int> distribution_b(0,m-k-1);
    int index_b = distribution_b(generator);

    uniform_int_distribution<int> distribution_a(0,n-k-1);
    string sb = create_substring(b,index_b,k);
    cout<<"Subsequence b: "<<sb<<endl;
    uniform_int_distribution<int> distribution_p(1,P);
    int p_ = distribution_p(generator);
    int score = -999; // apenas para garantir que no alguma subsequencia terá um score melhor
    vector<SubstringValue> sa_best_values;
    // salvando apenas strings para checar se já há no sa_best_values
    vector<string> all_seqs;
    cout<<"Subsequences a generated and yours scores: [ ";
    for (int l = 0; l<p_;l++){
        SubstringValue sa_temp;
        
        int index_a = distribution_a(generator);
        sa_temp.substring = create_substring(a,index_a,k);
        all_seqs.push_back(sa_temp.substring);
        sa_temp.score=calculate_score(sa_temp.substring,sb);
        if (sa_temp.score> score){
            score = sa_temp.score;
            sa_best_values.clear();
            sa_best_values.push_back(sa_temp);
        }
        else if(sa_temp.score == score){
            // evitando adicionar substrings iguais na lista
            if(!count(all_seqs.begin(),all_seqs.end(),sa_temp.substring)){
                sa_best_values.push_back(sa_temp);
            }   
        }
        cout<<sa_temp.substring<<" "<< sa_temp.score<<" | " ;
    }
    cout<<"]"<<endl<<endl;

    cout<<"Best Subsequence (highers scores) [ ";
    for (int i = 0; i < sa_best_values.size(); i++)
    {
        
        cout<<sa_best_values[i].substring<<" "<<sa_best_values[i].score<< " | ";
    }
    cout<<"]"<<endl;
    return 0;
    

}