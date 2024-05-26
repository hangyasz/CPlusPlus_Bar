//
// Created by Zoli on 2024. 04. 13..
//

#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "koktle.h"
#include "bevitel_kezel.h"
#include "fugvenyek.hpp"
#include "Ital.h"
#include "memtrace.h"



Koktle::Koktle(Italok &italok, std::ostream &os, std::istream &is): alapanyag_db(0), alapanyagok(nullptr), menyiseg(nullptr){
    Nev_bevitel(os, is); //beallitja a koktel nevet
    alapanyagok_beker(italok, os, is); //beallitja az alapanyagokat

}

//kirju a koktelt osztaly tartalmat az outputra
void Koktle::kiir(std::ostream &os) const {
    os<<"Koktel neve: "<<nev; //kiirja a koktel nevet
    for (size_t i=0; i<alapanyag_db; i++){ //vegigmegy az alapanyagokon és kirjuk hogy a hanyadik a neve es mennyiseget
        os<<" ["<<1+i<<"] "<<"alapanyag: "<<alapanyagok[i]->getTipusNev()<<" "<<alapanyagok[i]->getNev() <<" Mennyiseg: "<<menyiseg[i];
    }
}


//beallitja az alapanyagok mennyiseget
void Koktle::setMennyiseg(unsigned int *kap) {
    if(kap==nullptr)//ha a kapott tomb nullpointer akkor hibat dobunk
        throw "A mennyiseg nem lehet nullpointer!";
    for (size_t i=0; i<alapanyag_db; i++){
        if(kap[i]==0) //ha a mennyiseg 0 akkor hibat dobunk
            throw "A mennyiseg nem lehet 0!";
    }
    menyiseg=kap; //beallitjuk a mennyiseget
}
//beallitja az alapanyagokat
void Koktle::setAlapanyagok(Ital **kap) {
    if(kap==nullptr) //ha a kapott tomb nullpointer akkor hibat dobunk
        throw "Az alapanyagok nem lehet uresek!";
    for (size_t i=0; i<alapanyag_db; i++){
        if(kap[i]==nullptr) //ha a kapott tomb egy eleme nullpointer akkor hibat dobunk
            throw "Az alapanyag nem lehet nullpointer!";
    }
    alapanyagok=kap; //beallitjuk az alapanyagokat
}

//alapanyagok bekerese
void Koktle::alapanyagok_beker(Italok &italok, std::ostream &os, std::istream &is) {
   size_t db=Komunikacio::db_bekeres(os,is); //beolvasni az alapanyagok szamat
    size_t i=0;
    while (i<db){ //amig az alapanyagok szama nem egyenlo az i-vel
        ++i;
        try{
            addAlapanyag(italok,os,is); //anyyiszor hivjuk meg az addAlapanyag fuggvenyt amennyi az alapanyag db
        }catch (const char *s){
            os<<s<<std::endl;
            os<<"ujra probaljuk ha tobszor sem sikrul inditsa ujra a programot"<<std::endl;
            --i; //ha nem sikerult az alapanyagot hozzaadni akkor ujra probaljuk
        }
    }

}


