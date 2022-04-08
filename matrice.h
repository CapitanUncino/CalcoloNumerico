//
// Created by alessio on 17/03/22.
//

#ifndef CALCOLONUMERICO_MATRICE_H
#define CALCOLONUMERICO_MATRICE_H


class matrice {
private:

    int nrighe;
    int ncolonne;
    double** buffer= nullptr;


public:

    matrice(int m,int n);

    matrice(matrice* that);

    ~matrice();

    void initialize();

    matrice* lad(int *nswaps);

    double det();

    void print() const;

    matrice& operator =(const matrice& that);

    matrice* directsolve();

    friend matrice* operator+(const matrice left,const matrice right);

    friend matrice* operator*(const matrice left,const matrice right);

    matrice* operator^(int exp);



private:
   void copy_helper(const matrice* that);
   void cleaning_helper();
};


#endif //CALCOLONUMERICO_MATRICE_H
