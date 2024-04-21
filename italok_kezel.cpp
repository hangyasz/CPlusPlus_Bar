//
// Created by Zoli on 2024. 04. 13..
//

#include <iostream>
#include "Ital.h"

Italok::Italok() :ListaItalok(nullptr), db(0) {}
Italok::~Italok() {
    delete [] ListaItalok;
}

Italok::Italok(const Italok &italok) {
    db= italok.db;
    ListaItalok = new Ital*[db];
    for(size_t i=0;i<db;i++){
        ListaItalok[i]=italok.ListaItalok[i];
    }
}

Italok &Italok:: operator=(const Italok &italok) {
    if(this!=&italok){
        db=italok.db;
        delete [] ListaItalok;
        ListaItalok = new Ital*[db];
        for(size_t i=0;i<db;i++){
            ListaItalok[i]=italok.ListaItalok[i];
        }
    }
    return *this;
}

Ital* italok_bevitel() {
    int tipus=0;
    do{
        std::cout << "Adja meg az ital tipusát (1 - Bor, 2 - Wiskey, 3 - Gin, 4 - Rum, 5 - Tequila, 6 - Sor, 7 - Gyumolcsle, 8 - Alkohols, 9 - Alkohol mentes ): ";
        std::cin >> tipus;

        switch(tipus) {
            case 1:
                return new Bor(ital_tipus::bor);
            case 2:
                return new Wiskey(ital_tipus::whiskey);
            case 3:
                return new Gin(ital_tipus::gin);
            case 4:
                return new Rum(ital_tipus::rum);
            case 5:
                return new Tequila(ital_tipus::tequila);
            case 6:
                return new Sor(ital_tipus::sor);
            case 7:
                return new Gyumolcsle(ital_tipus::gyumolcsle);
            case 8:
                return new SzeszesItalok(ital_tipus::alkohols);
            case 9:
                return new  Ital(ital_tipus::alkohol_mentes);
            default:
                std::cout << "Hibás típus!" << std::endl;
        }
    } while(tipus<1 || tipus>9);
}

