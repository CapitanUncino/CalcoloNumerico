#include <iostream>
#include "matrice.h"

int main() {
    matrice *A=new matrice(4,1);
    matrice *B=new matrice(1,4);
    matrice *C;
    A->initialize();
    A->print();
    B->initialize();
    B->print();
    C=(*A)*(*B);
    if(C!= nullptr)
        C->print();



    return 0;
}
