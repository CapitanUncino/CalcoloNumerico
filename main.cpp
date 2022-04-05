#include <iostream>
#include "matrice.h"

int main() {
    matrice *A=new matrice(2,2);
    //matrice *B=new matrice(2,3);
    matrice *C;
    A->initialize();
    A->print();
    //int nswaps;
    //C=A->lad(&nswaps);
    //B->initialize();
    //B->print();
    C=A;
    C=(*A)^4;
    if(C!= nullptr)
        C->print();
    //double det= A->det();
    //std::cout<<det<<std::endl;



    return 0;
}
