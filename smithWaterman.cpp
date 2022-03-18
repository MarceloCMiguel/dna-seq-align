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
    int salto; // 0 = diagonal; 1 = deleção; 2 = inserção; -1 = ultimo
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
    vector<vector<int>> H;
    vector<char> a;
    vector<char> b;
    a.push_back(' ');
    b.push_back(' ');

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
    for (int i =1; i<n+1;i++){
        for (int j = 1; j < m+1; j++){
            int diagonal = H[i-1][j-1] + w_score(a[i],b[j]);
            int delecao = H[i-1][j] - 1;
            int insercao = H[i][j-1] - 1;
            H[i][j] = max({0,diagonal,delecao,insercao});
        }
    }
    // print da matriz
    cout<<"  ";
    for (int j = 0; j <=m;j++){
        cout<<b[j]<<" ";
    }
    cout<<endl;
    for (int i = 0; i<=n;i++){
        cout <<a[i]<<" ";
            for (int j = 0;j<=m;j++){
            cout<<H[i][j]<< " ";
        }
        cout<<endl;
    }

    // encontra maior
    int i_maior;
    int j_maior;
    int maior = 0;
    for (int i =0; i<=n;i++){
        for (int j = 0; j <= m; j++){
            if (maior < H[i][j]){
                maior = H[i][j];
                i_maior = i;
                j_maior = j;
            }
        }
    }
    cout<<endl<<"Max: "<<maior<<endl<<"Posição ("<<i_maior<<","<<j_maior<<")"<<endl;


    // alinhamento local ótimo

    int i = i_maior;
    int j = j_maior;
    int valor = maior;
    vector<Alinhamento> posicoes;
    Alinhamento posicao;
    posicao.i = i;
    posicao.j = j;
    posicao.salto = -1;
    posicoes.push_back(posicao);
    while(valor>0 && (i>0 && j>0)){
        Alinhamento posicao;
        // cout<<valor<<" "<<i<<" "<<j<<endl;
        int diagonal = H[i-1][j-1];
        int delecao = H[i-1][j];
        int insercao = H[i][j-1];
        if (diagonal >= delecao && diagonal >= insercao){
            i--;
            j--;
            valor = diagonal;
            posicao.salto = 0;
        }
        else if(delecao >= insercao){
            i--;
            valor = delecao;
            posicao.salto = 1;
        }
        else{
            j--;
            valor = insercao;
            posicao.salto = 2;
        }
        posicao.i = i;
        posicao.j = j;
        posicoes.push_back(posicao);
    }
    // cout<<valor<<" "<<i<<" "<<j<<endl;

    reverse(posicoes.begin(),posicoes.end());
    // cout<<endl;
    // for (int i =0; i <posicoes.size();i++){
    //     cout<<posicoes[i].salto<<" "<<posicoes[i].i<<" "<<posicoes[i].j<<endl;
    // }

    string seq1 = "";
    string seq2 = "";
    i = 0;


    for (int i =0;i< posicoes.size();i++){
        int posicao_i = posicoes[i].i;
        int posicao_j = posicoes[i].j;
        if(posicoes[i].salto == 0){ //alinhamento
            seq1.push_back(a[posicao_i+1]);
            seq2.push_back(b[posicao_j+1]);
        }
        else if(posicoes[i].salto ==1){ //deleção
            seq1.push_back(a[posicao_i+1]);
            seq2.push_back('-');
        }
        else if(posicoes[i].salto ==2){ //inserção                   
            seq1.push_back('-');
            seq2.push_back(b[posicao_j+1]);
        }
    }

    cout<<seq1<<endl;
    cout<<seq2<<endl;
    return 0;
    

}