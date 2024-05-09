//
// Created by Zoli on 2024. 04. 12..
//

#include "Ital.h"
#include <iostream>
#include <cstring>
#include "bevitel_kezel.h"
#include <limits>
#include <ctime>
#include "memtrace.h"

ital_tipus tipus_valszto() {
    int tipus;
    do{
        std::cout << "Adja meg az ital tipusat (1 - Bor, 2 - Wiskey, 3 - Gin, 4 - Rum, 5 - Tequila, 6 - Sor, 7 - Gyumolcsle, 8 - Alkohols, 9 - Alkohol mentes ): ";
        tipus=int_beolvas();
        switch(tipus) {
            case 1:
                return  bor;
            case 2:
                return  whiskey;
            case 3:
                return  gin;
            case 4:
                return  rum;
            case 5:
                return  tequila;
            case 6:
                return  sor;
            case 7:
                return  gyumolcsle;
            case 8:
                return  alkohols;
            case 9:
                return  alkohol_mentes;
            default:
                std::cout << "Hibas tipus valaztas!" << std::endl;
                break;
        }
    } while(tipus<1 || tipus>9);
    return alkohol_mentes;

}



const char* get_tipus_nev_str(ital_tipus tipus){
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


Ital::Ital(ital_tipus tipus):nev(nullptr),gyarto(nullptr),tipus(tipus){
    setNev();
    setGyarto();
}

Ital::Ital() :nev(nullptr),gyarto(nullptr){}

Ital::Ital(char *nev, ital_tipus tipus):nev(nullptr), gyarto(nullptr), tipus(tipus){
    this->nev=new char[strlen(nev)+1];
    strcpy(this->nev,nev);
    setGyarto();
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

const char*  Ital::getTipusNev(ital_tipus tipus_kap) const {
    return  get_tipus_nev_str(tipus_kap);
}

const char*  Ital::getTipusNev() const {
    return get_tipus_nev_str(tipus);
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
    std::cout << " Fajtaja: " << getTipusNev();
}

void Ital::setTipus() {
    tipus=tipus_valszto();
}

void Ital::setTipus(ital_tipus kap) {
    tipus=kap;
}



void Ital::Set() {
    int valasz;
    do {
        this->kiir();
        std::cout<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        valasz=int_beolvas();
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=3);
}

//szeszes italok

SzeszesItalok::SzeszesItalok(ital_tipus tipus) : Ital(tipus) {
    setAlkoholTartalom();
}

SzeszesItalok::SzeszesItalok() : Ital(){
}

SzeszesItalok::SzeszesItalok(char *nev, ital_tipus tipus): Ital(nev,tipus) {
    setAlkoholTartalom();
}

float SzeszesItalok::getAlkoholTartalom() const {
    return alkoholTartalom;
}

void SzeszesItalok::setAlkoholTartalom() {
    std::cout << "Adja meg az alkohol tartalmat: " << std::endl;
    alkoholTartalom=float_beolvas();
}

void SzeszesItalok::setAlkoholTartalom(float kap) {
    alkoholTartalom=kap;
}

void SzeszesItalok::kiir() const {
    Ital::kiir();
    std::cout << " Alkohol tartalom: " << alkoholTartalom;
}

void SzeszesItalok::Set() {
    int valasz;
    do {
        this->kiir();
        std::cout<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-alkohol, 4-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        valasz=int_beolvas();
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setAlkoholTartalom();
            break;
            case 4: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=4);
}

//bor

bool evjarat_teszt(int evjarat) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    if (evjarat > 1900 + ltm->tm_year) {
        return false;
    }
    return true;
}


Bor::Bor(ital_tipus tipus) : SzeszesItalok(tipus),fajta(nullptr),fajta_db(0) {
    setEvjarat();
    setSzin();
    std::cout << "Adja meg a fajtak szamat: " << std::endl;
    size_t fajtak=size_beolvas();
    for (size_t i = 0; i < fajtak; i++) {
        addFajta();
    }
}

Bor::Bor():SzeszesItalok(), fajta(nullptr),fajta_db(0) {
}

Bor::Bor(char* nev, ital_tipus tipus):SzeszesItalok(nev,tipus), fajta(nullptr),fajta_db(0) {
    setEvjarat();
    setEvjarat();
    std::cout << "Adja meg a fajtak szamat: " << std::endl;
    size_t fajtak=size_beolvas();
    for (size_t i = 0; i < fajtak; i++) {
        addFajta();
    }

}

Bor::~Bor() {
    for (size_t i = 0; i < fajta_db; i++) {
        delete[] fajta[i];
    }
    delete[] fajta;
}

int Bor::getEvjarat() const {
    return evjarat;
}

szinek_bor Bor::getSzin() const {
    return szin;
}


const char* Bor::getSzinNev() const{
    switch (szin) {
        case voros: return "voros";
        case rose: return "rose";
        case feher: return "feher";
        default: return "ismeretlen";
    }
}

void Bor::setEvjarat() {
    std::cout << "Adja meg az evjaratot: " << std::endl;
    evjarat=int_beolvas();
    while(!evjarat_teszt(evjarat)) {
        std::cout << "Hibas evjarat! Adjon meg egy helyes evjaratot!" << std::endl;
        evjarat=int_beolvas();
    }
}

void Bor::setEvjarat(int kap) {
    if(evjarat_teszt(kap))
        evjarat=kap;
    else
        setEvjarat();
}


void Bor::setSzin() {
    std::cout<< "Adja meg a bor szinet: [1]voros, [2]rose, [3]feher" << std::endl;
    int szin_be = 0;
    while (szin_be != 1 && szin_be != 2 && szin_be != 3) {
        szin_be=int_beolvas();
        switch (szin_be) {
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
    for (size_t i = 0; i < fajta_db; i++) {
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
    for (size_t i = 0; i < fajta_db; i++) {
        std::cout << fajta[i] << "\n";
    }
}

void Bor::removeFajta() {
    this->fajtakiir();
    std::cout << "Melyik fajtat szeretne torolni?" << std::endl;
    char *fajta_beolvas = hoszusor_olvas();
    for (size_t i = 0; i < fajta_db; i++) {
        if (strcmp(this->fajta[i], fajta_beolvas) == 0) {
            char **temp = new char *[fajta_db-1];
            for (size_t j = 0; j < i; j++) {
                temp[j] = this->fajta[j];
            }
            for (size_t j = i; j < this->fajta_db; j++) {
                temp[j] = this->fajta[j + 1];
            }
            delete[] this->fajta[i];
            delete[] fajta_beolvas;
            delete[] this->fajta;
            this->fajta = temp;
            --fajta_db;
            std::cout << "Sikeres torls!" << std::endl;
            if(fajta_db==0) {
                delete [] fajta_beolvas;
                fajta_beolvas=nullptr;
            }
            return;
        }
    }
    std::cout << "Nincs ilyen fajta!" << std::endl;
    delete[] fajta_beolvas;
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
    std::cout << " Szin: " << getSzinNev();
    if (fajta_db > 1) {
        std::cout << " Fajtak:";
    } else {
        std::cout << " Fajta:";
    }
    for (size_t i = 0; i < fajta_db; i++) {
        std::cout <<" "<< fajta[i];
    }
}

void Bor::Set() {
    size_t valasz;
    do {
        this->kiir();
        std::cout<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-alkohol, 4-evjart, 5-szin, 6-fajta hozzadas, 7-fajta torles 8-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        valasz=size_beolvas();
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setAlkoholTartalom();
            break;
            case 4:
                this->setEvjarat();
            break;
            case 5:
                this->setSzin();
                break;
            case 6:
                this->addFajta();
                break;
            case 7:
                this->removeFajta();
                break;
            case 8: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
            break;
        }
    }while (valasz!=8);
}

//whiskey

Wiskey::Wiskey(ital_tipus ital_tipus) : SzeszesItalok(ital_tipus), jeleg(nullptr) {
    setJeleg_wiskey();
    setErleses();
}

Wiskey::Wiskey():SzeszesItalok(),jeleg(nullptr) {}

Wiskey::Wiskey(char *nev,ital_tipus tipus):SzeszesItalok(nev,tipus),jeleg(nullptr) {
    setJeleg_wiskey();
    setErleses();

}

Wiskey::~Wiskey() {
    delete[] jeleg;
}

char * Wiskey::getJeleg_wiskey() const {
    return jeleg;
}

unsigned int Wiskey::getErleses() const {
    return erleses;
}

void Wiskey::setJeleg_wiskey() {
    delete[] this->jeleg;
    std::cout << "Adja meg a wiskey tipust: " << std::endl;
    this->jeleg = hoszusor_olvas();
}

void Wiskey::setJeleg_wiskey(char * kap) {
    delete [] this->jeleg;
    jeleg=kap;
}

void Wiskey::setErleses() {
    std::cout << "Adja meg az erleses evet: " << std::endl;
    erleses=unsigned_int_beolvas();
}

void Wiskey::setErleses(unsigned int kap) {
    erleses=kap;
}

void Wiskey::kiir() const {
    SzeszesItalok::kiir();
    std::cout << " Tipus: " << jeleg;
    std::cout << " Erleses: " << erleses;
}

void Wiskey::Set() {
        size_t valasz;
        do {
            this->kiir();
            std::cout<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto,3-alkohol, 4-wiskey tipud, 5-erleles, 6-viszalepes" << std::endl;
            std::cout<<"\nAdja meg az utasitas szamat: ";
            valasz=size_beolvas();
            switch (valasz) {
                case 1:
                    this->setNev();
                    break;
                case 2:
                    this->setGyarto();
                    break;
                case 3:
                    this->setAlkoholTartalom();
                    break;
                case 4:
                    this->setJeleg_wiskey();
                    break;
                case 5:
                    this->setErleses();
                    break;
                case 6: return;
                default: std::cout<<"Hibas bemenet!"<<std::endl;
            }
        }while (valasz!=6);
    }

//gin

Gin::Gin(ital_tipus ital_tipus) : SzeszesItalok(ital_tipus),iz(nullptr) {
    setSzin();
    setIz();
}

Gin::Gin() :SzeszesItalok(), iz(nullptr){
}

Gin::Gin(char *nev, ital_tipus tipus):SzeszesItalok(nev,tipus), iz(nullptr) {
    setIz();
   setSzin();

}


gin_szin Gin::getSzin() const {
    return szin;
}

const char* Gin::getSzinNev() const {
    switch (szin) {
        case szintelen: return "szintelen";
        case pink: return "pink";
        case egyeb: return "egyeb";
        default: return "ismeretlen";
    }
}

void Gin::setSzin() {
    std::cout<< "Adja meg a gin szinet: [1]szintelen, [2]pink, [3]egyeb" << std::endl;
    int szin_olvas = 0;
    while (szin_olvas != 1 && szin_olvas != 2 && szin_olvas != 3) {
        szin_olvas=int_beolvas();
        switch (szin_olvas) {
            case 1:
                this->szin = szintelen;
                return;
            case 2:
                this->szin = pink;
                return;
            case 3:
                this->szin = egyeb;
                return;
            default:
                std::cout << "nem megfelelo szamot adott meg" << std::endl;
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
    int iz_bevit = 0;
    std::cout << "A ginek van jelgzetes íze pl(levendulas)  1(igen), 0(nem)" << std::endl;
    iz_bevit=int_beolvas();
    if (iz_bevit == 1) {
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
    std::cout << " Szin: " << getSzinNev();
    if (iz != nullptr) {
        std::cout << " Iz: " << iz;
    }
}

void Gin::Set() {
    size_t valasz;
    do {
        this->kiir();
        std::cout<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-alkohol, 4-Gin iz, 5-Szin, 6-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        valasz=size_beolvas();
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setAlkoholTartalom();
            break;
            case 4:
                this->setIz();
                break;
            case 5:
                this->setSzin();
            break;
            case 6: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=7);
}

Gin::~Gin() {
    delete[] iz;
}


//Rum

Rum::Rum(ital_tipus tipus) : SzeszesItalok(tipus) {
    setFajta();
}

Rum::Rum():SzeszesItalok() {
}

Rum::Rum(char *nev, ital_tipus tipus):SzeszesItalok(nev,tipus) {
    setFajta();
}


rum_fajta Rum::getFajta() const {
    return fajta;
}

void Rum::setFajta() {
    std::cout<< "Adja meg a rum fajtajt: [1]fuszeres_rum, [2]fekete_rum, [3]arany_rum, [4]feher_rum" << std::endl;
    int szin_beolvas = 0;
    while (szin_beolvas != 1 && szin_beolvas != 2 && szin_beolvas != 3 && szin_beolvas != 4) {
        szin_beolvas=int_beolvas();
        switch (szin_beolvas) {
            case 1:
                this->fajta = fuszeres_rum;
                return;
            case 2:
                this->fajta = fekete_rum;
                return;
            case 3:
                this->fajta = arany_rum;
                return;
            case 4:
                this->fajta = feher_rum;
                return;
            default:
                std::cout << "nem megfelelo szamot adott meg" << std::endl;
                break;
        }
    }
}

void Rum::setFajta(rum_fajta kap) {
    fajta=kap;
}

const char* Rum::getFajtaNev() const{
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
    std::cout << " Fajta: " << getFajtaNev();
}

void Rum::Set() {
    size_t valasz;
    do {
        this->kiir();
        std::cout<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-alkohol, 4-Rum fajtaja, 5-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        valasz=size_beolvas();
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setAlkoholTartalom();
            break;
            case 4:
                this->setFajta();
            break;
            case 5: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=5);
}


//tequila

Tequila::Tequila(ital_tipus ital_tipus) : SzeszesItalok(ital_tipus) {
    setFajta();
}

Tequila::Tequila():SzeszesItalok() {}

Tequila::Tequila(char *nev, ital_tipus tipus):SzeszesItalok(nev,tipus) {
    setFajta();
}


tequli_fajta Tequila::getFajta() const {
    return fajta;
}

void Tequila::setFajta() {
    int olvas_fajta;
    do{
        std::cout << "valasza ki a tequila tipisat [1]silver, [2]gold, [3]aged" << std::endl;
        olvas_fajta=int_beolvas();
        switch (olvas_fajta) {
            case 1:
                this->fajta = silver;
                return;
            case 2:
                this->fajta = gold;
                return;
            case 3:
                this->fajta = aged;
                return;
            default:
                std::cout << "nem megfelelo szamot adott meg" << std::endl;
                break;
        }
    }while (olvas_fajta != 1 && olvas_fajta != 2 && olvas_fajta != 3);
}

void Tequila::setFajta(tequli_fajta kap) {
    fajta=kap;
}

const char* Tequila::getFajtaNev() const {
    switch (fajta) {
        case silver: return "silver";
        case gold: return "gold";
        case aged: return "aged";
        default: return "ismeretlen";
    }
}

void Tequila::kiir() const {
    SzeszesItalok::kiir();
    std::cout << " Fajta: " << getFajtaNev();
}

void Tequila::Set() {
    size_t valasz;
    do {
        this->kiir();
        std::cout<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-alkohol, 4-Tequila fajtaja, 5-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        valasz=size_beolvas();
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setAlkoholTartalom();
            break;
            case 4:
                this->setFajta();
            break;
            case 5: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=5);
}

//sor
Sor::Sor(ital_tipus tipuss) : SzeszesItalok(tipuss), tipus_sor(nullptr) {
    setTipus_sor();
}

Sor::Sor():SzeszesItalok(),tipus_sor(nullptr) {}

Sor::Sor(char *nev, ital_tipus tipus): SzeszesItalok(nev,tipus),tipus_sor(nullptr) {
    setTipus_sor();
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
        std::cout<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-alkohol, 5-Sor jeleg, 6-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        valasz=size_beolvas();
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setAlkoholTartalom();
            break;
            case 4:
                this->setTipus_sor();
            break;
            case 5: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=5);
}

//gyumolcslev

Gyumolcsle::Gyumolcsle(ital_tipus ital_tipus) : Ital(ital_tipus) {
   setGyumolcsszazalek();
}

Gyumolcsle::Gyumolcsle():Ital() {}

Gyumolcsle::Gyumolcsle(char *nev, ital_tipus tipus):Ital(nev,tipus) {
    setGyumolcsszazalek();
}



unsigned int Gyumolcsle::getGyumolcsszazalek() const {
    return gyumolcsszazalek;
}

void Gyumolcsle::setGyumolcsszazalek() {
    std::cout << "Adja meg a gyumolcsszazalekot: " << std::endl;
    gyumolcsszazalek=unsigned_int_beolvas();
    while (gyumolcsszazalek>100) {
        std::cout << "Hibas szazalek! Adjon meg egy helyes szazalekot!" << std::endl;
        gyumolcsszazalek=unsigned_int_beolvas();
    }
}

void Gyumolcsle::setGyumolcsszazalek(unsigned int kap) {
    gyumolcsszazalek=kap;
    while (gyumolcsszazalek>100) {
        std::cout << "Hibas szazalek! Adjon meg egy helyes szazalekot!" << std::endl;
        gyumolcsszazalek=unsigned_int_beolvas();
    }
}

void Gyumolcsle::kiir() const {
    Ital::kiir();
    std::cout << "Gyumolcsszazalek: " << gyumolcsszazalek;
}

void Gyumolcsle::Set() {
    size_t valasz;
    do {
        this->kiir();
        std::cout<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-gyumolcsszazalek, 5-viszalepes" << std::endl;
        std::cout<<"\nAdja meg az utasitas szamat: ";
        valasz=size_beolvas();
        switch (valasz) {
            case 1:
                this->setNev();
            break;
            case 2:
                this->setGyarto();
            break;
            case 3:
                this->setGyumolcsszazalek();
            break;
            case 4: return;
            default: std::cout<<"Hibas bemenet!"<<std::endl;
        }
    }while (valasz!=4);
}


//os adatok kiíráas
std::ostream& operator<<(std::ostream& os, const Ital& ital) {
    ital.kiir();
    return os;
}

