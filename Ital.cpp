//
// Created by Zoli on 2024. 04. 12..
//

#include "Ital.h"
#include <iostream>
#include <cstring>
#include "bevitel_kezel.h"
#include <limits>
#include <ctime>

#include "fugvenyek.hpp"
#include "gtest_lite.h"
#include "memtrace.h"

size_t get_tipusok_szam() {
    TipusInfo i;
    return i.meret;
}


const char* get_tipus_nev_str(size_t tipus) {
    static const TipusInfo info;
    if(tipus==0 or tipus>get_tipusok_szam())
        throw "Hibas tipus!";
    return info.italkok[tipus-1];
}


//Italok Konstruktorok a mi az itall tipusat kapja parameter kent
Ital::Ital(size_t tipus,std::ostream &os,std::istream &is):tipus(tipus){ //a tipust inicializalolistan alitjuk be
    setNev(os, is); //a nevet bealito fuggveny
    setGyarto(os,is); //a gyartot bealito fuggveny
}

Ital::Ital(){} //alap konstruktor semit nem álit be

//konstruktor nevvel es tipussal kap
Ital::Ital(String nev_kap, size_t tipus,std::ostream &os,std::istream &is): tipus(tipus){  //a tipust inicializalolistan alitjuk be
    nev=nev_kap; //a nev legyen egynlo a kapot nevvel
    setGyarto(os,is); //a gyartot bealito fuggveny
}

Ital::~Ital() {}//destruktor semit nem csinal



//getter a nevhez
String Ital::getNev() const
{
    return nev;
}

//getter a gyartohoz
String Ital::getGyarto() const {
    return gyarto;
}

//getter a tipushoz
size_t Ital::getTipus() const {
    return tipus;
}

//getter a tipus nevehez char* ként
const char*  Ital::getTipusNev() const {
    try {
        return get_tipus_nev_str(tipus);
    } catch (const char *hiba) {
        return hiba;
    }
}

//setter a nevhez
void Ital::setNev(std::ostream &os,std::istream &is) {
    os << "Adja meg az ital nevet: " << std::endl;
    is >> nev; //a nevet beolvasuk az inputrol
}

//setter a nevhez ami kap egy stringet
void Ital::setNev(String kap ) {
    nev=kap; //a nevet beallitjuk a kapott stringre
}

//setter a gyartohoz
void Ital::setGyarto(std::ostream &os,std::istream &is) {
    os << "Adja meg az ital gyartojat " << std::endl;
    is >> gyarto; //a gyartot beolvasuk az inputrol
}

//setter a gyartohoz ami kap egy stringet
void Ital::setGyarto(String kap) {
    gyarto=kap; //a gyartot beallitjuk a kapott stringre
}

//kiirja az ital adatait
void Ital:: kiir(std::ostream &os)  const{
    os << "Nev: " << nev; //kiirja a nevet
    os << " Gyarto: " << gyarto; //kiirja a gyartot
    os << " Fajtaja: " << getTipusNev(); //és a tipusat stringkent
}

//a kapott tipust beáltja az ittal tipusanak;
void Ital::setTipus(size_t kap) {
    if(kap==0 or get_tipusok_szam())
        throw "hibas tipus";
    tipus=kap;
}


//Ez a fuggveny a beallitott adatokat modositja
void Ital::Set(std::ostream & os,std::istream &is) {
    int valasz;
    do {
        kiir(os); //kiirja az ital adatait
        os<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-viszalepes" << std::endl;
        os<<"\nAdja meg az utasitas szamat: ";
        valasz=int_beolvas(os,is); //bekerjeuk a valaszt
        switch (valasz) {
            case 1:
                setNev(os, is); //ha 1 akkor a nevet allitjuk at
            break;
            case 2:
                this->setGyarto(os,is); //ha 2 akkor a gyartot allitjuk at
            break;
            case 3: return; //ha 3 akkor viszalep
            default: os<<"Hibas bemenet!"<<std::endl; //kirjuk hogy hibba elorol kezdokik a folyamt
            break;
        }
    }while (valasz!=3);
}

//szeszes italok
//konstruktorok SzeszesItalok_hoz
SzeszesItalok::SzeszesItalok(size_t tipus, std::ostream &os, std::istream &is) : Ital(tipus,os,is) { //inizalitálo listán meghivom az ital konstruktorát
    intput(os,is); //az alkohol tartalmat beallito fuggveny
}

