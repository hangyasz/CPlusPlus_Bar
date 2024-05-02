//
// Created by Zoli on 2024. 04. 18..
//

#include "faljkezel.h"
#include <iostream>
#include <fstream>
#include "Ital.h"
#include <limits>


void Ital::kiirF(std::ofstream& os) const {
    os<<getTipusszam(tipus)<<"<"<<nev<<"><"<<gyarto<<">";
}

void SzeszesItalok::kiirF(std::ofstream& os) const {
    Ital::kiirF(os);
    os<<"<"<<alkoholTartalom<<">";
}
void Bor::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os);
    os<<"<"<<evjarat<<"><"<<getBorSzin(szin)<<"><"<<fajta_db<<"><";
    if(fajta_db>=1)
        os<<fajta[0];
    for(size_t i=1;i<fajta_db;i++){
        os<<"><"<<fajta[i];
    }
    os<<">";
}
void Wiskey::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os);
    os<<"<"<<tipus<<"><"<<erleses<<">";
}

void Gin::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os);
    os<<"<"<<getGinSzin(szin)<<"><";
    if(iz!=nullptr)
        os<<iz;
    os<<">";
}
void Rum::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os);
    os<<"<"<<getRumtipus(fajta)<<">";
}

void Tequila::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os);
    os<<"<"<<getTequilaTipus(fajta)<<">";
}

void Sor::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os);
    os<<"<"<<tipus_sor<<">";
}

void Gyumolcsle::kiirF(std::ofstream& os) const {
    Ital::kiirF(os);
    os<<"<"<<gyumolcsszazalek<<">";
}


std::ofstream& operator<<(std::ofstream& os,const Ital &ital) {
    ital.kiirF(os);
    return os;
}
/*
std::ofstream& operator<<(std::ofstream& os,const SzeszesItalok &ital) {
    os<<(Ital&)ital<<"<"<<ital.getAlkoholTartalom()<<">";
    return os;
}
std::ofstream& operator<<(std::ofstream& os,const Bor &ital) {
    os<<(SzeszesItalok&)ital<<"<"<<getBorSzin(ital.getSzin())<<"<"<<ital.getFajta_db()<<">{";
    if(ital.getFajta_db()>=1)
        os<<ital.getFajtaindex(0);
    for(size_t i=1;i<ital.getFajta_db();i++){
        os<<","<<ital.getFajtaindex(i);
    }
    os<<"}";
   return os;}
std::ofstream& operator<<(std::ofstream& os,const Wiskey &ital) {
    os<<(SzeszesItalok&)ital<<"<"<<ital.getTipus_wiskey()<<"<"<<ital.getErleses()<<">";
    return os;
}

std::ofstream& operator<<(std::ofstream& os,const Gin &ital) {
    os<<(SzeszesItalok&)ital<<"<"<<getGinSzin(ital.getSzin())<<"<"<<ital.getIz()<<">";
    return os;
}

std::ofstream& operator<<(std::ofstream& os,const Rum &ital) {
    os<<(SzeszesItalok&)ital<<"<"<<getRumtipus(ital.getFajta())<<">";
    return os;
}
std::ofstream& operator<<(std::ofstream& os,const Tequila &ital) {
    os<<(SzeszesItalok&)ital<<"<"<<getTequilaTipus(ital.getFajta())<<">";
    return os;
}
std::ofstream& operator<<(std::ofstream& os,const Sor &ital) {
    os<<(SzeszesItalok&)ital<<"<"<<ital.getTipus_sor()<<">";
    return os;
}

std::ofstream& operator<<(std::ofstream& os,const Gyumolcsle &ital) {
    os<<(Ital&)ital<<"<"<<ital.getGyumolcsszazalek()<<">";
    return os;
}
*/
int getTipusszam(ital_tipus tipus) {
    switch (tipus) {
        case bor: return 1;
        case whiskey: return 2;
        case gin: return 3;
        case rum: return 4;
        case tequila: return 5;
        case sor: return 6;
        case gyumolcsle: return 7;
        case alkohols: return 8;
        case alkohol_mentes: return 9;
        default:
            throw "Hibás típus!";
    }
}

