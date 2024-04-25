//
// Created by Zoli on 2024. 04. 18..
//

#include "faljkezel.h"
#include <iostream>
#include <fstream>
#include "Ital.h"


void Ital::kiirF(std::ofstream& os) const {
    os<<getTipusszam(tipus)<<"<"<<nev<<"><"<<gyarto<<">";
}

void SzeszesItalok::kiirF(std::ofstream& os) const {
    Ital::kiirF(os);
    os<<"<"<<alkoholTartalom<<">";
}
void Bor::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os);
    os<<"<"<<getBorSzin(szin)<<"><"<<fajta_db<<"><";
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
    os<<"<"<<getGinSzin(szin)<<"><"<<iz<<">";
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
        case alkohols: return 8;
        case alkohol_mentes: return 9;
        case bor: return 1;
        case whiskey: return 2;
        case gin: return 3;
        case rum: return 4;
        case tequila: return 5;
        case sor: return 6;
        case gyumolcsle: return 7;
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

int getGinSzin(gin_szin szin) {
    switch (szin) {
        case szintelen: return 1;
        case pink: return 2;
        case egyeb: return 3;
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


int getRumtipus(rum_fajta fajta) {
    switch (fajta) {
        case fuszeres_rum: return 1;
        case fekete_rum: return 2;
        case arany_rum: return 3;
        case feher_rum: return 4;
        default: throw"Hibás fajta!";
    }
}

void ital_kiir(const Italok &kap) {
    std::ofstream file;
    file.open("italok.txt");
    if (!file.is_open())
        throw"nem nyilt meg az italok.txt";
    for(size_t i=0;i<kap.getdb();i++){
        file<<kap.getItal(i)<<"\n";
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
            szoveg[db] = c;
            szoveg[db++] = '\0';
        }
        else{
            char *uj=new char[db+1];
            for(size_t i=0;i<db;i++){
                uj[i]=szoveg[i];
            }
            uj[db]=c;
            uj[db++]='\0';
            delete[] szoveg;
            szoveg=uj;
        }
    }
    return szoveg;
}

int szam_olvas(std::ifstream &file) {
    char kacsacsor;
    unsigned int szam;
    file>>kacsacsor>>szam>>kacsacsor;
    return szam;
}

size_t size_olvs(std::ifstream &file) {
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
    Ital *olvas=new Ital(alkohol_mentes);
    return  olvas;
}

Bor *bor_olvas(std::ifstream &file) {
    Bor *olvas=new Bor(bor);
    return olvas;
}


Ital * italok_beolvas(Italok &kap) {
    std::ifstream file;
    file.open("italok.txt");
    if (!file.is_open())
        throw"nem nyilt meg az italok.txt";
    int tipus;
    while (!file.eof()){
        file>>tipus;
        switch (tipus) {
            case 1:

                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            default: throw "Hibás típus!";
        }
    }
}