//parameter nelkuli konstruktor
SzeszesItalok::SzeszesItalok() : Ital(){
}

//konstruktor nevvel es tipussal
SzeszesItalok::SzeszesItalok(String nev_kap, size_t tipus,std::ostream &os, std::istream &is): Ital(nev_kap,tipus,os,is) {
    intput(os, is); //az alkohol tartalmat beallito fuggveny
}

void SzeszesItalok::intput(std::ostream &os, std::istream &is) {
    setAlkoholTartalom(os, is); //az alkohol tartalmat beallito fuggveny
}


//viszaadja az alkohol tartalmat
float SzeszesItalok::getAlkoholTartalom() const {
    return alkoholTartalom;
}

//belehet velle álitani az alkohol tartalmat
void SzeszesItalok::setAlkoholTartalom(std::ostream &os, std::istream &is) {
    os << "Adja meg az alkohol tartalmat: " << std::endl;
    alkoholTartalom=float_beolvas(os,is); //beolvasunk egy float szamot
    try {
        szazalek_tests(alkoholTartalom); //elenorizzuk az alkohol tartalmat
    } catch (const char *hiba) {
        os << hiba << std::endl; //ha hibas akkor hibat irunk ki
        setAlkoholTartalom(os,is); //es ujra beolvasunk
    }
}

//kapot alkohol tartalommal beallitja a kapot alkohol tartalmra
void SzeszesItalok::setAlkoholTartalom(float kap) {
    szazalek_tests(kap); //elenorizzuk az alkohol tartalmat
    alkoholTartalom=kap; //beallitjuk az alkohol tartalmat
}

//kiirja az SzeszesItalok adatait
void SzeszesItalok::kiir(std::ostream &os) const {
    Ital::kiir(os); //kiirja az ital adatait
    os << " Alkohol tartalom: " << alkoholTartalom; //kiirja az alkohol tartalmat
}

//modositja az SzeszesItalok adatait
void SzeszesItalok::Set(std::ostream & os, std::istream& is) {
    int valasz;
    do {
        kiir(os); //kiirja az ital adatait
        os<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-alkohol, 4-viszalepes" << std::endl;
        os<<"\nAdja meg az utasitas szamat: ";
        valasz=int_beolvas(os, is); //bekerjeuk a valaszt
        switch (valasz) {
            case 1:
                setNev(os, is); //ha 1 akkor a nevet allitjuk at
            break;
            case 2:
                setGyarto(os, is); //ha 2 akkor a gyartot allitjuk at
            break;
            case 3:
                setAlkoholTartalom(os, is); //ha 3 akkor az alkohol tartalmat allitjuk at
            break;
            case 4: return; //ha 4 akkor viszater
            default: os<<"Hibas bemenet!"<<std::endl; //kirjuk hogy hibba elorol kezdokik a folyamt
            break;
        }
    }while (valasz!=4);
}

//bor
//bornak az evjara ellenorzes
void evjarat_teszt(int evjarat) {
    time_t now = time(0);
    tm *ltm = localtime(&now);//lekerjuk az aktualis idot
    if (evjarat > 1900 + ltm->tm_year) { //ha az evjarat nagyobb mint az aktualis ev akkor hibas
        throw"Hibas evjarat! Adjon meg egy helyes evjaratot!";
    }
}

//bor konstruktorok
Bor::Bor(size_t tipus, std::ostream &os, std::istream &is) : SzeszesItalok(tipus, os,is),fajta(nullptr),fajta_db(0) { //inizalitálo listán meghivom az SzeszesItalok konstruktorát
    intput(os, is);
}

//parameter nelkuli konstruktor
Bor::Bor():SzeszesItalok(), fajta(nullptr),fajta_db(0) {
}
//konstruktor nevvel es tipussal
Bor::Bor(String nev_kap, size_t tipus, std::ostream &os, std::istream &is):SzeszesItalok(nev_kap,tipus, os,is), fajta(nullptr),fajta_db(0) { //inizalitálo listán meghivom az SzeszesItalok konstruktorát
    intput(os,is); //a bor adatait beallito fuggveny

}
//destruktor
Bor::~Bor() {
    delete[] fajta; //felszabaditjuk a fajtakat
}

