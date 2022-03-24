//
// Created by alessio on 17/03/22.
//
#include "iostream"
#include "matrice.h"

matrice::matrice(int m, int n):nrighe(m),ncolonne(n){

    buffer=new double* [nrighe];
    for(int i=0;i<nrighe;i++){
        buffer[i]=new double[ncolonne];
    }
}


void matrice::initialize() {
    for(int i=0;i<nrighe;i++){
        for(int j=0;j<ncolonne;j++){
            std::cout<<"inserisci elemento["<<i+1<<"]["<<j+1<<"]"<<std::endl;
            std::cin>>buffer[i][j];
        }
    }
}

void matrice::print() const{
    std::cout<<std::endl;
    for(int i=0;i<nrighe;i++){
        for(int j=0;j<ncolonne;j++){
            std::cout<<buffer[i][j]<<"   ";
        }

        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

matrice* operator+(matrice left, matrice right){

    if (left.ncolonne!=right.ncolonne||left.nrighe!=right.nrighe)
        return nullptr;
    matrice *res=new matrice(left.ncolonne,left.nrighe);

    for(int i=0;i<left.nrighe;i++){
        for(int j=0;j<left.ncolonne;j++){
                res->buffer[i][j]=left.buffer[i][j]+right.buffer[i][j];
        }
    }
    return res;
}

matrice* operator*(const matrice left, matrice right){

    if (left.ncolonne!=right.nrighe)
        return nullptr;

    matrice *res=new matrice(right.ncolonne,left.nrighe);
    int sum;

    for(int i=0;i<left.nrighe;i++){
        for(int j=0;j<right.ncolonne;j++){
            sum=0;
            for(int k=0;k<left.ncolonne;k++){
                sum+=left.buffer[i][k]*right.buffer[k][j];
            }
            res->buffer[i][j]=sum;
        }
    }
    return res;
}
