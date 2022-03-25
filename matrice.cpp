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

matrice::matrice(matrice *that) {
    copy_helper(that);
}

matrice::~matrice() {

    //cleaning_helper();
}

void matrice::copy_helper(matrice *that) {
    nrighe=that->nrighe;
    ncolonne=that->ncolonne;

    buffer=new double* [nrighe];
    for(int i=0;i<nrighe;i++){
        buffer[i]=new double[ncolonne];
    }

    for(int i=0;i<nrighe;i++){
        for(int j=0;j<ncolonne;j++){

            buffer[i][j]=that->buffer[i][j];
        }
    }
}

void matrice::cleaning_helper() {

    if (buffer!= nullptr) {
        for (int i =0; i <nrighe; i++) {
            delete[] buffer[i]; //FIXME fix cleaning_helper and uncomment its calls
        }
        delete[] buffer;
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

matrice* matrice::operator=(matrice* that){

    if (that==this)return nullptr;

    cleaning_helper();
    //copy_helper(that);
    return this;
}

matrice* operator+(matrice left, matrice right){

    if (left.ncolonne!=right.ncolonne||left.nrighe!=right.nrighe)
        return nullptr;
    matrice *res=new matrice(left.nrighe,left.ncolonne);

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

    matrice *res=new matrice(left.nrighe,right.ncolonne);
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

matrice* matrice::operator^(int exp) {
    if(nrighe!=ncolonne||exp<1) return nullptr;
    matrice *res=new matrice(nrighe,ncolonne);
    res=this;
    for(int i=1;i<exp;i++){
        res=(*res)*(*this);
    }

    return res;
}

