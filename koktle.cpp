//
// Created by Zoli on 2024. 04. 13..
//

#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "koktle.h"
#include "Ital.h"
#include "memtrace.h"

//konstruktor ami beállítja a koktel
Koktle::Koktle():nev(nullptr), alapanyag_db(0), alapanyagok(nullptr), menyiseg(nullptr){
}


Koktle::Koktle(Italok &italok):nev(nullptr), alapanyag_db(0), alapanyagok(nullptr), menyiseg(nullptr){
    setNev();
    std::cout<<"Alapanyagok szama: ";
    size_t alapanyag_szam = size_beolvas();
    for (size_t i=0; i<alapanyag_szam; i++){
        this->addAlapanyag(italok);
    }
}

void Koktle::kiir() const {
    std::cout<<"Koktel neve: "<<this->nev;
    for (size_t i=0; i<this->alapanyag_db; i++){
        std::cout<<" ["<<1+i<<"] "<<"alapanyag: "<<alapanyagok[i]->getTipusNev()<<" "<<alapanyagok[i]->getNev() <<" Mennyiseg: "<<this->menyiseg[i];
    }
}

void Koktle::addAlapanyag(Italok &italok) {
    Ital **uj_alapanyagok = new Ital*[this->alapanyag_db+1];
    unsigned int *uj_mennyiseg = new unsigned int[this->alapanyag_db+1];
    for (size_t i=0; i<this->alapanyag_db; i++){
        uj_alapanyagok[i] = this->alapanyagok[i];
        uj_mennyiseg[i] = this->menyiseg[i];
    }
    italok.kiir_index();
    std::cout<<"\nAlapanyag index: ";
    size_t index=size_beolvas();
    while (index>italok.getdb()){
        std::cout<<"Hibas index!"<<std::endl;
        italok.kiir_index();
        std::cout<<"\nAlapanyag index: ";
        index=size_beolvas();
    }
    if(index==0){
        italok.addItal();
        index=italok.getdb();
        italok.kiirF();
    }
    uj_alapanyagok[this->alapanyag_db] = italok.getItalCsilag(index-1);
    std::cout<<" Mennyiseg: ";
    uj_mennyiseg[this->alapanyag_db] = unsigned_int_beolvas();
    delete [] this->alapanyagok;
    delete [] this->menyiseg;
    this->alapanyagok = uj_alapanyagok;
    this->menyiseg = uj_mennyiseg;
    this->alapanyag_db++;
}

void Koktle::removeAlapanyag() {
    kiir();
    std::cout<<"torolni kivant Alapanyag index: ";
    size_t index=size_beolvas();
    while (index>=this->alapanyag_db){
        std::cout<<"Hibas index!"<<std::endl;
        kiir();
        std::cout<<"torolni kivant Alapanyag index: ";
        index=size_beolvas();
    }
    if(index==0) {
        std::cout<<"a koktelnak nincsen alapnyagai!"<<std::endl;
        return;
    }
    Ital **uj_alapanyagok = new Ital*[this->alapanyag_db-1];
    unsigned int *uj_mennyiseg = new unsigned int[this->alapanyag_db-1];
    for (size_t i=0; i<index-1; i++){
        uj_alapanyagok[i] = this->alapanyagok[i];
        uj_mennyiseg[i] = this->menyiseg[i];
    }
    for (size_t i=index-1; i<this->alapanyag_db-1; i++) {
        uj_alapanyagok[i] = this->alapanyagok[i+1];
        uj_mennyiseg[i] = this->menyiseg[i+1];
    }
    delete [] this->alapanyagok;
    delete [] this->menyiseg;
    this->alapanyagok = uj_alapanyagok;
    this->menyiseg = uj_mennyiseg;
    --alapanyag_db;
    if(alapanyag_db) {
        delete [] this->alapanyagok;
        delete [] this->menyiseg;
        alapanyagok=nullptr;
        menyiseg=nullptr;
    }

}