//uj alapanyag hozzaadasa a koktelhez
void Koktle::addAlapanyag(Italok &italok, std::ostream &os, std::istream &is) {
    char szoveg[]="\nAlapanyag index: ";
    Ital **uj_alapanyagok = new Ital*[alapanyag_db+1]; //letrhozunk egy uj alapanyagok tombot ami egyel nagyobb mint az eredeti az alapanyagnak
    unsigned int *uj_mennyiseg = new unsigned int[alapanyag_db+1]; //letrehozunk egy uj mennyiseg tombot ami egyel nagyobb mint az eredeti a menyisegnek
    //atmasoljuk az eredeti alapanyagokat es mennyisegeket az uj tombokbe
    Dinamikus::din_atmasol(uj_alapanyagok, alapanyagok, alapanyag_db);
    Dinamikus::din_atmasol(uj_mennyiseg, menyiseg, alapanyag_db);
    italok.kiir_index(os); //kiirjuk az italokat
    os<<szoveg;
    size_t index=Komunikacio::size_beolvas(os, is); //beolvasni az indexet amelyik italt hozza akarjuk adni
    while (index>italok.getdb()){
        os<<"Hibas index!"<<std::endl;
        italok.kiir_index(os);
        os<<szoveg;
        index=Komunikacio::size_beolvas(os,is);
    }
    //ha a 0 indexet valasztja akkor uj italt adhat hozza
    if(index==0){
        italok.addItal(os,is);
        index=italok.getdb(); //az uj alapanyag indexe a legutolso lesz
        italok.kiirF();
    }
    try {
        uj_alapanyagok[alapanyag_db] = &italok.getItal(index-1); //a tobb uj eleme legyen a kivalsztot indexu elem
    } catch (const char *s) {
        delete [] uj_alapanyagok;
        delete [] uj_mennyiseg;
        throw   "Nem sikerult az italt hozadni ";
    }
    os<<"Mennyiseg: ";
    uj_mennyiseg[alapanyag_db] = Komunikacio::mennyiseg_beker(os,is); //az uj mennyiseg tomb utolso eleme legyen a beolvasott mennyiseg
    //töroljuk az eredeti alapanyagokat es mennyisegeket
    delete [] this->alapanyagok;
    delete [] this->menyiseg;
    //az uj tombokat allitjuk be az eredetik helyere
    alapanyagok = uj_alapanyagok;
    menyiseg = uj_mennyiseg;
    alapanyag_db++; //az alapanyagok szamat noveljuk
}

void Koktle::removeAlapanyag(std::ostream &os, std::istream &is) {
    if(alapanyag_db==0) { //ha nincsenek alapanyagok akkor kiirjuk hogy nincsenek es visszaterunk
        os<<"A koktelnak nincsen alapnyagai!"<<std::endl;
        return;
    }
    kiir(os); //kiirjuk a koktelt
    char szoveg[]="\nTorolni kivant Alapanyag index: ";
    os<<szoveg;
    size_t index=Komunikacio::size_beolvas(os, is); //beolvasni a torolni kivant alapanyag indexet
    while (index>alapanyag_db){
        os<<"Hibas index!\n";
        kiir(os);
        os<<szoveg;
        index=Komunikacio::size_beolvas(os, is);
    }
    if(index==0) { //ha 0-t valasztott akkor visszaterunk
        return;
    }
    if(alapanyag_db-1==0) {
        removeAlapanyag();
        return;
    }
    Ital **uj_alapanyagok = new Ital*[alapanyag_db-1]; //letrehozunk egy uj alapanyagok tombot ami egyel kisebb mint az eredeti az alapanyagnak
    unsigned int *uj_mennyiseg = new unsigned int[this->alapanyag_db-1]; //letrehozunk egy uj mennyiseg tombot ami egyel kisebb mint az eredeti a menyisegnek
    //atmasoljuk az eredeti alapanyagokat es mennyisegeket az uj tombokbe
    Dinamikus::din_atmasol(uj_alapanyagok, alapanyagok, alapanyag_db, index-1);
    Dinamikus::din_atmasol(uj_mennyiseg, menyiseg, alapanyag_db, index-1);
    //toroljuk az eredeti alapanyagokat es mennyisegeket
    delete [] this->alapanyagok;
    delete [] this->menyiseg;
    //az uj tombokat allitjuk be az eredetik helyere
    this->alapanyagok = uj_alapanyagok;
    this->menyiseg = uj_mennyiseg;
    //az alapanyagok szamat csokkentjuk
    --alapanyag_db;

}