void Bor::intput(std::ostream &os, std::istream &is) {
    setEvjarat(os, is); //az evjaratot beallito fuggveny
    setSzin(os, is);    //a szint beallito fuggveny
    os << "Adja meg a fajtak szamat: " << std::endl;
    size_t fajtak=size_beolvas(os,is); //beolvasuk a fajtak szamat
    for (size_t i = 0; i < fajtak; i++) {   //hozadjuk a fajtakat
        addFajta(os,is);
    }
}


//getter az evjarathoz
int Bor::getEvjarat() const {
    return evjarat;
}
//getter a szinhez
size_t Bor::getSzin() const {
    return szin;
}

//getter a szin nevehez
const char* Bor::getSzinNev() const{
    const char *szin_nev[]={"voros","rose","feher"};
    return szin_nev[szin-1];
}

//setter az evjarathoz
void Bor::setEvjarat(std::ostream &os, std::istream &is) {
    os << "Adja meg az evjaratot: " << std::endl;
    evjarat=int_beolvas(os, is); //beolvasunk egy int szamot
    try {
        evjarat_teszt(evjarat); //elenorizzuk az evjaratot
    }catch (const char *hiba) {
        os << hiba << std::endl; //ha hibas akkor hibat irunk ki
        setEvjarat(os, is); //es ujra beolvasunk
    }
}

//setter az evjarathoz ami kap egy intet
void Bor::setEvjarat(int kap) {
    evjarat_teszt(kap); //elenorizzuk az evjaratot
    evjarat=kap; //beallitjuk az evjaratot
}

//setter a szinhez
void Bor::setSzin( std::ostream& os, std::istream &is) {
    os<< "Adja meg a bor szinet: [1]voros, [2]rose, [3]feher" << std::endl;
    try {
        setSzin(size_beolvas(os,is));//beolvasunk egy szamot es beallitjuk a szint
    }catch (const char *hiba) {
        os << hiba << std::endl; //ha hibas akkor kirjuk a bibat hibat irunk ki
        setSzin(os, is); //es ujra beolvasunk

    }
}

//setter a szinhez ami kap sint beallitja a bor szinere
void Bor::setSzin(size_t kap) {
    if(kap>3 or kap<1) //ha a szin nem 1,2,3 akkor hibas
        throw "Hibas szin!";
    szin=kap;
}

//a kapot szamot beálitja a fajtak darab szamara
void Bor::setFajta_db(size_t kap) {
    fajta_db=kap;
}

//a kapat string tombot bealitja a fajta String tombere
void Bor::setFajta_string(String *kap) {
    fajta=kap;
}

//a bor fajtaihoz lehett uj elemet felvini velle
void Bor::addFajta(std::ostream &os, std::istream &is) {
    String * temp = new String [fajta_db + 1]; //nagyobbat tombot hozunk letre
    din_atmasol<String>(temp, fajta, fajta_db); //atmasoljuk a regit
    os << "Adja meg a fajtat: " << std::endl;
    is>> temp[fajta_db] ; //beolvasunk egy stringet
    delete[] fajta; //felszabaditjuk a regit
    fajta = temp;  //beallitjuk az ujat
    fajta_db++; //noveljuk a fajtak szamat
}


//a bornak a faktakit irja ki a kimenetre
void Bor::fajtakiir_index( std::ostream &os) const
{
    for (size_t i = 0; i < fajta_db; i++) { //vegigmegyunk a fajtakon
        os <<1+i<<" - "<< fajta[i] << "\n"; //kiirjuk oket a kimnetre
    }
}


//a bor fajtajit lehet veletorolni
void Bor::removeFajta(std::ostream &os, std::istream &is) {
    fajtakiir_index(os); //kiirjuk a fajtakat indexelve
    os << "Melyik fajtat szeretne torolni?" << std::endl;
    size_t index=size_beolvas(os, is);
    if(index> fajta_db)
        throw "sikrteln torle  tul indexeles";
    if(fajta_db-1==0)
        delete [] fajta;
    else {
        String * temp = new String [fajta_db - 1];
        din_atmasol<String>(temp, fajta,fajta_db, index-1); //atmasoljuk az elso reszt
        delete[] fajta;
        fajta = temp;
    }
    fajta_db--;
    os << "Sikeres torls!" << std::endl;
}


//viszaadja a fajtak darabb szamat
size_t Bor::getFajta_db() const {
    return fajta_db;
}