int getBorSzin(szinek_bor szin) {
    switch (szin) {
        case voros: return 1;
        case rose: return 2;
        case feher: return 3;
        default: throw "Hibás szín!";
    }
}

szinek_bor getSzinBor(int szin) {
    switch (szin) {
        case 1: return voros;
        case 2: return rose;
        case 3: return feher;
        default: throw "Hibás szín!";
    }
}

int getGinSzin(gin_szin szin) {
    switch (szin) {
        case szintelen: return 1;
        case pink: return 2;
        case egyeb: return 3;
        default: throw "Hibás szín!";
    }
}

gin_szin getSzinGin(int szin) {
    switch (szin) {
        case 1: return szintelen;
        case 2: return pink;
        case 3: return egyeb;
        default: throw "Hibás szín!";
    }
}

int getTequilaTipus(tequli_fajta fajta) {
    switch (fajta) {
        case silver: return 1;
        case gold: return 2;
        case aged: return 3;
        default: throw "Hibás fajta!";
    }
}

tequli_fajta getFajtaTequila(int fajta) {
    switch (fajta) {
        case 1: return silver;
        case 2: return gold;
        case 3: return aged;
        default: throw "Hibás fajta!";
    }
}


int getRumtipus(rum_fajta fajta) {
    switch (fajta) {
        case fuszeres_rum: return 1;
        case fekete_rum: return 2;
        case arany_rum: return 3;
        case feher_rum: return 4;
        default: throw"Hibás fajta!";
    }
}

rum_fajta getFajtaRum(int fajta) {
    switch (fajta) {
        case 1: return fuszeres_rum;
        case 2: return fekete_rum;
        case 3: return arany_rum;
        case 4: return feher_rum;
        default: throw"Hibás fajta!";
    }
}

 void Italok::kiirF() const{
    std::ofstream file;
    file.open("italok.txt");
    if (!file.is_open())
        throw"nem nyilt meg az italok.txt";
    for(size_t i=0;i<db;i++){
        file<<this->getItal(i)<<"\n";
    }
    file.close();
}

char *szoveg_olvas(std::ifstream &file) {
    char *szoveg=nullptr;
    char c;
    size_t db=0;
    while(file.get(c) && c!='>'){
        if(szoveg==nullptr) {
            szoveg = new char[db + 1];
            szoveg[db] = '\0';
        }
        else{
            char *uj=new char[db+1];
            strcpy(uj,szoveg);
            uj[db]=c;
            uj[1+db++]='\0';
            delete[] szoveg;
            szoveg=uj;
        }
    }
    if(strcmp(szoveg,"")==0){
        delete[] szoveg;
        szoveg=nullptr;
    }
    return szoveg;
}

int szam_olvas(std::ifstream &file) {
    char kacsacsor;
    int szam;
    file>>kacsacsor>>szam>>kacsacsor;
    return szam;
}

unsigned int uszam_olvas(std::ifstream &file) {
    char kacsacsor;
    unsigned int szam;
    file>>kacsacsor>>szam>>kacsacsor;
    return szam;
}

size_t size_olvas(std::ifstream &file) {
    char kacsacsor;
    size_t szam;
    file>>kacsacsor>>szam>>kacsacsor;
    return szam;
}

float float_olvas(std::ifstream &file) {
    char kacsacsor;
    float szam;
    file>>kacsacsor>>szam>>kacsacsor;
    return szam;
}

Ital* ital_olvas(std::ifstream &file) {
    Ital *olvas=new Ital();
    olvas->setTipus(alkohol_mentes);
    olvas->setNev(szoveg_olvas(file));
    olvas->setGyarto(szoveg_olvas(file));
    return  olvas;
}

SzeszesItalok * szeszes_olvas(std::ifstream &file) {
    SzeszesItalok *olvas=new SzeszesItalok();
    olvas->setTipus(alkohols);
    olvas->setNev(szoveg_olvas(file));
    olvas->setGyarto(szoveg_olvas(file));
    olvas->setAlkoholTartalom(float_olvas(file));
    return olvas;
}



