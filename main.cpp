#include <iostream>
#include "matrice.h"

int main() {
    matrice *A=new matrice(4,4);
    //matrice *B=new matrice(2,2);
    matrice *C= nullptr;
    A->initialize();
    A->print();
    //std::cout<<A->det();
    int nswaps;
    //C=A->lad(&nswaps);
    //B->initialize();
    //C=A->lad(&nswaps);
    //B->print();
    C=A->inv();
    //C=C->inv();
    //C=(*C)*(*A);
    //C=A->directsolve();
    if(C!= nullptr)
        C->print();
    //double det= A->det();
    //std::cout<<det<<std::endl;



    return 0;
}
