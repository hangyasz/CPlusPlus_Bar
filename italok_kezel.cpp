//
// Created by Zoli on 2024. 04. 13..
//

#include <iostream>
#include <limits>
#include "Ital.h"

Italok::Italok() :ListaItalok(nullptr), db(0) {}

Italok::~Italok() {
    for (size_t i = 0; i < db; i++) {
        delete ListaItalok[i];
    }
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

void Italok::addItal() {
    Ital **uj=new Ital*[db+1];
    for(size_t i=0;i<db;i++){
        uj[i]=ListaItalok[i];
    }
    uj[db]=italok_bevitel();
    delete [] ListaItalok;
    ListaItalok=uj;
    db++;
    this->kiirF();
}

void Italok::addItal(Ital *kap) {
    Ital **uj=new Ital*[db+1];
    for(size_t i=0;i<db;i++){
        uj[i]=ListaItalok[i];
    }
    uj[db]=kap;
    delete [] ListaItalok;
    ListaItalok=uj;
    db++;
}


void Italok::addItal(char *nev, ital_tipus tipus) {
    switch(tipus) {
        case bor:
            this->addItal(new Bor(nev,bor));
            break;
        case whiskey:
            this->addItal(new Wiskey(nev,whiskey));
            break;
        case gin:
            this->addItal(new Gin(nev,gin));
            break;
        case rum:
            this->addItal(new Rum(nev,rum));
            break;
        case tequila:
            this->addItal(new Tequila(nev,tequila));
            break;
        case sor:
            this->addItal(new Sor(nev,sor));
            break;
        case gyumolcsle:
            this->addItal(new Gyumolcsle(nev,gyumolcsle));
            break;
        case alkohols:
            this->addItal(new SzeszesItalok(nev,alkohols));
            break;
        case alkohol_mentes:
            this->addItal(new  Ital(nev,alkohol_mentes));
            break;
        default:
            std::cout << "Hibás típus! Nem létezik ilyen tipus kerem vigye fel" << std::endl;
            this->addItal();
            delete [] nev;
        break;
    }
    this->kiirF();
}

size_t Italok::getdb() const {
    return db;
}

void Italok::kiir_index() {
    if(db==0){
        std::cout<<"Nincs ital a listaban!"<<std::endl;
        return;
    }
    std::cout<<"["<<0<<"] "<<*ListaItalok[0];
    for(size_t i=1;i<db;i++){
        std::cout<<"\n["<<i<<"] "<<*ListaItalok[i];
    }
    std::cout<<std::endl;
}


void Italok::removeItal() {
    this->kiir_index();
    size_t index;
    std::cout<<"\nAdja meg a torolni kivant ital indexet: ";
    while(!(std::cin >> index)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
    }
    if(index>=db){
        std::cout<<"Hibas index!"<<std::endl;
        return;
    }
    Ital **tmp=new Ital*[db-1];
    for(size_t i=0;i<index;i++){
        tmp[i]=ListaItalok[i];
    }
    delete ListaItalok[index];
    db--;
    for(size_t i=index;i<db;i++){
        tmp[i]=ListaItalok[i+1];
    }
    delete [] ListaItalok;
    ListaItalok=tmp;
}

Ital &Italok::getItal(size_t index) const {
    if (index >= db) {
        throw "Hibas index!";
    }
    return *ListaItalok[index];
}

Ital *Italok::getItalCsilag(size_t index) const {
    if (index >= db) {
        throw "Hibas index!";
    }
    return ListaItalok[index];
}


void Italok::setItalok() {
    size_t valaszto;
    do{
        std::cout<<"Mit szeretne csinalni?\n1 - Ital hozzaadasa\n2 - Ital torlese\n3 - Ital modositasa\n4 - viszalepes"<<std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        while(!(std::cin >> valaszto)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
        }
        switch (valaszto) {
            case 1:
                this->addItal();
                break;
            case 2:
                this->removeItal();
                break;
            case 3: {
                this->kiir_index();
                size_t index;
                std::cout<<"\nAdja meg a modositani kivant ital indexet: ";
                while(!(std::cin >> index)){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
                }
                if(index>=db){
                    std::cout<<"Hibas index!"<<std::endl;
                    break;
                }
                Ital modosit=getItal(index);
                modosit.Set();
                break;
            }
            case 4:
                break;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
                break;
        }

    }while (valaszto!=4);
}


Ital* Italok::italok_bevitel() {
    ital_tipus tipus=tipus_bevitel();
    switch(tipus) {
        case bor:
            return new Bor(bor);
        case whiskey:
            return new Wiskey(whiskey);
        case gin:
            return new Gin(gin);
        case rum:
            return new Rum(rum);
        case tequila:
            return new Tequila(tequila);
        case sor:
            return new Sor(sor);
        case gyumolcsle:
            return new Gyumolcsle(gyumolcsle);
        case alkohols:
            return new SzeszesItalok(alkohols);
        case alkohol_mentes:
            return new  Ital(alkohol_mentes);
        default:
            std::cout << "Hibás típus!" << std::endl;
        break;
    }
}


ital_tipus tipus_bevitel() {
    int tipus=0;
    do{
        std::cout << "Adja meg az ital tipusat (1 - Bor, 2 - Wiskey, 3 - Gin, 4 - Rum, 5 - Tequila, 6 - Sor, 7 - Gyumolcsle, 8 - Alkohols, 9 - Alkohol mentes ): ";
        while(!(std::cin >> tipus)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
        }

        switch(tipus) {
            case 1:
                return bor;
            case 2:
                return whiskey;
            case 3:
                return gin;
            case 4:
                return rum;
            case 5:
                return tequila;
            case 6:
                return sor;
            case 7:
                return gyumolcsle;
            case 8:
                return alkohols;
            case 9:
                return alkohol_mentes;
            default:
                std::cout << "Hibás típus!" << std::endl;
            break;
        }
    } while(tipus<1 || tipus>9);
}

