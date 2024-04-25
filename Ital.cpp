//
// Created by Zoli on 2024. 04. 12..
//

#include "Ital.h"
#include <iostream>
#include <cstring>
#include "string_kezez.h"
#include <limits>
#include <ctime>


Ital::Ital(ital_tipus tipus) {
    std::cout << "Adja meg az ital nevet: " << std::endl;
    this->nev = hoszusor_olvas();
    std::cout << "Adja meg az ital gyarojat: " << std::endl;
    this->gyarto = hoszusor_olvas();
    this->tipus = tipus;
}

Ital::Ital() {
    nev=nullptr;
    gyarto=nullptr;
}

Ital::~Ital() {
    delete[] nev;
    delete[] gyarto;
}

char * Ital::getNev() const
{
    return nev;
}

char *Ital::getGyarto() const {
    return gyarto;
}

ital_tipus Ital::getTipus() const {
    return tipus;
}

const char*  Ital::getTipusNev(ital_tipus tipus) const {
    switch (tipus) {
        case alkohols: return "alkohols";
        case alkohol_mentes: return "alkohol_mentes";
        case bor: return "bor";
        case whiskey: return "whiskey";
        case gin: return "gin";
        case rum: return "rum";
        case tequila: return "tequila";
        case sor: return "sor";
        case gyumolcsle: return "gyumolcsle";
        default: return "ismeretlen";
    }
}

void Ital::setNev() {
    delete[] this->nev;
    std::cout << "Adja meg az ital nevet: " << std::endl;
    this->nev = hoszusor_olvas();
}

void Ital::setNev(char* kap ) {
    delete [] this->nev;
    nev=kap;
}

void Ital::setGyarto() {
    delete[] this->gyarto;
    std::cout << "Adja meg az ital gyarojat: " << std::endl;
    this->gyarto = hoszusor_olvas();
}

void Ital::setGyarto(char* kap) {
    delete [] this->gyarto;
    gyarto=kap;
}

void Ital:: kiir()  const{
    std::cout << "Nev: " << nev;
    std::cout << " Gyarto: " << gyarto;
    std::cout << " Fajtaja: " << getTipusNev(tipus);
}

void Ital::setTipus() {
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
                tipus=bor;
                return;
            case 2:
                tipus=whiskey;
                return;
            case 3:
               tipus=gin;
                return;
            case 4:
                tipus=rum;
            case 5:
                tipus=tequila;
            case 6:
                tipus=sor;
            case 7:
                tipus=gyumolcsle;
            case 8:
                tipus=alkohols;
            case 9:
                tipus=alkohol_mentes;
            default:
                std::cout << "Hibás típus valaztas!" << std::endl;
        }
    } while(tipus<1 || tipus>9);
}

void Ital::setTipus(ital_tipus kap) {
    tipus=kap;
}



void Ital::Set() {
    size_t valasz;
    do {
        this->kiir();
        std::cout<< "Mit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-tipus, 4-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        while(!(std::cin >> valasz)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
        }
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setTipus();
            break;
            case 4: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=4);
}

//szeszes italok

SzeszesItalok::SzeszesItalok(ital_tipus tipus) : Ital(tipus) {
    std::cout << "Adja meg az alkohol tartalmat: " << std::endl;
    while(!(std::cin >> alkoholTartalom)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szam erteket!" << std::endl;
    }
}

SzeszesItalok::SzeszesItalok() : Ital(){
}

float SzeszesItalok::getAlkoholTartalom() const {
    return alkoholTartalom;
}

void SzeszesItalok::setAlkoholTartalom() {
    std::cout << "Adja meg az alkohol tartalmat: " << std::endl;
    while(!(std::cin >> alkoholTartalom)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szam erteket!" << std::endl;
    }
}

void SzeszesItalok::setAlkoholTartalom(float kap) {
    alkoholTartalom=kap;
}

void SzeszesItalok::kiir() const {
    Ital::kiir();
    std::cout << " Alkohol tartalom: " << alkoholTartalom;
}

void SzeszesItalok::Set() {
    size_t valasz;
    do {
        this->kiir();
        std::cout<< "Mit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-tipus,4-alkohol, 5-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        while(!(std::cin >> valasz)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
        }
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setTipus();
            break;
            case 4:
                this->setAlkoholTartalom();
            break;
            case 5: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=5);
}

