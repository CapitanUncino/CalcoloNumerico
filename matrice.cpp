//
// Created by alessio on 17/03/22.
//
#include "iostream"
#include "matrice.h"
#include "cmath"
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




 matrice* matrice::lad(int *nswaps) const{

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





double matrice::det() const{


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





matrice* matrice::directsolve() const{

    matrice *ladder;
    matrice *solution=new matrice(nrighe,1);
    int nswaps;
    double det;
    double sum;

    ladder = this->lad(&nswaps);
    det = ladder->det();
    if (det==0) return nullptr;

    for(int i=nrighe-1;i>=0;i--){

        sum=0;
        for(int j=i+1;j<nrighe;j++){
            sum=sum+ladder->buffer[i][j]*solution->buffer[j][0];
        }
        solution->buffer[i][0]=(ladder->buffer[i][ncolonne-1]-sum)/ladder->buffer[i][i];

    }

    return solution;
}


matrice* matrice::J_solve(double precision) const{

    matrice* solution=new matrice(nrighe,1);
    matrice* tmp=new matrice(nrighe,1);
    double sum;
    double diff;
    int maxsteps=100;
    int count=0;
    double scalar_res;
    double scalar_tmp;


    //TODO find a better start vector
    for(int i=0;i<nrighe;i++)
        tmp->buffer[i][0]=1.0;

    do {


        for (int i = nrighe - 1; i >= 0; i--) {

            sum = 0;
            for (int j = 0; j < nrighe; j++) {
                if(j!=i) {
                    sum = sum + this->buffer[i][j] * tmp->buffer[j][0];
                }
            }

            solution->buffer[i][0] = (this->buffer[i][ncolonne - 1] - sum) / this->buffer[i][i];

        }


        sum = 0;
        for (int i = 0; i < nrighe; i++)
            sum += pow(tmp->buffer[i][0], 2);

        scalar_tmp = sqrt(sum);

        sum = 0;
        for (int i = 0; i < nrighe; i++)
            sum += pow(solution->buffer[i][0], 2);

        scalar_res = sqrt(sum);

        diff = std::abs(scalar_res - scalar_tmp);

        if(isinfl(diff))return nullptr;


        *tmp = *solution;

        count++;


    } while (diff>precision&&count<maxsteps);

    if (count>=maxsteps) return nullptr;

    return solution;
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

    if (buffer!= nullptr) {
        for (int i =0; i <nrighe; i++) {
            delete buffer[i];
        }
        delete buffer;
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

    if (&that!=this) {

        cleaning_helper();
        copy_helper(&that);
    }

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

    matrice *op1=new matrice(nrighe,ncolonne);
    matrice *op2=new matrice(nrighe,ncolonne);
    *op1 = *this;
    *op2 = *this;
    for (int i = 1; i < exp; i++) {
        std::cout<<" nel posto "<<buffer[0]<<std::endl;
        op1 = (*op2) * (*op1);
    }
    return op1;
}