//a bor osztaly adatait kirjuk az outputra
void Bor::kiir(std::ostream &os) const {
    SzeszesItalok::kiir(os); //szeszes ittal kiíro fugveny
    os << " Evjarat: " << evjarat; //evjatar kirasa
    os << " Szin: " << getSzinNev(); //bor szinenek kirasa
    if (fajta_db > 1) { //a tobb fajta  van akkor fajtakat a csak egy akkor fajtat irunk
        os << " Fajtak:";
    } else {
        os << " Fajta:";
    }
    for (size_t i = 0; i < fajta_db; i++) { //kirjuk a fajtakat
        os <<" ["<<i<<"] "<< fajta[i];
    }
}
//a borok osztály adatait lehet
void Bor::Set(std::ostream &os, std::istream &is) {
    size_t valasz;
    do {
        kiir(os);
        os<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-alkohol, 4-evjart, 5-szin, 6-fajta hozzadas, 7-fajta torles 8-viszalepes" << std::endl;
        os<<"\nAdja meg az utasitas szamat: ";
        valasz=size_beolvas(os, is);
        switch (valasz) {
            case 1:
                setNev(os, is); //ha 1 akkor a nevet allitjuk at
            break;
            case 2:
                setGyarto(os, is); //ha 2 akkor a gyartot allitjuk at
            break;
            case 3:
                setAlkoholTartalom(os, is); //ha 3 akkor az alkohol tartalmat allitjuk at
            break;
            case 4:
                setEvjarat(os, is); //ha 4 akkor az evjaratot allitjuk at
            break;
            case 5:
                setSzin(os, is);    //ha 5 akkor a szint allitjuk at
                break;
            case 6:
                addFajta(os, is); //ha 6 akkor uj fajtat adunk hozza
                break;
            case 7:
                try {
                    removeFajta(os, is); //ha 7 akkor fajtat torlünk
                } catch (const char *hiba) {
                    os << hiba << std::endl; //ha hibas akkor hibat irunk ki
                }
                break;
            case 8: return;
            default: os<<"Hibas bemenet!"<<std::endl; //ha nem megfelelo a bemenet akkor hibat irunk ki és ujra kezdjük
            break;
        }
    }while (valasz!=8);
}

//whiskey
//wiskey osztály konstruktra bealitja az adatokat
Wiskey::Wiskey(size_t ital_tipus,std::ostream& os, std::istream& is) : SzeszesItalok(ital_tipus, os, is) {
    setJeleg_wiskey(os, is); //a wiskey tipusat beallito fuggveny
    setErleses(os, is); //az erleses evet beallito fuggveny
}
//wiskey osztály parameter nelkuli konstruktor
Wiskey::Wiskey():SzeszesItalok() {}

//wiskey osztály konstruktor nevvel es tipussal
Wiskey::Wiskey(String nev_kap,size_t tipus, std::ostream &os, std::istream &is):SzeszesItalok(nev_kap,tipus, os, is) {
    setJeleg_wiskey(os, is); //a wiskey tipusat beallito fuggveny
    setErleses(os, is);   //a erleses evet beallito fuggveny

}

//wiskey osztály destruktor
Wiskey::~Wiskey() {
}
//getter a wiskey tipusahoz
String Wiskey::getJeleg_wiskey() const {
    return jeleg;
}
//getter az erleseshez
unsigned int Wiskey::getErleses() const {
    return erleses;
}

//setter a wiskey jelegezeshez
void Wiskey::setJeleg_wiskey(std::ostream &os,std::istream& is) {
    os << "Adja meg a wiskey tipust: " << std::endl;
    is >> jeleg; //beolvasunk egy stringet
}

//elenorzi az erleses evet
void alkohol_keszul(unsigned int ido) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    if (ido > 100+1900 + static_cast<unsigned int> (ltm->tm_year)) { //kb ennel idosebb alkohol nem lehet
        throw  "Hibas evjarat! Adjon meg egy helyes erelssi idot!";

    }

}
//setter az erleseshez
void Wiskey::setErleses(std::ostream &os, std::istream &is) {
    os << "Adja meg az erleses evet: " << std::endl; //kiirjuk a felhasznalonak hogy adja meg az erleses evet
    erleses=unsigned_int_beolvas(os, is); //beolvasunk egy elojelnelkuli intet
    try {
        alkohol_keszul(erleses); //elenorizzuk az erleses evet
    } catch (const char *hiba) {
        os << hiba << std::endl; //ha hibas akkor hibat irunk ki
        setErleses(os, is); //es ujra beolvasunk
    }
}

