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

void Ital::setGyarto() {
    delete[] this->gyarto;
    std::cout << "Adja meg az ital gyarojat: " << std::endl;
    this->gyarto = hoszusor_olvas();
}

void Ital:: kiir() {
    std::cout << "Nev: " << nev << std::endl;
    std::cout << "Gyarto: " << gyarto << std::endl;
    std::cout << "fajtaja: " << getTipusNev(tipus) << std::endl;
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

void SzeszesItalok::kiir() {
    Ital::kiir();
    std::cout << "Alkohol tartalom: " << alkoholTartalom << std::endl;
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

void Bor::kiir() {
    SzeszesItalok::kiir();
    std::cout << "Evjarat: " << evjarat << std::endl;
    std::cout << "Szin: " << getSzinNev(szin) << std::endl;
    std::cout << "Fajtak: " << std::endl;
    for (int i = 0; i < fajta_db; i++) {
        std::cout << fajta[i] << std::endl;
    }
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

Wiskey::~Wiskey() {
    delete[] tipus;
}

char * Wiskey::getTipus_wiskey() const {
    return tipus;
}

unsigned int Wiskey::getErleses() const {
    return erleses;
}

void Wiskey::setTipus() {
    delete[] this->tipus;
    std::cout << "Adja meg a wiskey tipust: " << std::endl;
    this->tipus = hoszusor_olvas();
}

void Wiskey::setErleses() {
    std::cout << "Adja meg az erleses evet: " << std::endl;
    while(!(std::cin >> erleses)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szam erteket!" << std::endl;
    }
}

void Wiskey::kiir() {
    SzeszesItalok::kiir();
    std::cout << "Tipus: " << tipus << std::endl;
    std::cout << "Erleses: " << erleses << std::endl;
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

void Gin::kiir() {
    SzeszesItalok::kiir();
    std::cout << "Szin: " << getSzinNev(szin) << std::endl;
    if (iz != nullptr) {
        std::cout << "Iz: " << iz << std::endl;
    }
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

const char* Rum::getFajtaNev(rum_fajta fajta) const{
    switch (fajta) {
        case fuszeres_rum: return "fuszeres_rum";
        case fekete_rum: return "fekete_rum";
        case arany_rum: return "arany_rum";
        case feher_rum: return "feher_rum";
        default: return "ismeretlen";
    }
}

void Rum::kiir() {
    SzeszesItalok::kiir();
    std::cout << "Fajta: " << getFajtaNev(fajta) << std::endl;
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

const char* Tequila::getFajtaNev(tequli_fajta fajta) const {
    switch (fajta) {
        case silver: return "silver";
        case gold: return "gold";
        case aged: return "aged";
        default: return "ismeretlen";
    }
}

void Tequila::kiir() {
    SzeszesItalok::kiir();
    std::cout << "Fajta: " << getFajtaNev(fajta) << std::endl;
}

//sor
Sor::Sor(ital_tipus tipuss) : SzeszesItalok(tipuss) {
    std::cout << "Adja meg a sor tipusat: " << std::endl;
    this->tipus_sor = hoszusor_olvas();
}

char * Sor::getTipus_sor() const{
    return tipus_sor;
}

void Sor::setTipus(char *tipus) {
    delete[] this->tipus_sor;
    std::cout << "Adja meg a sor tipusat: " << std::endl;
    this->tipus_sor = hoszusor_olvas();
}

void Sor::kiir() {
    SzeszesItalok::kiir();
    std::cout << "Tipus: " << tipus_sor << std::endl;
}

Sor::~Sor() {
    delete[] tipus_sor;
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

void Gyumolcsle::kiir() {
    Ital::kiir();
    std::cout << "Gyumolcsszazalek: " << gyumolcsszazalek << std::endl;
}

//>>italok
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