//Eltalvoltja a kapot italt a kotelbol
void Koktle::removeAlapanyag(Ital *ital) {
    size_t index=tartalmaz_e(ital); //megnezzuk hogy benne van e az ital
    while (index!=0) {  //amig benne van az ital
            if(alapanyag_db-1==0) { //ha csak egy alapanyag van akkor toroljuk
                removeAlapanyag();
                return;
            }
            --index;//az indexet csokkentjuk mert a tartalmaz_e 1-el nagyobbat ad vissza
            //letrehozunk egy uj alapanyagok tombot ami egyel kisebb mint az eredeti az alapanyagnak
            Ital **uj_alapanyagok = new Ital*[alapanyag_db-1];
            unsigned int *uj_mennyiseg = new unsigned int[alapanyag_db-1];
            //atmasoljuk az eredeti alapanyagokat es mennyisegeket az uj tombokbe
            Dinamikus::din_atmasol(uj_alapanyagok, alapanyagok, alapanyag_db, index);
            Dinamikus::din_atmasol(uj_mennyiseg, menyiseg, alapanyag_db, index);
            //toroljuk az eredeti alapanyagokat es mennyisegeket
            delete [] this->alapanyagok;
            delete [] this->menyiseg;
            //az uj tombokat allitjuk be az eredetik helyere
            this->alapanyagok = uj_alapanyagok;
            this->menyiseg = uj_mennyiseg;
            --alapanyag_db; //az alapanyagok szamat csokkentjuk
        index=tartalmaz_e(ital);
        }
    }

void Koktle::removeAlapanyag() {
    alapanyag_db=0;//alapnyag szam nullara allitasa
    delete [] alapanyagok;
    delete [] menyiseg;
    menyiseg=nullptr;
    alapanyagok=nullptr;
}



//viszaadja a kereset ittal indexet +1 0 ha nincs benne
size_t Koktle::tartalmaz_e(Ital* kap) const {
    //vegigmegy az alapanyagokon es ha megtalalja az italt akkor visszaadja az indexet +1
    for (size_t i=0; i<alapanyag_db; i++){
        if (kap == alapanyagok[i]){
            return i+1;
        }
    }
    return 0;
}
//viszaadja hogy tartalmaz e adott alapanyag tipust
bool Koktle::tartalmaz_e(size_t tipus) const {
    for (size_t i=0; i<alapanyag_db; i++){
        if (tipus == alapanyagok[i]->getTipus()){
            return true;
        }
    }
    return false;
}

//belaitja a koktel nevet
void Koktle::Nev_bevitel(std::ostream &os, std::istream &is) {
    os<<"Koktel neve: ";
    try {
        setNev(Komunikacio::szoveg_beolvas(is)); //beolvasni a koktel nevet és meprobáljuk bealitani
    }catch (const char * hibba) { //ha nem sikerült ujra probáljuk
        os<<hibba<<std::endl;
        Nev_bevitel(os,is);
    }

}

void Koktle::setNev(String kap) {
    if(Elenorzes::ures_string(kap))
        throw "A nev nem lehet ures!";
    nev=kap;
}


//visszaadja a koktel nevet
String Koktle::getNev() const {
    return nev;
}

//beallitja az alapanyagok szamat
void Koktle::setAlapanyagDb(size_t db) {
    Elenorzes::alapanyag_szam(db); //elenorizzuk hogy megfelelo e az alapanyagok szama
    alapanyag_db=db; //beallitjuk az alapanyagok szamat
}

//elvegezhetunk modositasokst a koktelon
void Koktle::modosit(Italok &italok, std::ostream &os, std::istream &is) {
    size_t valaszto;
    do{
        os<<"Mit szeretne csinalni?\n1 - alapanyag hozzaadasa\n2 - alapanyag torlese\n3 - Nev modositasa\n4 - alapanyag adatok";
        Menu::menu_vege(os);
        valaszto=Komunikacio::size_beolvas(os, is); //beolvasni a valasztast
        switch (valaszto) {
            case 1: //ha 1-et valasztott akkor alapanyag hozzaadasa
                addAlapanyag(italok, os, is);
                break;
            case 2: //ha 2-t valasztott akkor alapanyag torlese
                removeAlapanyag(os, is);
                break;
            case 3: //ha 3-t valasztott akkor a nev modositasa
                Nev_bevitel(os, is);
                break;
            case 0: //ha 0-t valasztott akkor nem csinal semmit
                break;
            case 4:
                alapanyagok_adatok(os, is); //ha 5-t valasztott akkor egy alapanyagok adatait irjuk ki
                break;
            default: Menu::hibba(os); //ha mas szamot valasztott akkor hibat irunk ki és ujra kezdjuk
            break;
        }

    }while (valaszto!=0);
}


