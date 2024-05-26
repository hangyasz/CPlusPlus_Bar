//
// Created by Zoli on 2024. 04. 17..
//

#include "bevitel_kezel.h"
#include <iostream>
#include <cstring>
#include <limits>

#include "Ital.h"
#include "memtrace.h"


//Buffer torlese
void Komunikacio::bufer_torles(std::istream &is) {
    is.clear(); // Hibaflag törlése
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Beolvasott adatok törlése
}

//szamam beolvasasa
int Komunikacio::int_beolvas(std::ostream &os, std::istream &is) {
    int olvas;
    while(!(is >> olvas)){ //amig nem sikerul beolvasni egy szamot
        bufer_torles(is); //buffer torlese
        os << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
    }
    return olvas; //visszater a beolvasott szammal
}
//float beolvasasa
float Komunikacio::float_beolvas(std::ostream &os, std::istream &is) {
    float olvas;
    while(!(is >> olvas)){ //amig nem sikerul beolvasni egy float szamot
        bufer_torles(is); //buffer torlese
        os << "Hibas bemenet. Kerlek, adj meg egy tizedes szamot!" << std::endl;
    }
    return olvas; //visszater a beolvasott float szammal
}
//unsigned int beolvasasa
unsigned int Komunikacio::unsigned_int_beolvas(std::ostream &os, std::istream &is) {
     unsigned int olvas;
    while(!(is >> olvas)){ //amig nem sikerul beolvasni egy unsigned int szamot
        bufer_torles(is); //buffer torlese
        os << "Hibas bemenet. Kerlek, adj meg egy elojel szamot!" << std::endl;
    }

    return olvas;//visszater a beolvasott unsigned int szammal
}
//size_t beolvasasa
size_t Komunikacio::size_beolvas(std::ostream &os, std::istream &is) {
    size_t olvas;
    while(!(is >> olvas)){ //amig nem sikerul beolvasni egy size_t
        bufer_torles(is); //buffer torlese
        os << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
    }
    return olvas; //visszater a beolvasott size_t
}
//vait fuggveny
void Komunikacio::vait(std::ostream &os, std::istream &is) {
    os << "Nyomjon meg az enter-t a folytatashoz...";
    bufer_torles(is);
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool Komunikacio::bool_beolvas(std::ostream &os, std::istream &is) {
    int olvas;
    while(!(is >> olvas) or (olvas!=0 and olvas!=1)){ //amig nem sikerul beolvasni egy szamot vagy nem 0 vagy 1
        bufer_torles(is); //buffer torlese
        os << "Hibas bemenet. Kerlek, adj meg egy 0 vagy 1-t!" << std::endl;
    }
    return olvas; //visszater a beolvasott szammal
}

//ital tipusok kivalasztasa és viszadasa
size_t Komunikacio::tipus_valszto(std::ostream & os,std::istream &is) {
    os << "Valassz egy ital tipust!" << std::endl;
    for (size_t i = 0; i < TipusInfo::db; i++) { //kiirjuk az ital tipusokat
        os << i+1 << ". " << TipusInfo::ital_nevek[i] <<' ';
    }
    os << std::endl;
    while (true) {
        size_t tipus = size_beolvas(os,is); //beolvasunk egy szamot
        if (tipus>=1 and tipus <= TipusInfo::db) { //ha megfelelo intervallumban van
            return tipus; //visszaterunk a tipussal
        }
        os << "Hibas bemenet. Kerlek, adj meg egy helyes szamot!" << std::endl;
    }
}

//Szöveg beolvasása
String Komunikacio::szoveg_beolvas(std::istream &is) {
    String szoveg;
    is >> szoveg; //beolvassuk a szoveget
    return szoveg; //visszaterunk a szoveggel
}

//adatok kiirasa
void Komunikacio::adatok_kiirasa(const char* szoveg, std::ostream &os) {
    os << szoveg << std::endl; //kiirjuk a szoveget
}

//mennyiseg bekerese
unsigned int Komunikacio::mennyiseg_beker(std::ostream &os, std::istream &is) {
    unsigned int menyiseg=unsigned_int_beolvas(os, is); //beolvasni a mennyiseget
    while (menyiseg==0) {   //elenorizik hogy nem nulla e a mennyiseg
        os<<"nem lehet 0 probálja ujra"<<"\n";
        menyiseg=unsigned_int_beolvas(os, is);
    }
    return menyiseg; //visszater a mennyiseggel
}

//a koktel alapanyagok szamanak bekerese
size_t Komunikacio::db_bekeres(std::ostream &os, std::istream &is) {
    char szoveg[]="Alapanyagok szama: ";
    os<<szoveg;
    size_t db=Komunikacio::size_beolvas(os,is); //beolvasni az alapanyagok szamat
    while (db<2){ //amig az alapanyagok szama nem legalabb 2
        os<<"Legalabb 2 alapanyag kell!"<<std::endl;
        os<<szoveg;
        db=Komunikacio::size_beolvas(os,is); //beolvasni az alapanyagok szamat
    }
    return db;
}





