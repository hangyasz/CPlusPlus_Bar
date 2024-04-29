//
// Created by Zoli on 2024. 04. 13..
//

#include "koktle.h"
#include "Ital.h"
#include <cstring>
#include <limits>
#include <iostream>

bool alapanyag_letezik_e(Italok &italok,const char* nev){
    for (size_t i=0; i<italok.getdb(); i++){
        if (strcmp(italok.getItal(i).getNev(),nev)==0){
            return true;
        }
    }
    return false;
}

//konstruktor ami beállítja a koktel
Koktle::Koktle(Italok &italok) {
    std::cout<<"Koktel neve: ";
    this->nev = hoszusor_olvas();
    std::cout<<"Alapanyagok szama: ";
    while(!(std::cin >> this->alapanyag_db)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
    }
    this->alapanyagok = new Ital*[this->alapanyag_db];
    this->menyiseg = new unsigned int[this->alapanyag_db];
    for (size_t i=0; i<this->alapanyag_db; i++){
        italok.kiir_index();
        std::cout<<"\nAlapanyag index: ";
        size_t index;
        while(!(std::cin >> index) or index>italok.getdb()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
        }
        if(index==italok.getdb()){
            italok.addItal();
        }
        alapanyagok[i] = italok.getItalCsilag(index);
        std::cout<<" Mennyiseg: ";
        while(!(std::cin >> this->menyiseg[i])){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
        }
    }
}

void Koktle::kiir() const {
    std::cout<<"Koktel neve: "<<this->nev;
    for (size_t i=0; i<this->alapanyag_db; i++){
        std::cout<<" ["<<i<<"] "<<"alapanyag: "<<alapanyagok[i]->getTipusNev()<<" "<<alapanyagok[i]->getNev() <<" Mennyiseg: "<<this->menyiseg[i];
    }
}

bool Koktle::tartalmaz_e(Ital* kap) const {
    for (size_t i=0; i<this->alapanyag_db; i++){
        if (kap == alapanyagok[i]){
            return true;
        }
    }
    return false;
}


Koktle::~Koktle() {
    delete [] this->nev;
    delete [] this->alapanyagok;
    delete [] this->menyiseg;
}

Koktle::Koktle(Italok &italok, char *nev, size_t alapanyag_db, Ital **alapanyagok, unsigned int *menyiseg) {
    this->nev = nev;
    this->alapanyag_db = alapanyag_db;
    this->alapanyagok = new Ital*[this->alapanyag_db];
    this->menyiseg = new unsigned int[this->alapanyag_db];
    for (size_t i=0; i<this->alapanyag_db; i++){
        this->alapanyagok[i] = alapanyagok[i];
        this->menyiseg[i] = menyiseg[i];
    }
}

void Koktle::kiirF(std::ofstream &os) const {
    os<<this->nev<<"><";
    os<<this->alapanyag_db<<">{";
    for (size_t i=0; i<this->alapanyag_db; i++){
        os<<"<"<<this->alapanyagok[i]->getNev()<<"><";
        os<<this->menyiseg[i]<<">";
    }
    os<<"}";
}

Koktlok::Koktlok() {
    this->koktel_db = 0;
    this->koktelok = nullptr;
}

size_t Koktlok::getKoktelDb() const {
    return  this->koktel_db;
}

Koktle* Koktlok::getKoktel(size_t index) const {
    if(index>=this->koktel_db){
        throw "tulindexeles";
    }
    return this->koktelok[index];
}

void Koktlok::kiir() const {
    for (size_t i=0; i<this->koktel_db; i++){
        this->koktelok[i]->kiir();
    }
}

void Koktlok::addKoktel(Italok &italok, Koktle *kap) {
    Koktle** uj = new Koktle*[this->koktel_db+1];
    for (size_t i=0; i<this->koktel_db; i++){
        uj[i] = this->koktelok[i];
    }
    uj[this->koktel_db] = kap;
    delete [] this->koktelok;
    this->koktelok = uj;
    this->koktel_db++;
}

void Koktlok::addKoktel(Italok &italok) {
    Koktle* uj = new Koktle(italok);
    this->addKoktel(italok, uj);
}

