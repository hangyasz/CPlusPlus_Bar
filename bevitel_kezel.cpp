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
void bufer_torles(std::istream &is) {
    is.clear(); // Hibaflag törlése
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Beolvasott adatok törlése
}

//szamam beolvasasa
int int_beolvas(std::ostream &os, std::istream &is) {
    int olvas;
    while(!(is >> olvas)){ //amig nem sikerul beolvasni egy szamot
        bufer_torles(is); //buffer torlese
        os << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
    }
    return olvas; //visszater a beolvasott szammal
}
//float beolvasasa
float float_beolvas(std::ostream &os, std::istream &is) {
    float olvas;
    while(!(is >> olvas)){ //amig nem sikerul beolvasni egy float szamot
        bufer_torles(is); //buffer torlese
        os << "Hibas bemenet. Kerlek, adj meg egy tizedes szamot!" << std::endl;
    }
    return olvas; //visszater a beolvasott float szammal
}
//unsigned int beolvasasa
unsigned int unsigned_int_beolvas(std::ostream &os, std::istream &is) {
    unsigned int olvas;
    while(!(is >> olvas)){ //amig nem sikerul beolvasni egy unsigned int szamot
        bufer_torles(is); //buffer torlese
        os << "Hibas bemenet. Kerlek, adj meg egy elojel szamot!" << std::endl;
    }
    return olvas;//visszater a beolvasott unsigned int szammal
}
//size_t beolvasasa
size_t size_beolvas(std::ostream &os, std::istream &is) {
    size_t olvas;
    while(!(is >> olvas)){ //amig nem sikerul beolvasni egy size_t
        bufer_torles(is); //buffer torlese
        os << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
    }
    return olvas; //visszater a beolvasott size_t
}
//vait fuggveny
void vait(std::ostream &os, std::istream &is) {
    os << "Nyomjon meg az enter-t a folytatashoz...";
    std::getchar(); //enter megnyomasa
}

bool bool_beolvas(std::ostream &os, std::istream &is) {
    int olvas;
    while(!(is >> olvas) or (olvas!=0 and olvas!=1)){ //amig nem sikerul beolvasni egy szamot vagy nem 0 vagy 1
        bufer_torles(is); //buffer torlese
        os << "Hibas bemenet. Kerlek, adj meg egy 0 vagy 1-t!" << std::endl;
    }
    return olvas; //visszater a beolvasott szammal
}

//ital tipusok kivalasztasa és viszadasa
size_t tipus_valszto(std::ostream & os,std::istream &is) {
    TipusInfo info; //ital tipusokat tartalmazo struktura
    size_t db=info.db; //ital tipusok szama
    os << "Valassz egy ital tipust!" << std::endl;
    for (size_t i = 0; i < db; i++) { //kiirjuk az ital tipusokat
        os << i+1 << ". " << info.ital_nevek[i] <<' ';
    }
    os << std::endl;
    while (true) {
        size_t tipus = size_beolvas(os,is); //beolvasunk egy szamot
        if (tipus>=1 and tipus <= db) { //ha megfelelo intervallumban van
            return tipus; //visszaterunk a tipussal
        }
        os << "Hibas bemenet. Kerlek, adj meg egy helyes szamot!" << std::endl;
    }
}

//adatok kiirasa
void adatok_kiirasa(const char* szoveg, std::ostream &os) {
    os << szoveg << std::endl; //kiirjuk a szoveget
}





