#include <iostream>
#include "matrice.h"

int main() {
    matrice *A=new matrice(3,3);
    //matrice *B=new matrice(2,3);
    matrice *C;
    A->initialize();
    A->print();
    C=A->lad();
    //B->initialize();
    //B->print();
    //C=(*A)*(*B);
    if(C!= nullptr)
        C->print();



    return 0;
}
