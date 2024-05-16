//
// Created by Zoli on 2024. 04. 18..
//

#include "faljkezel.h"
#include <iostream>
#include <fstream>
#include "Ital.hpp"
#include <limits>
#include "memtrace.h"

int Ital::getTipus_Szam() const {
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
            std::cerr<<"Hibás típus!"<<std::endl;
        break;
    }
    return 0;
}


void Ital::kiirF(std::ofstream& os) const {
    os<<getTipus_Szam()<<"<"<<nev<<"><"<<gyarto<<">";
}

void SzeszesItalok::kiirF(std::ofstream& os) const {
    Ital::kiirF(os);
    os<<"<"<<alkoholTartalom<<">";
}

void Wiskey::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os);
    os<<"<"<<jeleg<<"><"<<erleses<<">";
}

int Gin::getGinSzin() const {
    switch (szin) {
        case szintelen: return 1;
        case pink: return 2;
        case egyeb: return 3;
        default: std::cerr<< "Hibás szín!"<<std::endl;
        break;
    }
    return 0;
}

void Gin::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os);
    os<<"<"<<getGinSzin()<<"><";
    if(iz.size()!=0)
        os<<iz;
    os<<">";
}
int Rum::getFajta_Szam() const {
    switch (fajta) {
        case fuszeres_rum: return 1;
        case fekete_rum: return 2;
        case arany_rum: return 3;
        case feher_rum: return 4;
        default: std::cerr<<"Hibás fajta!"<<std::endl;
    }
    return 0;
}


void Rum::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os);
    os<<"<"<<getFajta_Szam()<<">";
}


int Tequila::getFajta_Szam() const {
    switch (fajta) {
        case silver: return 1;
        case gold: return 2;
        case aged: return 3;
        default: std::cerr<< "Hibás fajta!"<<std::endl;
    }
    return 0;
}

void Tequila::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os);
    os<<"<"<<getFajta_Szam()<<">";
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



int Bor::getSzin_Szam() const {
    switch (szin) {
        case voros: return 1;
        case rose: return 2;
        case feher: return 3;
        default: std::cerr<<"Hibás szín!"<<std::endl;
        break;
    }
    return 0;
}

void Bor::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os);
    os<<"<"<<evjarat<<"><"<<getSzin_Szam()<<"><"<<fajta_db<<"><";
    if(fajta_db>=1)
        os<<fajta[0];
    for(size_t i=1;i<fajta_db;i++){
        os<<"><"<<fajta[i];
    }
    os<<">";
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

Ital::Ital(std::ifstream &file) {
    setTipus(alkohol_mentes);
    file>>nev;
    file>>gyarto;
}


SzeszesItalok::SzeszesItalok(std::ifstream &file):Ital(file) {
    setTipus(alkohols);
    setAlkoholTartalom(float_olvas(file));
}

void Bor::setSzin(int kap) {
    switch (kap) {
        case 1: szin= voros;
        break;
        case 2: szin= rose;
        break;
        case 3: szin= feher;
        break;
        default: std::cerr<< "Hibás szín!"<<std::endl;
        std::cout<<"Nev: "<<getNev()<<" Gyarto: "<<getGyarto()<<std::endl;
        setSzin();
        break;
    }
}


