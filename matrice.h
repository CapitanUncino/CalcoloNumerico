//
// Created by alessio on 17/03/22.
//

#ifndef CALCOLONUMERICO_MATRICE_H
#define CALCOLONUMERICO_MATRICE_H


class matrice {
private:
    int nrighe;
    int ncolonne;
    double** buffer;


public:
    matrice(int m,int n);

    matrice(matrice* that);

    ~matrice();

    void initialize();

    matrice* lad();

    void print() const;





    matrice* operator=(matrice* that);

    friend matrice* operator+(matrice left, matrice right);

    friend matrice* operator*(matrice left, matrice right);

    matrice* operator^(int exp);



private:
   void copy_helper(matrice* that);
   void cleaning_helper();
};


#endif //CALCOLONUMERICO_MATRICE_H