//setter az erleseshez ami kap egy szamot és beálitja az erleses evet
void Wiskey::setErleses(unsigned int kap) {
    alkohol_keszul(kap); //elenorizzuk az erleses evet
    erleses=kap; //beálitjuk
}

//a wiskey osztály adatait kirjuk az outputra
void Wiskey::kiir(std::ostream &os) const {
    SzeszesItalok::kiir(os);
    os << " Tipus: " << jeleg;
    os << " Erleses: " << erleses;
}

//a wiskey osztály adatait lehet modositani
void Wiskey::Set(std::ostream &os, std::istream &is) {
        size_t valasz;
        do {
            kiir(os); //kiirja az ital adatait
            os<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto,3-alkohol, 4-wiskey tipud, 5-erleles, 6-viszalepes" << std::endl;
            os<<"\nAdja meg az utasitas szamat: ";
            valasz=size_beolvas(os, is);
            switch (valasz) {
                case 1:
                    setNev(os, is); //ha 1 akkor a nevet allitjuk at
                    break;
                case 2:
                    setGyarto(os,is); //ha 2 akkor a gyartot allitjuk at
                    break;
                case 3:
                    setAlkoholTartalom(os,is); //ha 3 akkor az alkohol tartalmat allitjuk at
                    break;
                case 4:
                    setJeleg_wiskey(os,is); //ha 4 akkor a wiskey tipusat allitjuk at
                    break;
                case 5:
                    setErleses(os, is); //ha 5 akkor az erleses evet allitjuk at
                    break;
                case 6: return; //ha 6 akkor viszalep
                default: os<<"Hibas bemenet!"<<std::endl; //ha nem megfelelo a bemenet akkor hibat irunk ki és ujra kezdjük
                    break;
                break;
            }
        }while (valasz!=6);
    }

//gin
//gin osztály konstruktorok
Gin::Gin(size_t ital_tipus, std::ostream &os,std::istream &is) : SzeszesItalok(ital_tipus,os,is) { //inizalitálo listán meghivom az SzeszesItalok konstruktorát
    setSzin(os, is); //a szint beallito fuggveny
    setIz(os,is); //a izt beallito fuggveny
}
//parameter nelkuli konstruktor
Gin::Gin() :SzeszesItalok(){
}
//konstruktor nevvel es tipussal
Gin::Gin(String nev_kap, size_t tipus,std::ostream &os,std::istream &is):SzeszesItalok(nev_kap,tipus, os,is) { //inizalitálo listán meghivom az SzeszesItalok konstruktorát
    setSzin(os, is); //a szint beallito fuggveny
    setIz(os, is);  //a izt beallito fuggveny

}

//viszater a gin szinvel
String Gin::getSzin() const {
    return szin;
}


//setter a gin szinhez
void Gin::setSzin(std::ostream &os,std::istream &is) {
    os<< "Adja meg a gin szinet: " << std::endl;
    is >> szin; //beolvasunk egy stringet
}


void Gin::setSzin(String kap) {
    szin=kap;
}

//viszater a gin izvel
String Gin::getIz() const {
    return iz;
}

//setter a gin izhez
void Gin::setIz(std::ostream &os, std::istream &is) {
    os<< "A ginek van jelgzetes ize pl(levendulas)  1(igen), 0(nem)" << std::endl;
    if (bool_beolvas(os,is)) { //ha igaz akkor beolvasunk egy stringet
        os << "Adja meg a ginek jellegzetes izet: " << std::endl;
        is >> iz; //és beallitjuk az izt
    } else {
        iz=""; //különben az izt üres stringre allitjuk
    }
}

//setter a gin izhez ami kap egy stringet es beallitja az izt
void Gin::setIz(String kap) {
    iz=kap;
}

//a gin osztály adatait kirjuk az outputra
void Gin::kiir(std::ostream &os)  const{
    SzeszesItalok::kiir(os); //kiirja az ital adatait
    os << " Szin: " << szin; //kiirja a szint
    if (iz.size() !=0 ) { //ha van iz akkor azt is kiirja
        os << " Iz: " << iz;
    }
}