//Koktel destruktor
Koktle::~Koktle() {
    delete [] alapanyagok;
    delete [] menyiseg;
}

//kirja egy kiválsztot alapanyag adatait
void Koktle::alapanyagok_adatok(std::ostream &os, std::istream &is) const {
    if(alapanyag_db==0) { //ha nincsenek alapanyagok akkor kiirjuk hogy nincsenek es visszaterunk
        os<<"A koktelnak nincsen alapnyagai!"<<std::endl;
        return;
    }
    kiir(os); //kiirjuk a koktelt
    os<<"\nAlapanyag index: ";
    size_t index=Komunikacio::size_beolvas(os, is); //beolvasni a torolni kivant alapanyag indexet
    while (index>alapanyag_db){
        os<<"Hibas index!\n";
        kiir(os);
        os<<"torolni kivant Alapanyag index: ";
        index=Komunikacio::size_beolvas(os, is);
    }
    if(index==0) { //ha 0-t valasztott akkor visszaterunk
        return;
    }
    --index;
    alapanyagok[index]->kiir(os); //kiirjuk az adott indexu alapanyagot
    os<<"\n";
    Komunikacio::vait(os, is); //varakozas
}

//konstruktor Koktle parameter kent kapott adatokat beallitja
Koktle::Koktle(String nev_kap, size_t alapanyag_db_kap, Ital **alapanyagok_kap, unsigned int *menyiseg_kap) {
    setNev(nev_kap);
    setAlapanyagDb(alapanyag_db_kap);
    setMennyiseg(menyiseg_kap);
    setAlapanyagok(alapanyagok_kap);
}

//Koktlok parameter nelkul konstruktor
Koktlok::Koktlok():koktelok(nullptr),koktel_db(0) {
    //a koktelok tombot nullpointerre allitjuk es a koktel_db-t 0-ra
}

//viszaadja a koktelok szamat
size_t Koktlok::getKoktelDb() const {
    return  this->koktel_db;
}



//viszaadja a megindexelt koktelt
Koktle& Koktlok::getKoktel(size_t index) const {
    if(index>=this->koktel_db){
        if(koktel_db==0)
            throw "urse a tomb";
        throw "tulindexeles";
    }
    return *this->koktelok[index];
}


//a kapot koktelt hozzaadasa a koktelokhoz
void Koktlok::addKoktel(Koktle *kap) {
    //letrehozunk egy uj koktelok tombot ami egyel nagyobb mint az eredeti a kokteloknak
    Koktle** uj = new Koktle*[koktel_db+1];
    Dinamikus::din_atmasol(uj, koktelok, koktel_db); //atmasoljuk az eredeti koktelokat az uj tombokbe (dinamikus tomb atmasolasa fuggveny)
    uj[koktel_db] = kap; //az utolso eleme legyen a kapott koktel
    //toroljuk az eredeti koktelokat
    delete [] koktelok;
    //az uj tombokat allitjuk be az eredetik helyere
    koktelok = uj;
    //a koktelok szamat noveljuk
    koktel_db++;
}

//a kapot italokbol letrehoz egy koktelt es hozzaadja a koktelokhoz
void Koktlok::addKoktel(Italok &italok, std::ostream &os, std::istream &is) {
    Koktle* uj = new Koktle(italok, os, is); //letrehozunk egy uj koktelt
    addKoktel(uj);    //az uj koktelt hozzaadjuk a koktelokhoz
}