Bor::Bor(std::ifstream &file):SzeszesItalok(file),fajta(nullptr) {
    this->setTipus(bor);
    this->setEvjarat(szam_olvas(file));
    if(!evjarat_teszt(this->getEvjarat())) {
        std::cout<<"Hibás évjárat: "<<std::endl;
        std::cout<<"Nev: "<<getNev()<<" Gyarto: "<<getGyarto()<<getSzinNev()<<std::endl;
        this->setEvjarat();
    }
    this->setSzin(szam_olvas(file));
    this->setFajta_db(size_olvas(file));
    if(fajta_db!=0) {
        String *fajatk=new String[this->getFajta_db()];
        for(size_t i=0;i<this->getFajta_db();i++){
            file>>fajatk[i];
        }
        this->setFajta_string(fajatk);
    }
    else {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


}

Wiskey::Wiskey(std::ifstream &file):SzeszesItalok(file) {
    this->setTipus(whiskey);
    file>>jeleg;
    this->setErleses(uszam_olvas(file));
}


void Gin::setSzin(int kap) {
    switch (kap) {
        case 1: szin= szintelen;
        break;
        case 2: szin= pink;
        break;
        case 3: szin= egyeb;
        break;
        default: std::cerr<< "Hibás szín!"<<std::endl;
        std::cout<<"Nev: "<<getNev()<<" Gyarto: "<<getGyarto()<<std::endl;
        setSzin();
        break;
    }
}

Gin::Gin(std::ifstream &file):SzeszesItalok(file) {
    setTipus(gin);
    setSzin(szam_olvas(file));
    file>>iz;
}


void Rum::setFajta(int kap) {
    switch (kap) {
        case 1: fajta= fuszeres_rum;
        break;
        case 2: fajta= fekete_rum;
        break;
        case 3: fajta= arany_rum;
        break;
        case 4: fajta= feher_rum;
        break;
        default: std::cerr<< "Hibás fajta!"<<std::endl;
        std::cout<<"Nev: "<<getNev()<<" Gyarto: "<<getGyarto()<<std::endl;
        setFajta();
        break;
    }
}

Rum::Rum(std::ifstream &file):SzeszesItalok(file) {
    setTipus(rum);
    setFajta(szam_olvas(file));
}



void Tequila::setFajta(int kap){
    switch (kap) {
        case 1: fajta= silver;
        break;
        case 2: fajta= gold;
        break;
        case 3: fajta= aged;
        break;
        default: std::cerr<<"Hibás fajta!"<<std::endl;
        std::cout<<"Nev: "<<getNev()<<" Gyarto: "<<getGyarto()<<std::endl;
        setFajta();
    }
}

Tequila::Tequila(std::ifstream &file):SzeszesItalok(file) {
    setTipus(tequila);
    setFajta(szam_olvas(file));
}


Sor::Sor(std::ifstream &file):SzeszesItalok(file) {
    setTipus(sor);
    file>>tipus_sor;
}


Gyumolcsle::Gyumolcsle(std::ifstream &file):Ital(file),gyumolcsszazalek(0) {
    setTipus(gyumolcsle);
    setGyumolcsszazalek(uszam_olvas(file));
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
                this->addItal(new Bor(file));
                break;
            case 2:
                this->addItal(new Wiskey(file));
                break;
            case 3:
                this->addItal(new Gin(file));
                break;
            case 4:
               this->addItal(new Rum(file));
                break;
            case 5:
               this->addItal(new Tequila(file));
                break;
            case 6:
                this->addItal(new Sor(file));
                break;
            case 7:
               this->addItal(new Gyumolcsle(file));
                break;
            case 8:
                this->addItal(new SzeszesItalok(file));
            break;
            case 9:
               this->addItal(new Ital(file));
                break;
            default:
                std::cerr<<"Hibas tipus kreme vigye fell majd kezzel"<<std::endl;
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    }
}


void Koktle::kiirF(std::ofstream &os) const {
    os<<this->alapanyag_db;
    os<<"<"<<this->nev<<">";
    for (size_t i=0; i<this->alapanyag_db; i++){
        os<<"<"<<this->alapanyagok[i]->getTipus_Szam()<<"><"<<this->alapanyagok[i]->getNev()<<"><";
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
        String nev;
        file>>nev;
        Ital **alapanyagok=new Ital*[alapanyag_db];
        unsigned int *menyiseg=new unsigned int[alapanyag_db];
        for (size_t i=0; i<alapanyag_db; i++){
            int tipus=szam_olvas(file);
            String nev_ital;
            file>>nev_ital;
            switch (tipus) {
                case 1:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,bor);
                    break;
                case 2:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,whiskey);
                    break;
                case 3:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,gin);
                    break;
                case 4:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,rum);
                    break;
                case 5:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,tequila);
                    break;
                case 6:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,sor);
                    break;
                case 7:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,gyumolcsle);
                    break;
                case 8:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,alkohols);
                    break;
                case 9:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,alkohol_mentes);
                    break;
                default:
                    std::cout<<"Hibas tipus ital nev: "<<nev_ital<<  " mi legyen az uj jeleg: "<<std::endl;
                    ital_tipus bevit=tipus_valszto();
                    italok.addItal(nev_ital,bevit);
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,bevit);
                    break;
            }
            menyiseg[i]=uszam_olvas(file);
        }
        this->addKoktel(new Koktle(nev,alapanyag_db,alapanyagok,menyiseg));
    }
}


Ital* Koktlok::ital_letezik_e(Italok &italok, String nev, ital_tipus tipus){
    size_t db=italok.getdb();
    for(size_t i=0; i<db; i++){
        Ital *akt=italok.getItalCsilag(i);
        if(akt->getTipus()==tipus and nev==akt->getNev()){
            return akt;
        }
    }
    std::cout<<"\nNem talalhato az ital!: most hozaadjuk a tipus: "<<get_tipus_nev_str(tipus)<<" Nev: "<<nev<<std::endl;
    italok.addItal(nev,tipus);
    italok.kiirF();
    return italok.getItalCsilag(db);
}



std::ofstream& operator<<(std::ofstream& os,const Koktle &koktle) {
    koktle.kiirF(os);
    return os;
}