//a gin osztály adatait lehet modositani
void Gin::Set(std::ostream &os, std::istream &is) {
    size_t valasz;
    do {
        kiir(os); //kiirja az ital adatait
        os<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-alkohol, 4-Gin iz, 5-Szin, 6-viszalepes" << std::endl;
        os<<"\nAdja meg az utasitas szamat: ";
        valasz=size_beolvas(os, is);
        switch (valasz) {
            case 1:
                setNev(os, is); //ha 1 akkor a nevet allitjuk at
            break;
            case 2:
                setGyarto(os, is);  //ha 2 akkor a gyartot allitjuk at
            break;
            case 3:
                setAlkoholTartalom(os, is); //3 akkor az alkohol tartalmat allitjuk at
            break;
            case 4:
                setIz(os, is);  //ha 4 akkor az izt allitjuk at
                break;
            case 5:
                setSzin(os, is);    //ha 5 akkor a szint allitjuk at
            break;
            case 6: return; //ha 6 akkor viszater
            default: os<<"Hibas bemenet!"<<std::endl; //ha nem megfelelo a bemenet akkor hibat irunk ki és ujra kezdjük
            break;
        }
    }while (valasz!=7);
}

//gin osztály destruktor
Gin::~Gin() {}


//Fajta
//rum osztály konstruktorok
Fajta::Fajta(size_t tipus, std::ostream &os, std::istream &is) : SzeszesItalok(tipus, os, is) {//inizalitálo listán meghivom az SzeszesItalok konstruktorát
    setFajta(os, is); //a rum fajtajat beallito fuggveny
}

//parameter nelkuli konstruktor
Fajta::Fajta():SzeszesItalok() {
}

//konstruktor nevvel es tipussal
Fajta::Fajta(String nev_kap, size_t tipus, std::ostream &os, std::istream &is):SzeszesItalok(nev_kap,tipus, os ,is) {//inizalitálo listán meghivom az SzeszesItalok konstruktorát
    setFajta(os, is); //a rum fajtajat beallito fuggveny
}


//getter a rum fajtajahoz
String Fajta::getFajta() const {
    return fajta;
}

//setter a rum fajtajahoz
void Fajta::setFajta( std::ostream &os, std::istream &is) {
    os<< "Adja meg a "<<getTipusNev() <<"fajtajt: "<< std::endl;
    is >> fajta; //beolvasunk egy stringet
}

//setter a rum fajtajahoz ami kap ertekere alitja a fajtat
void Fajta::setFajta(String kap) {
    fajta=kap;
}


//a rum osztály adatait kirjuk az outputra
void Fajta::kiir(std::ostream &os) const {
    SzeszesItalok::kiir( os); //kiirja az ital adatait
    os << " Fajta: " << fajta; //kiirja a fajtat
}

//a rum osztály adatait lehet modositani
void Fajta::Set( std::ostream &os, std::istream &is) {
    size_t valasz;
    do {
        kiir(os); //kiirja az ital adatait
        os<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-alkohol, 4-Fajta fajtaja, 5-viszalepes" << std::endl;
        os<<"\nAdja meg az utasitas szamat: ";
        valasz=size_beolvas( os, is);
        switch (valasz) {
            case 1:
                setNev(os,is);
            break;
            case 2:
                setGyarto(os,is);
            break;
            case 3:
                setAlkoholTartalom(os, is);
            break;
            case 4:
                setFajta(os, is);
            break;
            case 5: return;
            default: os<<"Hibas bemenet!"<<std::endl;
            break;
        }
    }while (valasz!=5);
}