void Koktlok::removeKoktel(std::ostream &os, std::istream &is) {
    if(koktel_db==0) { //ha nincsenek koktelok akkor kiirjuk hogy ures es visszaterunk
        os<<"Nincsen koktelok"<<std::endl;
        return;
    }
    kiir_index(os); //kiirjuk a koktelokat
    os<<"Torolni kivant koktel index: ";
    size_t index = Komunikacio::size_beolvas(os, is); //beolvasni a torolni kivant koktel indexet
    while (index>koktel_db){ //ha tulindexelt akkor hibat irunk ki es ujra beolvasunk
        os<<"Hibas index!"<<std::endl;
        kiir_index(os);
        os<<"Torolni kivant koktel index: ";
        index = Komunikacio::size_beolvas(os, is);
    }
    if(index==0) {//ha 0-t valasztott akkor visszaterunk
        return;
    }
    --index;
    //ha csak egy koktel van akkor toroljuk és visszaterunk
    if(koktel_db-1==0){
        removeKoktel();
        return;
    }
    //letrehozunk egy uj koktelok tombot ami egyel kisebb mint az eredeti a kokteloknak
    Koktle** uj = new Koktle*[koktel_db-1];
    Dinamikus::din_atmasol(uj, koktelok, koktel_db, index); //atmasoljuk az eredeti koktelokat az uj tombokbe (dinamikus tomb atmasolasa fuggveny
    //toroljuk a kaotelt
    delete koktelok[index];
    //toroljuk az eredeti koktelokat
    delete [] koktelok;
    //az uj tombokat allitjuk be az eredetik helyere
    koktelok = uj;
    //a koktelok szamat csokkentjuk
    koktel_db--;
}

//toruljuk az adot indexu koktelt
void Koktlok::removeKoktel(size_t index) {
    if(index>=koktel_db){
        if(koktel_db==0) {
            throw "urse a tomb";
        }
        throw "tulindexeles";
    }
    if(koktel_db-1==0){
        removeKoktel();
        return;
    }
    Koktle** uj = new Koktle*[this->koktel_db-1];
    Dinamikus::din_atmasol(uj,koktelok,koktel_db, index);//atmasoljuk az eredeti koktelokat az uj tombokbe (dinamikus tomb atmasolasa fuggveny
    delete koktelok[index];
    delete [] koktelok;
    koktelok = uj;
    koktel_db--;
}

void Koktlok::removeKoktel() {
    delete koktelok[0];
    delete [] koktelok;
    koktelok=nullptr;
    koktel_db=0;
}


//kiirja a koktelokat tombjuket indexekkel+1
void Koktlok::kiir_index(std::ostream &os) const {
    for (size_t i=0; i<koktel_db;++i) {
        os << "[" << i+1 << "] ";
        koktelok[i]->kiir(os);
        os << '\n';
    }
}

void Koktlok::modosit(Italok &italok, std::ostream &os, std::istream &is) {
    size_t valaszto;
    size_t index;
    do{
        os<<"Mit szeretne csinalni?\n1 - Koktel hozzaadasa\n2 - Koktel torlese\n3 - Koktel modositas\n4 - koktelok kiirasa";
        Menu::menu_vege(os);
        valaszto=Komunikacio::size_beolvas(os, is);
        switch (valaszto) {
            case 1: //ha 1-et valasztott akkor koktel hozzaadasa
                addKoktel(italok, os, is);
                break;
            case 2: //ha 2-t valasztott akkor koktel torles
                removeKoktel(os, is);
                break;
            case 3:
                //ha 3-t valasztott akkor koktel modositasa
                kiir_index(os); //kiirjuk a koktelokat
                os<<"\nAdja meg a modositani kivant koktel indexet: ";
                index=Komunikacio::size_beolvas(os, is);//beolvasni a modositani kivant koktel indexet
                if(index>koktel_db){
                    os<<"Hibas index!"<<std::endl;
                    break;
                }
                if(index==0) //ha 0-t valasztott akkor visszaterunk
                    break;
                try {
                    getKoktel(index-1).modosit(italok, os, is); //a kivalasztott koktel modositasa
                }catch (const char *s){
                    os<<s<<std::endl;
                }
                break;
            case 4: //ha 4-t valasztott akkor koktelok kiirasa outputra
                kiir_index(os);
                break;
            case 0:
                break; //ha 5-t valasztott akkor nem csinal semmit
            default: Menu::hibba(os); //ha mas szamot valasztott akkor hibat irunk ki es ujra kezdjuk
                break;
        }

    }while (valaszto!=0);
    try {
        kiirF();
    } //kiirjuk a koktelokat fajlba
    catch (const char* hiba){
        os<<hiba<<std::endl;
        os<<"Nem sikerult a fajlba iras!"<<std::endl;
        Komunikacio::vait(os, is); //varakozas
    }
}