Bor *bor_olvas(std::ifstream &file) {
    Bor *olvas=new Bor();
    olvas->setTipus(bor);
    olvas->setNev(szoveg_olvas(file));
    olvas->setGyarto(szoveg_olvas(file));
    olvas->setAlkoholTartalom(float_olvas(file));
    olvas->setEvjarat(uszam_olvas(file));
    if(!evjarat_teszt(olvas->getEvjarat())) {
        std::cout<<"Hibas evjarat!"<<std::endl;
        std::cout << "Adja meg az evjaratot: " << std::endl;
        unsigned int bevitel;
        while(!(std::cin >> bevitel) or !evjarat_teszt(bevitel)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Hibas bemenet. Kerlek, adj meg egy szam erteket!" << std::endl;
        }
        olvas->setEvjarat(bevitel);
    }
    olvas->setSzin(getSzinBor(szam_olvas(file)));
    olvas->setFajta_db(size_olvas(file));
    char **fajatk=new char*[olvas->getFajta_db()];
    for(size_t i=0;i<olvas->getFajta_db();i++){
        fajatk[i]=szoveg_olvas(file);
    }
    olvas->setFajta_string(fajatk);
    return olvas;
}

Wiskey *wiskey_olvas(std::ifstream &file) {
    Wiskey *olvas=new Wiskey();
    olvas->setTipus(whiskey);
    olvas->setNev(szoveg_olvas(file));
    olvas->setGyarto(szoveg_olvas(file));
    olvas->setAlkoholTartalom(float_olvas(file));
    olvas->setTipus_wiskey(szoveg_olvas(file));
    olvas->setErleses(uszam_olvas(file));
    return olvas;
}

Gin *gin_olvas(std::ifstream &file) {
    Gin *olvas=new Gin();
    olvas->setTipus(gin);
    olvas->setNev(szoveg_olvas(file));
    olvas->setGyarto(szoveg_olvas(file));
    olvas->setAlkoholTartalom(float_olvas(file));
    olvas->setSzin(getSzinGin(szam_olvas(file)));
    olvas->setIz(szoveg_olvas(file));
    return olvas;
}

Rum *rum_olvas(std::ifstream &file) {
    Rum *olvas=new Rum(rum);
    olvas->setTipus(rum);
    olvas->setNev(szoveg_olvas(file));
    olvas->setGyarto(szoveg_olvas(file));
    olvas->setAlkoholTartalom(float_olvas(file));
    olvas->setFajta(getFajtaRum(szam_olvas(file)));
    return olvas;
}

Tequila* tequila_olvas(std::ifstream &file) {
    Tequila *olvas=new Tequila();
    olvas->setTipus(tequila);
    olvas->setNev(szoveg_olvas(file));
    olvas->setGyarto(szoveg_olvas(file));
    olvas->setAlkoholTartalom(float_olvas(file));
    olvas->setFajta(getFajtaTequila(szam_olvas(file)));
    return olvas;
}

Sor *sor_olvas(std::ifstream &file) {
    Sor *olvas=new Sor();
    olvas->setTipus(sor);
    olvas->setNev(szoveg_olvas(file));
    olvas->setGyarto(szoveg_olvas(file));
    olvas->setAlkoholTartalom(float_olvas(file));
    olvas->setTipus_sor(szoveg_olvas(file));
    return olvas;
}

Gyumolcsle* gyumolcsle_olvas(std::ifstream &file) {
    Gyumolcsle *olvas=new Gyumolcsle();
    olvas->setTipus(gyumolcsle);
    olvas->setNev(szoveg_olvas(file));
    olvas->setGyarto(szoveg_olvas(file));
    olvas->setGyumolcsszazalek(float_olvas(file));
    return olvas;
}


void Italok::olvasF() {
    std::ifstream file;
    file.open("italok.txt");
    if (!file.is_open())
        throw"nem nyilt meg az italok.txt";
    int tipus;
    while ((file>>tipus)){
        switch (tipus) {
            case 1:
                this->addItal(bor_olvas(file));
                break;
            case 2:
                this->addItal(wiskey_olvas(file));
                break;
            case 3:
                this->addItal(gin_olvas(file));
                break;
            case 4:
               this->addItal(rum_olvas(file));
                break;
            case 5:
               this->addItal(tequila_olvas(file));
                break;
            case 6:
                this->addItal(sor_olvas(file));
                break;
            case 7:
               this->addItal(gyumolcsle_olvas(file));
                break;
            case 8:
                this->addItal(szeszes_olvas(file));
            break;
            case 9:
               this->addItal(ital_olvas(file));
                break;
            default: std::cout<<"Hibás típus"<<std::endl;
            break;
        }
    }
}