/*

//tequila
//tequila osztály konstruktorok
Tequila::Tequila(size_t ital_tipus, std::ostream& os, std::istream &is) : SzeszesItalok(ital_tipus,os,is) { //inizalitálo listán meghivom az SzeszesItalok konstruktorát
    setFajta(os,is); //a tequila fajtajat beallito fuggveny
    setAgave(os,is); //az agave alpanyag beallito fuggveny
}

//parameter nelkuli konstruktor
Tequila::Tequila():SzeszesItalok() {}

//konstruktor nevvel es tipussal
Tequila::Tequila(String nev_kap, size_t tipus, std::ostream &os, std::istream& is):SzeszesItalok(nev_kap,tipus,os,is) {
    setFajta(os, is); //a tequila fajtajat beallito fuggveny
    setAgave(os, is); //az agave alpanyag beallito fuggveny
}


//Tequila fajtajat addja vissza
String Tequila::getFajta() const {
    return fajta;
}

//setter a tequila fajtajahoz
void Tequila::setFajta(std::ostream &os, std::istream &is) {
    os<< "Adja meg a tequila fajtajat: " << std::endl;
    is >> fajta; //beolvasunk egy stringet
}

//setter a tequila fajtajahoz ami kap egy erteket es beallitja a fajtat
void Tequila::setFajta(String kap) {
    fajta=kap;
}

//getter az agavehoz
bool Tequila::getAgave() const {
    return  agave;
}

//setter az agavehoz
void Tequila::setAgave(std::ostream &os, std::istream &is) {
    os<< "Az 100% agave a tequila alapanyaga 1(igen), 0(nem)" << std::endl;
    agave=bool_beolvas(os, is);
}



//setter az agavehoz ami kap egy bool erteket es beallitja az agavet
void Tequila::setAgave(bool kap) {
    agave=kap;
}


//a tequila osztály adatait irja ki az outputra
void Tequila::kiir( std::ostream &os) const {
    SzeszesItalok::kiir(os);
    os << " Fajta: " << fajta;
    if (agave) { //ha igaz akkor kiirjuk hogy igen
        os << " 100% Agave";
    } else { //különben hogy nem
        os << " Nem tudjuk";
    }
}

void Tequila::Set(std::ostream &os, std::istream &is) {
    size_t valasz;
    do {
        kiir(os);
        os<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-alkohol, 4-Tequila fajtaja, 5-Agave, 6-viszalepes" << std::endl;
        os<<"\nAdja meg az utasitas szamat: ";
        valasz=size_beolvas(os, is); //beolvasunk egy szamot
        switch (valasz) {
            case 1:
                setNev(os, is); //ha 1 akkor a nevet allitjuk at
            break;
            case 2:
                setGyarto(os ,is); //ha 2 akkor a gyartot allitjuk at
            break;
            case 3:
                setAlkoholTartalom( os, is); //ha 3 akkor az alkohol tartalmat allitjuk at
            break;
            case 4:
                setFajta(os, is); //ha 4 akkor a tequila fajtajat allitjuk at
            break;
            case 5: //ha 5 akkor az agavet allitjuk at
                setAgave(os, is);
            case 6: return; //ha 5 akkor viszalep
            default: os<<"Hibas bemenet!"<<std::endl; //ha nem megfelelo a bemenet akkor hibat irunk ki és ujra kezdjük
            break;
        }
    }while (valasz!=5);
}

//sor
//sor osztály konstruktorok
Sor::Sor(size_t tipuss, std::ostream &os, std::istream &is) : SzeszesItalok(tipuss, os,is) {
    setTipus_sor(os, is); //a sor tipusat beallito fuggveny
}

//parameter nelkuli konstruktor
Sor::Sor():SzeszesItalok(),tipus_sor(nullptr) {}

Sor::Sor(String nev_kap, size_t tipus, std::ostream &os, std::istream &is): SzeszesItalok(nev_kap,tipus, os,is) {
    setTipus_sor(os,is);    //a sor tipusat beallito fuggveny
}


//getter a sor tipusahoz
String Sor::getTipus_sor() const{
    return tipus_sor;
}
//setter a sor tipusahoz
void Sor::setTipus_sor(std::ostream &os, std::istream &is) {
    os << "Adja meg a sor tipusat: " << std::endl;
    is >> tipus_sor; //beolvasunk egy stringet

}

//setter a sor tipusahoz ami kap egy stringet es beallitja a tipust
void Sor::setTipus_sor(String kap) {
    tipus_sor=kap;
}

//a sor osztály adatait kirjuk az outputra
void Sor::kiir(std::ostream &os) const {
    SzeszesItalok::kiir(os); //meghivjuk a Szeszesital ital kiir fuggvenyt
    os << " Tipus: " << tipus_sor; //kiirja a tipust
}

//destruktor a sor osztálynak
Sor::~Sor() {

}

//a sor osztály adatait lehet modositani
void Sor::Set(std::ostream &os, std::istream &is) {
    size_t valasz;
    do {
        kiir(os);//kiirja az ital adatait
        os<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-alkohol, 4-Sor jeleg, 5-viszalepes" << std::endl;
        os<<"\nAdja meg az utasitas szamat: ";
        valasz=size_beolvas(os, is); //beolvasunk egy szamot
        switch (valasz) {
            case 1:
                setNev(os, is); //ha 1 akkor a nevet allitjuk at
            break;
            case 2:
                setGyarto(os, is); //ha 2 akkor a gyartot allitjuk at
            break;
            case 3:
                setAlkoholTartalom(os, is); //ha 3 akkor az alkohol tartalmat allitjuk at
            break;
            case 4:
                setTipus_sor(os,is); //ha 4 akkor a sor tipusat allitjuk at
            break;
            case 5: return; //ha 5 akkor viszalep
            default: os<<"Hibas bemenet!"<<std::endl; //ha nem megfelelo a bemenet akkor hibat irunk ki és ujra kezdjük
            break;
        }
    }while (valasz!=5);
}
*/

