//
// Created by alessio on 17/03/22.
//
#include "iostream"
#include "matrice.h"
const double eps=0.00000000001;

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

    cleaning_helper();
}

 matrice* matrice::lad(int *nswaps) {

    matrice* res = new matrice(*this);
    int npassi=0;
    *nswaps=0;

    while(npassi<nrighe) {

        //_______________scambio righe
        int maxrow = npassi;
        for (int i = npassi; i < nrighe; i++) {
            if (std::abs(res->buffer[i][npassi]) > std::abs(res->buffer[maxrow][npassi]))
                maxrow = i;
        }
        double *tmp;
        tmp = res->buffer[npassi];
        res->buffer[npassi] = res->buffer[maxrow];
        res->buffer[maxrow] = tmp;
        (*nswaps)++;

        //_______________somma righe
        if (res->buffer[npassi][npassi]>eps||buffer[npassi][npassi]<-eps) {
            double mul;
            for (int i = npassi + 1; i < nrighe; i++) {
                mul = res->buffer[i][npassi] / res->buffer[npassi][npassi];

                for (int j = npassi; j < ncolonne; j++) {
                    res->buffer[i][j] = res->buffer[i][j] - (res->buffer[npassi][j] * mul);
                }
            }
        }

    npassi++;
    }

    return res;
}

double matrice::det(){


    matrice *ladder;
    int nswaps;
    double det=1;
    ladder=lad(&nswaps);
    for(int i=0;i<nrighe;i++){
        det = det * ladder->buffer[i][i];
    }
    if (nswaps%2==1){
        det = det * -1;
    }
    return det;
}

void matrice::copy_helper(matrice const *that) {
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

    std::cout<<" nel posto "<<buffer<<std::endl;
    if (buffer!= nullptr) {
        for (int i =0; i <nrighe; i++) {
            std::cout<<i<<" nel posto "<<buffer[i]<<std::endl;
            delete buffer[i]; //FIXME fix cleaning_helper and uncomment its calls
        }
        delete buffer;
        std::cout<<" fine matrice "<<std::endl;
        buffer=nullptr;
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
            if(buffer[i][j]>eps||buffer[i][j]<-eps)
                std::cout<<buffer[i][j]<<"   ";
            else
                std::cout<<0<<"   ";
        }

        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

matrice& matrice::operator = (const matrice& that){

    //if (&that==this)return nullptr;

    cleaning_helper();
    copy_helper(&that);
    return *this;
}

matrice* operator+(const matrice left,const matrice right){

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

matrice* operator*(const matrice left,const matrice right){

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
    *res = *this;
    for (int i = 1; i < exp; i++)
        res = (*res) * (*this);

    return res;
}