//bor

Bor::Bor(ital_tipus tipus) : SzeszesItalok(tipus) {
    std::cout << "Adja meg az evjaratot: " << std::endl;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    evjarat=1901 + ltm->tm_year;
    while (evjarat > 1900 + ltm->tm_year) {
        while(!(std::cin >> evjarat)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Hibas bemenet. Kerlek, adj meg egy szam erteket!" << std::endl;
        }
        std::cout << "Hibas evjarat!" << std::endl;
    }

    int szin = 0;
    while (szin != 1 && szin != 2 && szin != 3) {
        std::cout << "valasza kia bor szinet [1]voros,[2]rose,[3]feher" << std::endl;
        std::cin.sync();
        std::cin >> szin;
        switch (szin) {
            case 1:
                this->szin = voros;
            break;
            case 2:
                this->szin = rose;
            break;
            case 3:
                this->szin = feher;
            break;
            default:
                std::cout << "nem megfelelo szamot adott meg" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    std::cout << "Adja meg a fajtak szamat: " << std::endl;
    while(!(std::cin >> fajta_db)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szam erteket!" << std::endl;
    }
    this->fajta = new char *[fajta_db];
    for (int i = 0; i < fajta_db; i++) {
        std::cout << "Adja meg a fajtat: " << std::endl;
        fajta[i] = hoszusor_olvas();
    }
}

Bor::Bor():SzeszesItalok() {
    fajta=nullptr;
}

Bor::~Bor() {
    for (int i = 0; i < fajta_db; i++) {
        delete[] fajta[i];
    }
    delete[] fajta;
}

unsigned int Bor::getEvjarat() const {
    return evjarat;
}

szinek_bor Bor::getSzin() const {
    return szin;
}

std::string getSzinNev(szinek_bor szin) {
        switch (szin) {
            case voros: return "voros";
            case rose: return "rose";
            case feher: return "feher";
            default: return "ismeretlen";
        }
    }

const char* Bor::getSzinNev(szinek_bor szin) const{
    switch (szin) {
        case voros: return "voros";
        case rose: return "rose";
        case feher: return "feher";
        default: return "ismeretlen";
    }
}

void Bor::setEvjarat() {
    std::cout << "Adja meg az evjaratot: " << std::endl;
    while(!(std::cin >> evjarat)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szam erteket!" << std::endl;
    }
}

void Bor::setEvjarat(unsigned int kap) {
        evjarat=kap;
}


void Bor::setSzin() {
    int szin = 0;
    while (szin != 1 && szin != 2 && szin != 3) {
        std::cout << "valasza kia bor szinet [1]voros,[2]rose,[3]feher" << std::endl;
        std::cin.sync();
        std::cin >> szin;
        switch (szin) {
            case 1:
                this->szin = voros;
            break;
            case 2:
                this->szin = rose;
            break;
            case 3:
                this->szin = feher;
            break;
            default:
                std::cout << "nem megfelelo szamot adott meg" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

void Bor::setSzin(szinek_bor kap) {
    szin=kap;
}

void Bor::setFajta_db(size_t kap) {
    fajta_db=kap;
}

void Bor::setFajta_string(char **kap) {
    fajta=kap;
}

void Bor::addFajta() {
    char **temp = new char *[fajta_db + 1];
    for (int i = 0; i < fajta_db; i++) {
        temp[i] = fajta[i];
    }
    std::cout << "Adja meg a fajtat: " << std::endl;
    temp[fajta_db] = hoszusor_olvas();
    delete[] fajta;
    fajta = temp;
    fajta_db++;
}


void Bor::fajtakiir() const
{
    for (int i = 0; i < fajta_db; i++) {
        std::cout << fajta[i] << "\n";
    }
}

void Bor::removeFajta() {
    this->fajtakiir();
    std::cout << "Melyik fajtat szeretne torolni?" << std::endl;
    char *fajta = hoszusor_olvas();
    for (int i = 0; i < this->fajta_db; i++) {
        if (strcmp(this->fajta[i], fajta) == 0) {
            char **temp = new char *[this->fajta_db];
            for (int j = 0; j < i; j++) {
                temp[j] = this->fajta[j];
            }
            for (int j = i; j < this->fajta_db; j++) {
                temp[j] = this->fajta[j + 1];
            }
            delete[] this->fajta;
            this->fajta = temp;
            std::cout << "Sikeres torls!" << std::endl;
            return;
        }
    }
    std::cout << "Nincs ilyen fajta!" << std::endl;
}


char * Bor::getFajtaindex(size_t index) const {
    if (index >= fajta_db) {
        throw "Tull indexeles";
    }
    return fajta[index];
}

size_t Bor::getFajta_db() const {
    return fajta_db;
}

void Bor::kiir() const {
    SzeszesItalok::kiir();
    std::cout << " Evjarat: " << evjarat;
    std::cout << " Szin: " << getSzinNev(szin);
    if (fajta_db > 1) {
        std::cout << " Fajtak:";
    } else {
        std::cout << " Fajta:";
    }
    for (int i = 0; i < fajta_db; i++) {
        std::cout <<" "<< fajta[i];
    }
}

void Bor::Set() {
    size_t valasz;
    do {
        this->kiir();
        std::cout<< "Mit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-tipus,4-alkohol, 5-evjart, 6-szin, 7-fajta hozzadas, 8-fajta torles 9-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        while(!(std::cin >> valasz)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
        }
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setTipus();
            break;
            case 4:
                this->setAlkoholTartalom();
            break;
            case 5:
                this->setEvjarat();
            break;
            case 6:
                this->setSzin();
                break;
            case 7:
                this->addFajta();
                break;
            case 8:
                this->removeFajta();
                break;
            case 9: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=9);
}

//whiskey

Wiskey::Wiskey(ital_tipus ital_tipus) : SzeszesItalok(ital_tipus) {
    std::cout << "Adja meg a wiskey tipust: " << std::endl;
    this->tipus = hoszusor_olvas();
    std::cout << "Adja meg az erleses evet: " << std::endl;
    while(!(std::cin >> erleses)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szam erteket!" << std::endl;
    }
}

Wiskey::Wiskey():SzeszesItalok() {
    tipus=nullptr;
}

Wiskey::~Wiskey() {
    delete[] tipus;
}

char * Wiskey::getTipus_wiskey() const {
    return tipus;
}

unsigned int Wiskey::getErleses() const {
    return erleses;
}

void Wiskey::setTipus_wiskey() {
    delete[] this->tipus;
    std::cout << "Adja meg a wiskey tipust: " << std::endl;
    this->tipus = hoszusor_olvas();
}

void Wiskey::setTipus_wiskey(char * kap) {
    delete [] this->tipus;
    tipus=kap;
}

void Wiskey::setErleses() {
    std::cout << "Adja meg az erleses evet: " << std::endl;
    while(!(std::cin >> erleses)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szam erteket!" << std::endl;
    }
}

void Wiskey::setErleses(unsigned int kap) {
    erleses=kap;
}

void Wiskey::kiir() const {
    SzeszesItalok::kiir();
    std::cout << " Tipus: " << tipus;
    std::cout << " Erleses: " << erleses;
}

void Wiskey::Set() {
        size_t valasz;
        do {
            this->kiir();
            std::cout<< "Mit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-tipus,4-alkohol, 5-wiskey tipud, 6-erleles, 7-viszalepes" << std::endl;
            std::cout<<"\nAdja meg az utasitas szamat: ";
            while(!(std::cin >> valasz)){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
            }
            switch (valasz) {
                case 1:
                    this->setNev();
                break;
                case 2:
                    this->setGyarto();
                break;
                case 3:
                    this->setTipus();
                break;
                case 4:
                    this->setAlkoholTartalom();
                break;
                case 5:
                    this->setTipus_wiskey();
                case 6:
                    this->setErleses();
                    break;
                case 7: return;
                default: std::cout<<"Hibas bemenet!"<<std::endl;
            }
        }while (valasz!=7);
    }

//gin

Gin::Gin(ital_tipus ital_tipus) : SzeszesItalok(ital_tipus) {
    int szin = 0;
    iz = nullptr;
    while (szin != 1 && szin != 2 && szin != 3) {
        std::cout << "válasza ki a gin szinet [1]szintelen, [2]pink, [3]egyeb" << std::endl;
        std::cin >> szin;
        switch (szin) {
            case 1:
                this->szin = szintelen;
            break;
            case 2:
                this->szin = pink;
            break;
            case 3:
                this->szin = egyeb;
            break;
            default:
                std::cout << "nem megfelelo szamot adott meg" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    int iz = 0;
    std::cout << "A ginek van jelgzetes íze pl(levendulas)  1(igen), 0(nem)" << std::endl;
    while(!(std::cin >> iz)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szam erteket!" << std::endl;
    }
    if (iz == 1) {
        std::cout << "Adja meg a ginek jellegzetes izet: " << std::endl;
        this->iz = hoszusor_olvas();
    }
}

Gin::Gin() :SzeszesItalok(){
    iz=nullptr;
}

gin_szin Gin::getSzin() const {
    return szin;
}

const char* Gin::getSzinNev(gin_szin szin) const {
    switch (szin) {
        case szintelen: return "szintelen";
        case pink: return "pink";
        case egyeb: return "egyeb";
        default: return "ismeretlen";
    }
}

void Gin::setSzin() {
    int szin = 0;
    while (szin != 1 && szin != 2 && szin != 3) {
        std::cout << "válasza ki a gin szinet [1]szintelen, [2]pink, [3]egyeb" << std::endl;
        std::cin >> szin;
        switch (szin) {
            case 1:
                this->szin = szintelen;
            break;
            case 2:
                this->szin = pink;
            break;
            case 3:
                this->szin = egyeb;
            break;
            default:
                std::cout << "nem megfelelo szamot adott meg" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

void Gin::setSzin(gin_szin kap) {
    szin=kap;
}

const char *Gin::getIz() const {
    return iz;
}

void Gin::setIz() {
    delete[] this->iz;
    int iz = 0;
    std::cout << "A ginek van jelgzetes íze pl(levendulas)  1(igen), 0(nem)" << std::endl;
    while(!(std::cin >> iz)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szam erteket!" << std::endl;
    }
    if (iz == 1) {
        std::cout << "Adja meg a ginek jellegzetes izet: " << std::endl;
        this->iz = hoszusor_olvas();
    } else {
        this->iz = nullptr;
    }
}

void Gin::setIz(char* kap) {
    delete [] this->iz;
    iz=kap;
}

void Gin::kiir()  const{
    SzeszesItalok::kiir();
    std::cout << " Szin: " << getSzinNev(szin);
    if (iz != nullptr) {
        std::cout << " Iz: " << iz;
    }
}

void Gin::Set() {
    size_t valasz;
    do {
        this->kiir();
        std::cout<< "Mit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-tipus,4-alkohol, 5-Gin iz, 6-Szin, 7-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        while(!(std::cin >> valasz)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
        }
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setTipus();
            break;
            case 4:
                this->setAlkoholTartalom();
            break;
            case 5:
                this->setIz();
            case 6:
                this->setSzin();
            break;
            case 7: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=7);
}


//Rum

Rum::Rum(ital_tipus ital_tipus) : SzeszesItalok(ital_tipus) {
    int szin = 0;
    while (szin != 1 && szin != 2 && szin != 3 && szin != 4) {
        std::cout << "válasza ki a rum tipist [1]fuszeres_rum, [2]fuszeres_rum, [3]arany_rum, [4]feher_rum" <<
                std::endl;
        std::cin >> szin;
        switch (szin) {
            case 1:
                this->fajta = fuszeres_rum;
            break;
            case 2:
                this->fajta = fuszeres_rum;
            break;
            case 3:
                this->fajta = arany_rum;
            break;
            case 4:
                this->fajta = feher_rum;
            break;

            default:
                std::cout << "nem megfelelo szamot adott meg" << std::endl;
                std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

Rum::Rum():SzeszesItalok() {
}

rum_fajta Rum::getFajta() const {
    return fajta;
}

void Rum::setFajta() {
    int szin = 0;
    while (szin != 1 && szin != 2 && szin != 3 && szin != 4) {
        std::cout << "válasza kia rum tipist [1]fuszeres_rum, [2]fekete_rum, [3]arany_rum, [4]feher_rum" <<
                std::endl;
        std::cin >> szin;
        switch (szin) {
            case 1:
                this->fajta = fuszeres_rum;
            break;
            case 2:
                this->fajta = fekete_rum;
            break;
            case 3:
                this->fajta = arany_rum;
            break;
            case 4:
                this->fajta = feher_rum;
            break;

            default:
                std::cout << "nem megfelelo szamot adott meg" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

void Rum::setFajta(rum_fajta kap) {
    fajta=kap;
}

const char* Rum::getFajtaNev(rum_fajta fajta) const{
    switch (fajta) {
        case fuszeres_rum: return "fuszeres_rum";
        case fekete_rum: return "fekete_rum";
        case arany_rum: return "arany_rum";
        case feher_rum: return "feher_rum";
        default: return "ismeretlen";
    }
}

void Rum::kiir() const {
    SzeszesItalok::kiir();
    std::cout << " Fajta: " << getFajtaNev(fajta) << std::endl;
}

void Rum::Set() {
    size_t valasz;
    do {
        this->kiir();
        std::cout<< "Mit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-tipus,4-alkohol, 5-Rum fajtaja, 6-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        while(!(std::cin >> valasz)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
        }
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setTipus();
            break;
            case 4:
                this->setAlkoholTartalom();
            break;
            case 5:
                this->setFajta();
            break;
            case 6: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=6);
}


//tequila

Tequila::Tequila(ital_tipus ital_tipus) : SzeszesItalok(ital_tipus) {
    int szin = 0;
    while (szin != 1 && szin != 2 && szin != 3) {
        std::cout << "válasza ki a tequila tipist [1]silver, [2]gold, [3]aged" << std::endl;
        std::cin >> szin;
        switch (szin) {
            case 1:
                this->fajta = silver;
            break;
            case 2:
                this->fajta = gold;
            break;
            case 3:
                this->fajta = aged;
            break;
            default:
                std::cout << "nem megfelelo szamot adott meg" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

Tequila::Tequila():SzeszesItalok() {
}

tequli_fajta Tequila::getFajta() const {
    return fajta;
}

void Tequila::setFajta() {
    int szin = 0;
    while (szin != 1 && szin != 2 && szin != 3) {
        std::cout << "válasza kia tequila tipist [1]silver, [2]gold, [3]aged" << std::endl;
        std::cin >> szin;
        switch (szin) {
            case 1:
                this->fajta = silver;
            break;
            case 2:
                this->fajta = gold;
            break;
            case 3:
                this->fajta = aged;
            break;
            default:
                std::cout << "nem megfelelo szamot adott meg" << std::endl;
                 std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

void Tequila::setFajta(tequli_fajta kap) {
    fajta=kap;
}

const char* Tequila::getFajtaNev(tequli_fajta fajta) const {
    switch (fajta) {
        case silver: return "silver";
        case gold: return "gold";
        case aged: return "aged";
        default: return "ismeretlen";
    }
}

void Tequila::kiir() const {
    SzeszesItalok::kiir();
    std::cout << " Fajta: " << getFajtaNev(fajta);
}

void Tequila::Set() {
    size_t valasz;
    do {
        this->kiir();
        std::cout<< "Mit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-tipus,4-alkohol, 5-Tequila fajtaja, 6-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        while(!(std::cin >> valasz)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
        }
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setTipus();
            break;
            case 4:
                this->setAlkoholTartalom();
            break;
            case 5:
                this->setFajta();
            break;
            case 6: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=6);
}

//sor
Sor::Sor(ital_tipus tipuss) : SzeszesItalok(tipuss) {
    std::cout << "Adja meg a sor tipusat: " << std::endl;
    this->tipus_sor = hoszusor_olvas();
}

Sor::Sor():SzeszesItalok() {
    tipus_sor=nullptr;
}


char * Sor::getTipus_sor() const{
    return tipus_sor;
}

void Sor::setTipus_sor() {
    delete[] this->tipus_sor;
    std::cout << "Adja meg a sor tipusat: " << std::endl;
    this->tipus_sor = hoszusor_olvas();
}

void Sor::setTipus_sor(char *kap) {
    delete[] this->tipus_sor;
    tipus_sor=kap;
}

void Sor::kiir() const {
    SzeszesItalok::kiir();
    std::cout << " Tipus: " << tipus_sor;
}

Sor::~Sor() {
    delete[] tipus_sor;
}

void Sor::Set() {
    size_t valasz;
    do {
        this->kiir();
        std::cout<< "Mit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-tipus,4-alkohol, 5-Sor tipus, 6-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        while(!(std::cin >> valasz)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
        }
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setTipus();
            break;
            case 4:
                this->setAlkoholTartalom();
            break;
            case 5:
                this->setTipus_sor();
            break;
            case 6: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=7);
}

//gyumolcslev

Gyumolcsle::Gyumolcsle(ital_tipus ital_tipus) : Ital(ital_tipus) {
    std::cout << "Adja meg a gyumolcsszazalekot: " << std::endl;
    while(!(std::cin >> gyumolcsszazalek)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szam erteket!" << std::endl;
    }
}

Gyumolcsle::Gyumolcsle():Ital() {
}


unsigned int Gyumolcsle::getGyumolcsszazalek() const {
    return gyumolcsszazalek;
}

void Gyumolcsle::setGyumolcsszazalek() {
    std::cout << "Adja meg a gyumolcsszazalekot: " << std::endl;
    while(!(std::cin >> gyumolcsszazalek)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szam erteket!" << std::endl;
    }
}

void Gyumolcsle::setGyumolcsszazalek(unsigned int kap) {
    gyumolcsszazalek=kap;
}

void Gyumolcsle::kiir() const {
    Ital::kiir();
    std::cout << "Gyumolcsszazalek: " << gyumolcsszazalek;
}

void Gyumolcsle::Set() {
    size_t valasz;
    do {
        this->kiir();
        std::cout<< "Mit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-tipus,4-gyumolcsszazalek, 5-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        while(!(std::cin >> valasz)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
        }
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setTipus();
            break;
            case 4:
                this->setGyumolcsszazalek();
            break;
            case 5: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=5);
}

//>>italok
/*
std::ostream& operator<<(std::ostream& os, const Ital& ital) {
    os <<"Nev: "<< ital.getNev()<<" Gyarto "<< ital.getGyarto() << " tipus:"<< ital.getTipusNev(ital.getTipus());
    return os;
}
std::ostream& operator<<(std::ostream& os, const SzeszesItalok& ital) {
    os << (Ital&)ital<<" alk: " << ital.getAlkoholTartalom()<<" %";
    return os;
}
std::ostream& operator<<(std::ostream& os, const Bor& ital) {
    os<< (SzeszesItalok&)ital<< "\nEvjarat: " << ital.getEvjarat() << "Szin: " << ital.getSzin() << " Fajta db: " << ital.getFajta_db();
    for (int i = 0; i < ital.getFajta_db(); i++) {
        os <<" Fajta:"<< ital.getFajtaindex(i);
    }
        return os;
    }
std::ostream& operator<<(std::ostream& os, const Wiskey& ital) {
    os<<(SzeszesItalok&)ital<<"\nTipus:" << ital.getTipus_wiskey() << " Erleles:" << ital.getErleses();
    return os;
}
std::ostream& operator<<(std::ostream& os, const Gin& ital) {
    os<<(SzeszesItalok&)ital << "\nSzin:" << ital.getSzinNev(ital.getSzin());
    if (ital.getIz() != nullptr) {
        os <<" Ize "<< ital.getIz();
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Rum& ital) {
    os<<(SzeszesItalok&)ital << "\nFajta: " << ital.getFajtaNev(ital.getFajta());
    return os;
}
std::ostream& operator<<(std::ostream& os, const Tequila& ital) {
    os<<(SzeszesItalok&)ital<< "\nFajta: " << ital.getFajtaNev(ital.getFajta());
    return os;
}
std::ostream& operator<<(std::ostream& os, const Sor& ital) {
    os<<(SzeszesItalok&)ital<< "\nTipus: " << ital.getTipus_sor();
    return os;
}
std::ostream& operator<<(std::ostream& os, const Gyumolcsle& ital) {
    os<<(Ital&)ital<< "\nGyümölcstartam: " << ital.getGyumolcsszazalek() << "%";
    return os;
}
*/

std::ostream& operator<<(std::ostream& os, const Ital& ital) {
    ital.kiir();
    return os;
}

