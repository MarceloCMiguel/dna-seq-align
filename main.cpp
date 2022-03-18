/*
ALGORITMO SMITH-WATERMAN
Entrada: Duas sequencias de DNA a[i] e b[j], de tamanhos n e m respectivamente
Saída: score máximo de alinhamento 
*/


#include <iostream>
#include <vector>
#include<string.h>
#include <algorithm>
using namespace std;

struct Alinhamento{
    int i;
    int j;
    int valor;
    int salto; // 0 = diagonal; 1 = deleção; 2 = inserção; -1 = ultimo // 3 = vazio
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




int main(){
    int n;
    int m;
    cin>>n>>m;
    cout<<"n: "<<n<<endl;
    cout<<"m: "<<m<<endl;
    vector<vector<Alinhamento>> H;
    vector<char> a;
    vector<char> b;
    // a.push_back(' ');
    // b.push_back(' ');

    cout<<"Seq1: ";
    for (int i = 1; i <=n;i++){
        char temp;
        cin >> temp;
        a.push_back(temp);
        cout<<temp;
    }
    cout<<endl;


    cout<<"Seq2: ";
    for (int j = 1; j <=m;j++){
        char temp;
        cin >> temp;
        b.push_back(temp);
        cout<<temp;
    }
    cout<<endl;

    H.resize(n+1);

    for(int i = 0 ; i <= n ; i++)
    {
        //Grow Columns by n
        H[i].resize(m+1);
    }

    // calculando smithwaterman

    int i_maior;
    int j_maior;
    int maior = 0;

    for (int i =1; i<n+1;i++){
        for (int j = 1; j < m+1; j++){
            int diagonal = H[i-1][j-1].valor + w_score(a[i-1],b[j-1]);
            int delecao = H[i-1][j].valor - 1;
            int insercao = H[i][j-1].valor - 1;
            H[i][j].valor = max({0,diagonal,delecao,insercao});
            if (maior < H[i][j].valor){
                maior = H[i][j].valor;
                i_maior = i;
                j_maior = j;
            }
            if (H[i][j].valor == diagonal){
                H[i][j].salto = 0;
            }
            else if (H[i][j].valor == delecao){
                H[i][j].salto = 1;
            }
            else if (H[i][j].valor == insercao){
                H[i][j].salto = 2;
            }
            else{
                H[i][j].salto = -1;
            }
        }
    }
    // // print da matriz
    // cout<<"  ";
    // for (int j = 0; j <=m;j++){
    //     cout<<b[j]<<" ";
    // }
    // cout<<endl;
    // for (int i = 0; i<=n;i++){
    //     cout <<a[i]<<" ";
    //         for (int j = 0;j<=m;j++){
    //         cout<<H[i][j].valor<< " ";
    //     }
    //     cout<<endl;
    // }
    cout<<endl<<"Max: "<<maior<<endl<<"Posição ("<<i_maior<<","<<j_maior<<")"<<endl;
    Alinhamento posicao;
    posicao.i = i_maior;
    posicao.j = j_maior;
    posicao.valor = maior;
    posicao.salto = H[i_maior][j_maior].salto;
    string seq1 = "";
    string seq2 = "";
    while(posicao.valor>0 && posicao.i>0 && posicao.j>0){
        if(posicao.salto == 0){ //alinhamento
            seq1.push_back(a[posicao.i-1]);
            seq2.push_back(b[posicao.j-1]);
            posicao.i--;
            posicao.j--;
        }
        else if(posicao.salto ==1){ //deleção
            seq1.push_back(a[posicao.i-1]);
            seq2.push_back('-');
            posicao.i--;
        }
        else if(posicao.salto ==2){ //inserção                   
            seq1.push_back('-');
            seq2.push_back(b[posicao.j-1]);
            posicao.j--;
        }
        posicao.valor = H[posicao.i][posicao.j].valor;
        posicao.salto = H[posicao.i][posicao.j].salto;
        
    }
    reverse(seq1.begin(),seq1.end());
    reverse(seq2.begin(),seq2.end());
    cout<<seq2<<endl;
    cout<<seq1<<endl;
    return 0;
    

}