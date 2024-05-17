//
// Created by Zoli on 2024. 04. 13..
//

#include <iostream>
#include <limits>
#include "Ital.h"
#include "koktle.h"
#include "memtrace.h"

Italok::Italok() :ListaItalok(nullptr), db(0) {}

Italok::~Italok() {
    for (size_t i = 0; i < db; i++) {
        delete ListaItalok[i];
    }
    delete [] ListaItalok;
}


bool Italok::tartaalmaz(String nev, ital_tipus tipus) {
    for(size_t i=0;i<db;i++){
        if(ListaItalok[i]->getTipus()==tipus and ListaItalok[i]->getNev()==nev )
            return true;
    }
    return false;
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


void Italok::addItal(String nev, ital_tipus tipus) {
    if(!tartaalmaz(nev,tipus)) {
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
                std::cerr << "Hibás típus!\n a program ezt a tipust nem egeszen tudja kezelni vegye fel a kapcsolatot a fejlesztokel\n addig meg tegyuk el egy hasonlo csoportva" << std::endl;
            this->addItal();
            break;
        }
        kiirF();
    }
}

size_t Italok::getdb() const {
    return db;
}

void Italok::kiir_index() {
    if(db==0){
        std::cout<<"Nincs ital a listaban!"<<std::endl;
        return;
    }
    std::cout<<"["<<1<<"] "<<*ListaItalok[0];
    for(size_t i=1;i<db;i++){
        std::cout<<"\n["<<1+i<<"] "<<*ListaItalok[i];
    }
    std::cout<<std::endl;
}



void Italok::removeItal() {
    kiir_index();
    size_t index;
    std::cout << "\nAdja meg a torolni kivant ital indexet: ";
    index = size_beolvas();
    while (index > db) {
        std::cout << "Hibas index!" << std::endl;
        index = size_beolvas();
    }
    if (index == 0)
        return;
    --index;
    if(db-1==0) {
        delete ListaItalok[0];
        delete [] ListaItalok;
        ListaItalok=nullptr;
        --db;
        return;
    }
    Ital **tmp = new Ital*[db - 1];
    for (size_t i = 0; i < index; i++) {
        tmp[i] = ListaItalok[i];
    }
    for (size_t i = index; i < db - 1; i++) {
        tmp[i] = ListaItalok[i + 1];
    }
    delete ListaItalok[index];
    db--;
    delete[] ListaItalok;
    ListaItalok = tmp;
}

void Italok::removeItal(Koktlok &k) {
    kiir_index();
    size_t index;
    std::cout << "\nAdja meg a torolni kivant ital indexet: ";
    index = size_beolvas();
    while (index > db) {
        std::cout << "Hibas index!" << std::endl;
        index = size_beolvas();
    }
    if (index == 0)
        return;
    --index;
    for(size_t i=0; i<k.getKoktelDb();++i) {
        Koktle* koktle=k.getKoktel_csilag(i);
        if(koktle->tartalmaz_e(ListaItalok[index])) {
            if(k.removeAlapanyag_Italok(i,ListaItalok[index]))
                return;
        }
    }
    if(db-1==0) {
        delete ListaItalok[0];
        delete [] ListaItalok;
        ListaItalok=nullptr;
    }
    Ital **tmp = new Ital*[db - 1];
    for (size_t i = 0; i < index; i++) {
        tmp[i] = ListaItalok[i];
    }
    for (size_t i = index; i < db - 1; i++) {
        tmp[i] = ListaItalok[i + 1];
    }
    delete ListaItalok[index];
    db--;
    delete[] ListaItalok;
    ListaItalok = tmp;
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


void Italok::setItalok(Koktlok &kap) {
    size_t valaszto;
    size_t index;
    Ital *modosit;
    do{
        std::cout<<"Mit szeretne csinalni?\n1 - Ital hozzaadasa\n2 - Ital torlese\n3 - Ital modositasa\n4 - Italok kiiras\n5 - viszalepes"<<std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        valaszto=size_beolvas();
        switch (valaszto) {
            case 1:
                this->addItal();
                break;
            case 2:
                this->removeItal(kap);
                break;
            case 3:
                this->kiir_index();
                std::cout<<"\nAdja meg a modositani kivant ital indexet: ";
                index=size_beolvas();
                if(index>db){
                    std::cout<<"Hibas index!"<<std::endl;
                    break;
                }
                if(index==0)
                    break;
                modosit=getItalCsilag(index-1);
                modosit->Set();
                break;
            case 4:
                this->kiir_index();
                break;
            case 5:
                break;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
                break;
        }

    }while (valaszto!=5);
    kiirF();
}


Ital* Italok::italok_bevitel() {
    ital_tipus tipus;
    do {
    tipus=tipus_valszto();
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
}while (true);
}

