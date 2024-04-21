//
// Created by Zoli on 2024. 04. 18..
//

#include "faljkezel.h"
#include <iostream>
#include <fstream>

std::ofstream& operator<<(std::ofstream& os,const Ital &ital) {
    os<<"<"<<getTipusszam(ital.getTipus())<<"><"<<ital.getNev()<<"><"<<ital.getGyarto()<<">";;
    return os;
}

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

void ital_kiir(const Ital &ital) {
    std::ofstream file;
    file.open("italok.txt");
    if (!file.is_open())
        throw"nem nyilt meg az italok.txt";
    file<<ital;
    file.close();
}