void Koktle::removeAlapanyag(Ital *ital) {
    size_t index=0;
    while (tartalmaz_e(ital)) {
        if(ital==alapanyagok[index]){
            Ital **uj_alapanyagok = new Ital*[this->alapanyag_db-1];
            unsigned int *uj_mennyiseg = new unsigned int[this->alapanyag_db-1];
            for (size_t i=0; i<index; i++){
                uj_alapanyagok[i] = this->alapanyagok[i];
                uj_mennyiseg[i] = this->menyiseg[i];
            }
            for (size_t i=index; i<this->alapanyag_db-1; i++){
                uj_alapanyagok[i] = this->alapanyagok[i+1];
                uj_mennyiseg[i] = this->menyiseg[i+1];
            }
            delete [] this->alapanyagok;
            delete [] this->menyiseg;
            this->alapanyagok = uj_alapanyagok;
            this->menyiseg = uj_mennyiseg;
            --alapanyag_db;
            if(alapanyag_db==0) {
                delete [] this->alapanyagok;
                delete [] this->menyiseg;
                menyiseg=nullptr;
                alapanyagok=nullptr;
                return;
            }
        }
        ++index;
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

bool Koktle::tartalmaz_e(const ital_tipus tipus) const {
    for (size_t i=0; i<this->alapanyag_db; i++){
        if (tipus == alapanyagok[i]->getTipus()){
            return true;
        }
    }
    return false;
}

void Koktle::setNev() {
    std::cout<<"Koktel neve: ";
    delete nev;
    nev = hoszusor_olvas();
}

char *Koktle::getNev() const {
    return this->nev;
}

void Koktle::Set(Italok &italok) {
    size_t valaszto;
    do{
        std::cout<<"Mit szeretne csinalni?\n1 - alapanyag hozzaadasa\n2 - alapanyag torlese\n3 - szoveg_olvsa modositasa\n4 - viszalepes"<<std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        valaszto=size_beolvas();
        switch (valaszto) {
            case 1:
                this->addAlapanyag(italok);
                break;
            case 2:
                this->removeAlapanyag();
                break;
            case 3:
                setNev();
                break;
            case 4:
                break;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
            break;
        }

    }while (valaszto!=4);
}



Koktle::~Koktle() {
    delete [] this->nev;
    delete [] this->alapanyagok;
    delete [] this->menyiseg;
}

Koktle::Koktle(char *nev, size_t alapanyag_db, Ital **alapanyagok, unsigned int *menyiseg) {
    this->nev = nev;
    this->alapanyag_db = alapanyag_db;
    this->alapanyagok = alapanyagok;
    this->menyiseg = menyiseg;
}

Koktlok::Koktlok() {
    this->koktel_db = 0;
    this->koktelok = nullptr;
}

size_t Koktlok::getKoktelDb() const {
    return  this->koktel_db;
}

Koktle *Koktlok::getKoktel_csilag(size_t index) const {
    if(index>=this->koktel_db){
        if(koktel_db==0)
            throw "urse a tomb";
        throw "tulindexeles";
    }
    return this->koktelok[index];
}


Koktle& Koktlok::getKoktel(size_t index) const {
    if(index>=this->koktel_db){
        if(koktel_db==0)
            throw "urse a tomb";
        throw "tulindexeles";
    }
    return *this->koktelok[index];
}

void Koktlok::kiir() const {
    for (size_t i=0; i<this->koktel_db; i++){
        this->koktelok[i]->kiir();
    }
}

void Koktlok::addKoktel(Koktle *kap) {
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
    this->addKoktel(uj);
}

void Koktlok::removeKoktel() {
    this->kiir_index();
    std::cout<<"Torolni kivant koktel index: ";
    size_t index = size_beolvas();
    while (index>this->koktel_db){
        std::cout<<"Hibas index!"<<std::endl;
        this->kiir_index();
        std::cout<<"Torolni kivant koktel index: ";
        index = size_beolvas();
    }
    --index;
    if(koktel_db==0) {
        std::cout<<"urse nem tartalz koktelokat"<<std::endl;
        return;
    }
    Koktle** uj = new Koktle*[this->koktel_db-1];
    for (size_t i=0; i<index; i++){
        uj[i] = this->koktelok[i];
    }
    for (size_t i=index; i<this->koktel_db-1; i++){
        uj[i] = this->koktelok[i+1];
    }
    delete this->koktelok[index];
    delete [] this->koktelok;
    this->koktelok = uj;
    this->koktel_db--;
    if(koktel_db==0)
        delete [] this->koktelok;
        koktelok=nullptr;
}

void Koktlok::removeKoktel(size_t index) {
    if(index>=this->koktel_db){
        if(koktel_db==0) {
            std::cout <<"urse a tomb"<<std::endl;
            return;
        }
        std::cout<<"tulindexeles"<<std::endl;
        return;
    }
    Koktle** uj = new Koktle*[this->koktel_db-1];
    for (size_t i=0; i<index; i++){
        uj[i] = this->koktelok[i];
    }
    for (size_t i=index; i<this->koktel_db-1; i++){
        uj[i] = this->koktelok[i+1];
    }
    delete this->koktelok[index];
    delete [] this->koktelok;
    this->koktelok = uj;
    this->koktel_db--;
    if(koktel_db==0) {
        delete [] koktelok;
        koktelok=nullptr;
    }
}


void Koktlok::kiir_index() const {
    for (size_t i=0; i<koktel_db;++i) {
        std::cout << "[" << i+1 << "] ";
        koktelok[i]->kiir();
        std::cout << '\n';
    }
}

void Koktlok::Set(Italok &italok) {
    size_t valaszto;
    size_t index;
    Koktle* modosit;
    do{
        std::cout<<"Mit szeretne csinalni?\n1 - Koktel hozzaadasa\n2 - Koktel torlese\n3 - Koktel modositas\n4 - koktelok kiirasa\n5 - viszalepes"<<std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        valaszto=size_beolvas();
        switch (valaszto) {
            case 1:
                this->addKoktel(italok);
                break;
            case 2:
                this->removeKoktel();
                break;
            case 3:
                kiir_index();
                std::cout<<"\nAdja meg a modositani kivant koktel indexet: ";
                index=size_beolvas();
                if(index>koktel_db){
                    std::cout<<"Hibas index!"<<std::endl;
                    break;
                }
                if(index==0)
                    break;
                modosit=getKoktel_csilag(index-1);
                modosit->Set(italok);
                break;
            case 4:
                kiir_index();
            case 5:
                break;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
                break;
        }

    }while (valaszto!=5);
    kiirF();
}

void Koktlok::veltel_ajanlas() {
    srand(time(0));
    size_t rand_index=rand()% koktel_db;
    koktelok[rand_index]->kiir();
    std::cout<<"\n";
    vait();
}

void Koktlok::lista_alapanyagok_szerint() const {
    ital_tipus tipus=tipus_valszto();
    for (size_t i=0; i<koktel_db; i++){
        if(koktelok[i]->tartalmaz_e(tipus)){
            koktelok[i]->kiir();
            std::cout<<"\n";
        }
    }
    vait();
}


Koktlok::~Koktlok() {
    for (size_t i=0; i<this->koktel_db; i++){
        delete koktelok[i];
    }
    delete [] koktelok;
}

bool Koktlok::removeAlapanyag_Italok(size_t index, Ital *alpanyg) {
    std::cout<<"Ezt az alapnyagot akarjuk torolni:\n";
    alpanyg->kiir();
    std::cout<<"\nEzt az alapnyagot tartalmazo koktel"<<std::endl;
    koktelok[index]->kiir();
    size_t valaszto;
    do{
        std::cout<<"\n1 - egesz koktel torles\n 2 - csakk az alapanyg torles\n 3 - visszalepes"<<std::endl;
        valaszto=size_beolvas();
        switch (valaszto) {
            case 1:
                removeKoktel(index);
                kiirF();
                return false;
            case 2:
                koktelok[index]->removeAlapanyag(alpanyg);
                kiirF();
                return false;
            case 3:
                return true;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
            break;
        }
    }while (valaszto!=3);
    return true;
}

