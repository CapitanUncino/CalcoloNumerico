//
// Created by alessio on 17/03/22.
//

#ifndef CALCOLONUMERICO_MATRICE_H
#define CALCOLONUMERICO_MATRICE_H


class matrice {
private:
    const int nrighe;
    const int ncolonne;
    double** buffer;


public:
    matrice(int m,int n);

    void initialize();

    void print() const;

    friend matrice* operator+(matrice left, matrice right);

    friend matrice* operator*(matrice left, matrice righr);


};


#endif //CALCOLONUMERICO_MATRICE_H