void Koktlok::veltel_ajanlas(std::ostream &os, std::istream &is) const {
    if(koktel_db==0) { //ha nincsenek koktelok akkor kiirjuk hogy ures es visszaterunk
        os<<"Nincsenek koktelok"<<std::endl;
        return;
    }
    srand(time(0));
    size_t rand_index=rand()% koktel_db; //veletlen index generalasa
    koktelok[rand_index]->kiir(os); //kiirjuk a veletlen koktelt
    os<<"\n";
    Komunikacio::vait(os, is); //varunk egy entert
}

void Koktlok::lista_alapanyagok_szerint(std::ostream &os, std::istream &is) const {
    if(koktel_db==0) { //ha nincsenek koktelok akkor kiirjuk hogy ures es visszaterunk
        os<<"Nincsenek koktelok"<<std::endl;
        return;
    }
    size_t tipus=Komunikacio::tipus_valszto(os, is); //beolvasni az alapanyag tipusat
    size_t db=0;
    for (size_t i=0; i<koktel_db; i++){ //vegigmenni a koktelokon es ha tartalmazza az adott alapanyagot akkor kiirjuk
        if(koktelok[i]->tartalmaz_e(tipus)){
            koktelok[i]->kiir(os);
            os<<"\n";
            ++db;
        }
    }
    if(db==0) //ha nincsenek ilyen alapanyagok akkor kiirjuk hogy nincsenek
        os<<"Nincsen ilyen alapanyagot tartalmazo koktelok"<<std::endl;
    Komunikacio::vait(os, is);//varunk egy entert
}

//Koktelok Destruktor
Koktlok::~Koktlok() {
    for (size_t i=0; i<koktel_db; i++){
        delete koktelok[i]; //torli a koktet
    }

    delete [] koktelok; //torli a koktelok tombot
}

bool Koktlok::removeAlapanyag_Italok(size_t index, Ital *alpanyg, std::ostream &os, std::istream &is) {
    //kiirjuk az alapanyagot amit torolni akarunk
    os<<"Ezt az alapnyagot akarjuk torolni:\n";
    alpanyg->kiir(os);
    //kiirjuk a koktelt amiben benne van az alapanyag
    os<<"\nEzt az alapnyagot tartalmazo koktel"<<std::endl;
    koktelok[index]->kiir(os);
    size_t valaszto;
    do{
        os<<"\n1 - egesz koktel torles\n 2 - csakk az alapanyg torles";
        Menu::menu_vege(os);
        valaszto=Komunikacio::size_beolvas(os, is); //beolvasni a valasztast
        switch (valaszto) {
            case 1: //ha 1-et valasztott akkor az egesz koktel torles
                try {
                    removeKoktel(index);
                }catch (const char *hiba) {
                    os<<hiba<<std::endl;
                    os<<"Nem sikerult a koktel torlese!"<<std::endl;
                    Komunikacio::vait(os, is); //varakozas
                }
                try{
                    kiirF(); //kiirjuk a koktelokat fajlba
                } catch (const char *s) {
                    os << s << std::endl;
                    os<<"Nem sikerult a fajlba iras!"<<std::endl;
                    Komunikacio::vait(os, is); //varakozas
                }
                return false;
            case 2: //ha 2-t valasztott akkor csak az alapanyag torles
                koktelok[index]->removeAlapanyag(alpanyg);
            try{
                kiirF(); //kiirjuk a koktelokat fajlba
            } catch (const char *s) {
                os << s << std::endl;
                os<<"Nem sikerult a fajlba iras!"<<std::endl;
                Komunikacio::vait(os, is); //varakozas
            }
                return false;
            case 0://ha 0-t valasztott akkor visszaterunk megsem szertnemk torolini
                return true;
            default: os<<"Hibas bemenet!"<<std::endl; //ha mas szamot valasztott akkor hibat irunk ki és ujra kezdjuk
                break;
            break;
        }
    }while (valaszto!=3);
    return true;
}