void Koktle::kiirF(std::ofstream &os) const {
    os<<this->alapanyag_db;
    os<<"<"<<this->nev<<">";
    for (size_t i=0; i<this->alapanyag_db; i++){
        os<<"<"<<getTipusszam( this->alapanyagok[i]->getTipus())<<"><"<<this->alapanyagok[i]->getNev()<<"><";
        os<<this->menyiseg[i]<<">";
    }
}

void Koktlok::kiirF() const {
    std::ofstream file;
    file.open("koktelok.txt");
    if (!file.is_open())
        throw"nem nyilt meg a koktelok.txt";
    for (size_t i=0; i<koktel_db; i++){
        file<<this->getKoktel(i);
        file<<"\n";
    }
}

void Koktlok::olvasF(Italok &italok ) {
    std::ifstream file;
    file.open("koktelok.txt");
    if (!file.is_open())
        throw"nem nyilt meg a koktelok.txt";
    size_t alapanyag_db;
    while (file>>alapanyag_db){
        char *nev=szoveg_olvas(file);
        Ital **alapanyagok=new Ital*[alapanyag_db];
        unsigned int *menyiseg=new unsigned int[alapanyag_db];
        for (size_t i=0; i<alapanyag_db; i++){
            int tipus=szam_olvas(file);
            switch (tipus) {
                case 1:
                    alapanyagok[i]=ital_letezik_e(italok,szoveg_olvas(file),bor);
                    break;
                case 2:
                    alapanyagok[i]=ital_letezik_e(italok,szoveg_olvas(file),whiskey);
                    break;
                case 3:
                    alapanyagok[i]=ital_letezik_e(italok,szoveg_olvas(file),gin);
                    break;
                case 4:
                    alapanyagok[i]=ital_letezik_e(italok,szoveg_olvas(file),rum);
                    break;
                case 5:
                    alapanyagok[i]=ital_letezik_e(italok,szoveg_olvas(file),tequila);
                    break;
                case 6:
                    alapanyagok[i]=ital_letezik_e(italok,szoveg_olvas(file),sor);
                    break;
                case 7:
                    alapanyagok[i]=ital_letezik_e(italok,szoveg_olvas(file),gyumolcsle);
                    break;
                case 8:
                    alapanyagok[i]=ital_letezik_e(italok,szoveg_olvas(file),alkohols);
                    break;
                case 9:
                    alapanyagok[i]=ital_letezik_e(italok,szoveg_olvas(file),alkohol_mentes);
                    break;
                default:
                    char *nev_ital=szoveg_olvas(file);
                    std::cout<<"Hibás típus ital nev: "<<nev_ital<<  " mi legyen az uj tipus: "<<std::endl;
                    ital_tipus bevit=tipus_bevitel();
                    italok.addItal(nev_ital,bevit);
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,bevit);
                    break;
            }
            menyiseg[i]=uszam_olvas(file);
        }
        this->addKoktel(italok,new Koktle(italok,nev,alapanyag_db,alapanyagok,menyiseg));
    }
}


Ital* ital_letezik_e(Italok &italok,  char *nev, ital_tipus tipus) {
    size_t db=italok.getdb();
    for(size_t i=0; i<db; i++){
        Ital *akt=&italok.getItal(i);
        if(akt->getTipus()==tipus and strcmp(akt->getNev(),nev)==0){
            return akt;
        }
    }
    std::cout<<"\nNem talalhato az ital!: most hozaadjuk a tipus: "<<get_tipus_nev_str(tipus)<<" Nev: "<<nev<<std::endl;
    italok.addItal(nev,tipus);
    return &italok.getItal(db);
}



std::ofstream& operator<<(std::ofstream& os,const Koktle &koktle) {
    koktle.kiirF(os);
    return os;
}