//gyumolcslev
//gyumolcsle osztály konstruktorok
Gyumolcsle::Gyumolcsle(size_t ital_tipus,std::ostream &os, std::istream &is) : Ital(ital_tipus, os,is) {//inizalitálo listán meghivom az Ital konstruktorát
    setGyumolcsszazalek(os, is); //a gyumolcsszazalek beallito fuggveny
}

//parameter nelkuli konstruktor
Gyumolcsle::Gyumolcsle():Ital() {}

Gyumolcsle::Gyumolcsle(String nev_kap, size_t tipus, std::ostream & os, std::istream &is):Ital(nev_kap,tipus, os ,is) {//inizalitálo listán meghivom az Ital konstruktorát
    setGyumolcsszazalek(os, is);//a gyumolcsszazalek beallito fuggveny
}


//getter a gyumolcsszazalekhez
unsigned int Gyumolcsle::getGyumolcsszazalek() const {
    return gyumolcsszazalek;
}

//setter a gyumolcsszazalekhez
void Gyumolcsle::setGyumolcsszazalek(std::ostream &os, std::istream &is) {
    os << "Adja meg a gyumolcsszazalekot: " << std::endl; //kiirjuk a felhasznalonak hogy adja meg a gyumolcsszazalekot
    gyumolcsszazalek=unsigned_int_beolvas(os, is); //beolvasunk egy elojelnelkuli intet
    try {
        szazalek_tests(gyumolcsszazalek); //elenorizzuk a gyumolcsszazalekot
    }catch (const char *hiba) {
        os << hiba << std::endl; //ha hibas akkor hibat irunk ki
        setGyumolcsszazalek(os, is); //es ujra beolvasunk
    }
}

void Gyumolcsle::setGyumolcsszazalek(unsigned int kap) {
    szazalek_tests(kap); //elenorizzuk a gyumolcsszazalekot
    gyumolcsszazalek=kap; //beallitjuk
}

//a gyumolcsle osztály adatait kirjuk az outputra
void Gyumolcsle::kiir(std::ostream &os) const {
    Ital::kiir(os); //kiirja az ital adatait
    os << "Gyumolcsszazalek: " << gyumolcsszazalek; //kiirja a gyumolcsszazalekot
}

//a gyumolcsle osztály adatait lehet modositani
void Gyumolcsle::Set(std::ostream &os, std::istream &is) {
    size_t valasz;
    do {
        kiir(os); //kiirja az ital adatait
        os<< "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto, 3-gyumolcsszazalek, 4-viszalepes" << std::endl;
        os<<"\nAdja meg az utasitas szamat: ";
        valasz=size_beolvas(os, is); //beolvasunk egy szamot
        switch (valasz) {
            case 1:
                setNev(os, is); //ha 1 akkor a nevet allitjuk at
            break;
            case 2:
                setGyarto(os, is); //ha 2 akkor a gyartot allitjuk at
            break;
            case 3:
                setGyumolcsszazalek(os, is); //ha 3 akkor a gyumolcsszazalekot allitjuk at
            break;
            case 4: return; //ha 4 akkor viszalep
            default: os<<"Hibas bemenet!"<<std::endl; //ha nem megfelelo a bemenet akkor hibat irunk ki és ujra kezdjük
            break;
        }
    }while (valasz!=4);
}


//os adatok kiíráas
std::ostream& operator<<(std::ostream& os, const Ital& ital) {
    ital.kiir(os);
    return os;
}
