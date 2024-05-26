//
// Created by Zoli on 2024. 04. 12..
//

#include "Ital.h"
#include <iostream>
#include <cstring>
#include "bevitel_kezel.h"
#include <limits>
#include <ctime>
#include <set>

#include "fugvenyek.hpp"
#include "gtest_lite.h"
#include "memtrace.h"


// Definition and initializatim az ital_nevek tartalmát
const char TipusInfo::ital_nevek[9][20] = {
    "Bor", "Whiskey", "Gin", "Rum", "Tequila", "Sor", "Gyumolcsle", "Alkohols", "Alkohol mentes"
};

const char Bor_szin::szin_nevek[3][20] = {
    "Voros", "Feher", "Rose"
};


const char* TipusInfo::get_tipus_nev_str(size_t tipus) {
    if(tipus==0 or tipus>TipusInfo::db)
        throw "Hibas tipus!";
    return TipusInfo::ital_nevek[tipus-1];
}

const char* Bor_szin::get_szin_nev_str(size_t szin) {
    if(szin==0 or szin>Bor_szin::db)
        throw "Hibas szin!";
    return Bor_szin::szin_nevek[szin-1];
}

//elenörizuk hogy a kapt string ures e
bool Elenorzes::ures_string(String szoveg) {
    return strcmp(szoveg.c_str(),"")==0;
}

//bornak az evjara ellenorzes
void Elenorzes::evjarat_teszt(int evjarat) {
    time_t now = time(0);
    tm *ltm = localtime(&now);//lekerjuk az aktualis idot
    if (evjarat > 1900 + ltm->tm_year) { //ha az evjarat nagyobb mint az aktualis ev akkor hibas
        throw"Hibas evjarat! Adjon meg egy helyes evjaratot!";
    }
}

//elenorzi az erleses evet
void Elenorzes::alkohol_keszul(unsigned int ido) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    if (ido > 100+1900 + static_cast<unsigned int> (ltm->tm_year)) { //kb ennel idosebb alkohol nem lehet
        throw  "Hibas evjarat! Adjon meg egy helyes erelssi idot!";

    }

}

//ellenorzi az alapnyag számot
void Elenorzes::alapanyag_szam(size_t kap) {
    if(kap<2) //ha kevesebb mint 2 alapanyag van akkor hibat dob
        throw "A koktelnak legalabb 2 alapanyaga kell!";
}


//modositott menü kiirasa
void Menu::menu_vege(std::ostream &os) {
    os << "\n0 - viszalepes\nAdja meg az utasitas szamat: ";
}

void Menu::modosit_menu_ital(std::ostream &os) {
    os << "\nMit szeretne modositani?\n 1-Nev, 2-Gyarto";
}

void Menu::modosit_menu_szeszes_ital(std::ostream &os) {
    modosit_menu_ital(os);
    os << ", 3-alkohol";
}

void Menu::modosit_menu_bor(std::ostream &os) {
    modosit_menu_szeszes_ital(os);
    os << ", 4-evjart, 5-szin, 6-fajta hozzas, 7-fajta torles";
}

void Menu::modosit_menu_fajta(std::ostream &os) {
    modosit_menu_szeszes_ital(os);
    os<<", 4-fajta";
}

void Menu::modosit_menu_wiskey(std::ostream &os) {
    modosit_menu_fajta(os);
    os << ", 5-erleses";
}

void Menu::modosit_menu_gin(std::ostream &os) {
    modosit_menu_fajta(os);
    os<<", 5-ize";
}

void Menu::modosit_menu_gyumolcsle(std::ostream &os) {
    modosit_menu_ital(os);
    os<<" ,3-gyumolcsszazalek";
}

void Menu::hibba(std::ostream &os) {
    os<<"Hibas bemenet!"<<std::endl;
}






//Italok Konstruktorok a mi az itall tipusat kapja parameter kent
Ital::Ital(size_t tipus,std::ostream &os,std::istream &is):tipus(tipus){ //a tipust inicializalolistan alitjuk be
    nev_bekeres(os, is); //a nevet bealito fuggveny
    gyarto_bekeres(os,is); //a gyartot bealito fuggveny
}


//konstruktor nevvel es tipussal kap
Ital::Ital(String nev_kap, size_t tipus,std::ostream &os,std::istream &is): tipus(tipus){  //a tipust inicializalolistan alitjuk be
    try {
        setNeve(nev_kap); //beallitjuk az ital nevet
    } catch (const char *hiba) {
        os << hiba << std::endl; //ha hibas akkor hibat irunk ki
        nev_bekeres(os,is); //a nevet bealito fuggveny
    }
    gyarto_bekeres(os,is); //a gyartot bealito fuggveny
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
        return TipusInfo::get_tipus_nev_str(tipus);
    } catch (const char *hiba) {
        return hiba;
    }
}

//nev bekerese
void Ital::nev_bekeres(std::ostream &os,std::istream &is) {
    os << "Adja meg az ital nevet: " << std::endl;
    try {
        setNeve(Komunikacio::szoveg_beolvas(is)); //beolvasunk egy stringet
    } catch (const char *hiba) {
        os << hiba << std::endl; //ha hibas akkor hibat irunk ki
        nev_bekeres(os,is); //es ujra beolvasunk
    }
}


//setter a gyartohoz
void Ital::gyarto_bekeres(std::ostream &os,std::istream &is) {
    os << "Adja meg az ital gyartojat " << std::endl;
    try {
        setGyarto(Komunikacio::szoveg_beolvas(is)); //beolvasunk egy stringet
    } catch (const char *hiba) {
        os << hiba << std::endl; //ha hibas akkor hibat irunk ki
        gyarto_bekeres(os,is); //es ujra beolvasunk
    }
}


void Ital::setNeve(String nev_kap) {
    if(Elenorzes::ures_string(nev_kap)) //ha ures a nev akkor hibat dob
        throw "Nem lehet ures a neve!";
    nev=nev_kap; //beallitjuk az ital nevet
}

void Ital::setGyarto(String gyarto_kap) {
    if (Elenorzes::ures_string(gyarto_kap)) //ha ures a gyarto akkor hibat dob
        throw "Nem lehet ures a gyarto!";
    gyarto=gyarto_kap; //beallitjuk az ital gyartot
}



//kiirja az ital adatait
void Ital:: kiir(std::ostream &os)  const{
    os << "Nev: " << nev; //kiirja a nevet
    os << " Gyarto: " << gyarto; //kiirja a gyartot
    os << " Tipusa: " << getTipusNev(); //és a tipusat stringkent
}

//a kapott tipust beáltja az ittal tipusanak;
void Ital::setTipus(size_t kap) {
    if(kap==0 or kap>TipusInfo::db)
        throw "hibas tipus";
    tipus=kap;
}


//Ez a fuggveny a beallitott adatokat modositja
void Ital::modosit(std::ostream & os,std::istream &is) {
    size_t valasz;
    do {
        kiir(os); //kiirja az ital adatait
        Menu::modosit_menu_ital(os); //kiirja a modositasi menut
        Menu::menu_vege(os);
        valasz=Komunikacio::size_beolvas(os,is); //bekerjeuk a valaszt
        switch (valasz) {
            case 1:
                nev_bekeres(os, is); //ha 1 akkor a nevet allitjuk at
            break;
            case 2:
                this->gyarto_bekeres(os,is); //ha 2 akkor a gyartot allitjuk at
            break;
            case  0: return; //ha 0 akkor viszalep
            default: Menu::hibba(os); //kirjuk hogy hibba elorol kezdokik a folyamt
            break;
        }
    }while (valasz!=0);
}

//szeszes italok
//konstruktorok SzeszesItalok_hoz
SzeszesItalok::SzeszesItalok(size_t tipus, std::ostream &os, std::istream &is) : Ital(tipus,os,is) { //inizalitálo listán meghivom az ital konstruktorát
    alkohol_bealit(os, is); //az alkohol tartalmat beallito fuggveny
}


//konstruktor nevvel es tipussal
SzeszesItalok::SzeszesItalok(String nev_kap, size_t tipus,std::ostream &os, std::istream &is): Ital(nev_kap,tipus,os,is) {
    alkohol_bealit(os, is); //az alkohol tartalmat beallito fuggveny
}




//viszaadja az alkohol tartalmat
float SzeszesItalok::getAlkoholTartalom() const {
    return alkoholTartalom;
}

//belehet velle álitani az alkohol tartalmat
void SzeszesItalok::alkohol_bealit(std::ostream &os, std::istream &is) {
    os << "Adja meg az alkohol tartalmat: " << std::endl;

    try {
        setAlkoholTartalom(Komunikacio::float_beolvas(os,is)); //beolvasunk egy float szamot és atadjuk a setternek
    } catch (const char *hiba) {
        os << hiba << std::endl; //ha hibas akkor hibat irunk ki
        alkohol_bealit(os,is); //es ujra beolvasunk
    }
}

//kapot alkohol tartalommal beallitja a kapot alkohol tartalmra
void SzeszesItalok::setAlkoholTartalom(float kap) {
   Tesztek::szazalek_tests(kap); //elenorizzuk az alkohol tartalmat
    alkoholTartalom=kap; //beallitjuk az alkohol tartalmat
}

//kiirja az SzeszesItalok adatait
void SzeszesItalok::kiir(std::ostream &os) const {
    Ital::kiir(os); //kiirja az ital adatait
    os << " Alkohol tartalom: " << alkoholTartalom; //kiirja az alkohol tartalmat
}

//modositja az SzeszesItalok adatait
void SzeszesItalok::modosit(std::ostream & os, std::istream& is) {
    size_t valasz;
    do {
        kiir(os); //kiirja az ital adatait
        Menu::modosit_menu_szeszes_ital(os); //kiirja a modositasi menut
        Menu::menu_vege(os);
        valasz=Komunikacio::size_beolvas(os, is); //bekerjeuk a valaszt
        switch (valasz) {
            case 1:
                nev_bekeres(os, is); //ha 1 akkor a nevet allitjuk at
            break;
            case 2:
                gyarto_bekeres(os, is); //ha 2 akkor a gyartot allitjuk at
            break;
            case 3:
                alkohol_bealit(os, is); //ha 3 akkor az alkohol tartalmat allitjuk at
            break;
            case 0: return; //ha 0 akkor viszater
            default: Menu::hibba(os); //kirjuk hogy hibba elorol kezdokik a folyamt
            break;
        }
    }while (valasz!=0);
}

//destruktor
SzeszesItalok::~SzeszesItalok() {}//ures nincsen dinamikus memoria

//bor


//bor konstruktorok
Bor::Bor(size_t tipus, std::ostream &os, std::istream &is) : SzeszesItalok(tipus, os,is),fajta(nullptr),fajta_db(0) { //inizalitálo listán meghivom az SzeszesItalok konstruktorát
    Evjarat_bevitel(os, is); //az evjaratot beallito fuggveny
    Szin_bevitel(os, is); //a szint beallito fuggveny
    Fafja_bevitel(os, is); //a fajtakat beallito fuggveny
}

//konstruktor nevvel es tipussal
Bor::Bor(String nev_kap, size_t tipus, std::ostream &os, std::istream &is):SzeszesItalok(nev_kap,tipus, os,is), fajta(nullptr),fajta_db(0) { //inizalitálo listán meghivom az SzeszesItalok konstruktorát
    Evjarat_bevitel(os, is); //az evjaratot beallito fuggveny
    Szin_bevitel(os, is); //a szint beallito fuggveny

}
//destruktor
Bor::~Bor() {
    delete[] fajta; //felszabaditjuk a fajtakat
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
    return Bor_szin::get_szin_nev_str(szin);
}

//evjarat bekerese
void Bor::Evjarat_bevitel(std::ostream &os, std::istream &is) {
    os << "Adja meg az evjaratot: " << std::endl;
    try {
        setEvjarat(Komunikacio::int_beolvas(os, is)); //beolvasunk egy intet es beallitjuk az evjaratot
    }catch (const char *hiba) {
        os << hiba << std::endl; //ha hibas akkor hibat irunk ki
        Evjarat_bevitel(os, is); //es ujra beolvasunk
    }
}

//setter az evjarathoz ami kap egy intet
void Bor::setEvjarat(int kap) {
    Elenorzes::evjarat_teszt(kap); //elenorizzuk az evjaratot
    evjarat=kap; //beallitjuk az evjaratot
}

//bor szine bekerese
void Bor::Szin_bevitel( std::ostream& os, std::istream &is) {
    os<< "Adja meg a bor szinet:";
    for (size_t i=0; i<Bor_szin::db; i++) { //vegigmegyunk a szineken
        os<<" " << i+1 << " - " << Bor_szin::get_szin_nev_str(i+1); //kiirjuk oket
    }
    os<<"\n";
    try {
        setSzin(Komunikacio::size_beolvas(os,is));//beolvasunk egy szamot es beallitjuk a szint
    }catch (const char *hiba) {
        os << hiba << std::endl; //ha hibas akkor kirjuk a bibat hibat irunk ki
        Szin_bevitel(os, is); //es ujra beolvasunk

    }
}

//setter a szinhez ami kap sint beallitja a bor szinere
void Bor::setSzin(size_t kap) {
    if(Bor_szin::db<kap or kap==0) //ha a szin nem letezik akkor hibat dob
        throw "Hibas szin!";
    szin=kap;
}

//fajtak rögtitese
void Bor::Fafja_bevitel(std::ostream &os, std::istream &is) {
    char bekeres[]="Adja meg a fajtak szamat: ";
    os << bekeres<< std::endl;
    size_t db=Komunikacio::size_beolvas(os, is); //beolvasunk egy szamot
    while (db==0) {
        os<<"Nem lehet 0 a fajtak szama!\n"<<bekeres<<std::endl; //ha 0 akkor hibat dob
        db=Komunikacio::size_beolvas(os, is); //ujra beolvasunk
    }
    for (size_t i=0;i<db;i++) { //vegigmegyunk a fajtakon
        addFajta(os, is); //beolvasunk egy fajtat
    }
}


//a bor fajtaihoz lehett uj elemet felvini velle
void Bor::addFajta(std::ostream &os, std::istream &is) {
    String * temp = new String [fajta_db + 1]; //nagyobbat tombot hozunk letre
    char kiir[]="Adja meg a fajtat: ";
    Dinamikus::din_atmasol<String>(temp, fajta, fajta_db); //atmasoljuk a regit
    os << kiir<< std::endl;
    String uj_fajta=Komunikacio::szoveg_beolvas(is); //beolvasunk egy fajtat
    while (Elenorzes::ures_string(uj_fajta))
        os<<"Nem lehet ures a fajta!\n"<<kiir<<std::endl; //ha ures a fajta akkor bekerjuk ujra
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
    size_t index=Komunikacio::size_beolvas(os, is);
    if(index> fajta_db or fajta_db==0)
        throw "sikrteln torles  tul indexeles";
    if(index==0) //ha 0 akkor nem torolunk
        return;
    if(fajta_db-1==0) {
        delete [] fajta;
        fajta=nullptr;
    }
    else {
        String * temp = new String [fajta_db - 1];
        Dinamikus::din_atmasol<String>(temp, fajta,fajta_db, index-1); //atmasoljuk az elso reszt
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
        os <<" ["<<i+1<<"] "<< fajta[i];
    }
}
//a borok osztály adatait lehet
void Bor::modosit(std::ostream &os, std::istream &is) {
    size_t valasz;
    do {
        kiir(os);
        Menu::modosit_menu_bor(os); //kiirja a modositasi menut
        Menu::menu_vege(os);
        valasz=Komunikacio::size_beolvas(os, is);
        switch (valasz) {
            case 1:
                nev_bekeres(os, is); //ha 1 akkor a nevet allitjuk at
            break;
            case 2:
                gyarto_bekeres(os, is); //ha 2 akkor a gyartot allitjuk at
            break;
            case 3:
                alkohol_bealit(os, is); //ha 3 akkor az alkohol tartalmat allitjuk at
            break;
            case 4:
                Evjarat_bevitel(os, is); //ha 4 akkor az evjaratot allitjuk at
            break;
            case 5:
                Szin_bevitel(os, is);    //ha 5 akkor a szint allitjuk at
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
            case 0: return; //ha 0 akkor viszalep
            default: Menu::hibba(os); //ha nem megfelelo a bemenet akkor hibat irunk ki és ujra kezdjük
            break;
        }
    }while (valasz!=0);
}

//whiskey
//wiskey osztály konstruktra bealitja az adatokat
Wiskey::Wiskey(size_t ital_tipus,std::ostream& os, std::istream& is) : Fajta(ital_tipus, os, is) {
    Erleles_bekeres(os,is); //az erleses evet beallito fuggveny
}

//wiskey osztály konstruktor nevvel es tipussal
Wiskey::Wiskey(String nev_kap,size_t tipus, std::ostream &os, std::istream &is):Fajta(nev_kap,tipus, os, is) {
    Erleles_bekeres(os,is); //az erleses evet beallito fuggveny

}

//getter az erleseshez
unsigned int Wiskey::getErleses() const {
    return erleses;
}

//setter az erleseshez
void Wiskey::Erleles_bekeres(std::ostream &os, std::istream &is) {
    os << "Adja meg az erleses evet: " << std::endl; //kiirjuk a felhasznalonak hogy adja meg az erleses evet
    try {
        setErleses(Komunikacio::unsigned_int_beolvas(os,is)); //beolvasunk egy unsigned intet es beallitjuk az erleses evet
    } catch (const char *hiba) {
        os << hiba << std::endl; //ha hibas akkor hibat irunk ki
        Erleles_bekeres(os, is); //es ujra beolvasunk
    }
}

//setter az erleseshez ami kap egy szamot és beálitja az erleses evet
void Wiskey::setErleses(unsigned int kap) {
    Elenorzes::alkohol_keszul(kap); //elenorizzuk az erleses evet
    erleses=kap; //beálitjuk
}

//a wiskey osztály adatait kirjuk az outputra
void Wiskey::kiir(std::ostream &os) const {
    Fajta::kiir(os);
    os << " Erleses: " << erleses;
}

//a wiskey osztály adatait lehet modositani
void Wiskey::modosit(std::ostream &os, std::istream &is) {
        size_t valasz;
        do {
            kiir(os); //kiirja az ital adatait
            Menu::modosit_menu_wiskey(os); //kiirja a modositasi menut
            Menu::menu_vege(os);
            valasz=Komunikacio::size_beolvas(os, is);
            switch (valasz) {
                case 1:
                    nev_bekeres(os, is); //ha 1 akkor a nevet allitjuk at
                    break;
                case 2:
                    gyarto_bekeres(os,is); //ha 2 akkor a gyartot allitjuk at
                    break;
                case 3:
                    alkohol_bealit(os,is); //ha 3 akkor az alkohol tartalmat allitjuk at
                    break;
                case 4:
                    Fajta_bekeres(os,is); //ha 4 akkor a wiskey tipusat allitjuk at
                    break;
                case 5:
                    Erleles_bekeres(os, is); //ha 5 akkor az erleses evet allitjuk at
                    break;
                case 0: return; //ha 0 akkor viszalep
                default: Menu::hibba(os); //ha nem megfelelo a bemenet akkor hibat irunk ki és ujra kezdjük
                    break;
                break;
            }
        }while (valasz!=0);
    }

//gin
//gin osztály konstruktorok
Gin::Gin(size_t ital_tipus, std::ostream &os,std::istream &is) : Fajta(ital_tipus,os,is) { //inizalitálo listán meghivom az SzeszesItalok konstruktorát
    Iz_bekeres(os,is);
}


//konstruktor nevvel es tipussal
Gin::Gin(String nev_kap, size_t tipus,std::ostream &os,std::istream &is):Fajta(nev_kap,tipus, os,is) { //inizalitálo listán meghivom az SzeszesItalok konstruktorát
    Iz_bekeres(os,is);

}

//viszater a gin izvel
String Gin::getIz() const {
    return iz;
}

//setter a gin izhez
void Gin::Iz_bekeres(std::ostream &os, std::istream &is) {
    char kiir[]="Adja meg a ginek jellegzetes izet: ";
    char valsto[]="A ginek van jelgzetes ize pl(levendulas)  1(igen), 0(nem)";
    os<< valsto << std::endl;
    String ize="";
    if (Komunikacio::bool_beolvas(os,is)) {
        //ha igaz akkor beolvasunk egy stringet
        os << kiir << std::endl;
        ize=Komunikacio::szoveg_beolvas(is);
    }
    setIz(ize); //beallitjuk az izt
}

//setter a gin izhez ami kap egy stringet es beálitja az izt
void Gin::setIz(String kap) {
    //ha ures a sting akkor nincsen ize ha nem akkor van;
    iz=kap; //beallitjuk az izt a kapott stringre
}

//a gin osztály adatait kirjuk az outputra
void Gin::kiir(std::ostream &os)  const{
    Fajta::kiir(os); //kiirja az ital adatait
    if (iz.size() !=0 ) { //ha van iz akkor azt is kiirja
        os << " Iz: " << iz;
    }
}

//a gin osztály adatait lehet modositani
void Gin::modosit(std::ostream &os, std::istream &is) {
    size_t valasz;
    do {
        kiir(os); //kiirja az ital adatait
        Menu::modosit_menu_gin(os); //kiirja a modositasi menut
        Menu::menu_vege(os);
        valasz=Komunikacio::size_beolvas(os, is);
        switch (valasz) {
            case 1:
                nev_bekeres(os, is); //ha 1 akkor a nevet allitjuk at
            break;
            case 2:
                gyarto_bekeres(os, is);  //ha 2 akkor a gyartot allitjuk at
            break;
            case 3:
                alkohol_bealit(os, is); //3 akkor az alkohol tartalmat allitjuk at
            break;
            case 5:
                Iz_bekeres(os, is);  //ha 4 akkor az izt allitjuk at
                break;
            case 4:
                Fajta_bekeres(os, is);    //ha 5 akkor a szint allitjuk at
            break;
            case 0: return; //ha 0 akkor viszater
            default: Menu::hibba(os); //ha nem megfelelo a bemenet akkor hibat irunk ki és ujra kezdjük
            break;
        }
    }while (valasz!=0);
}


//Fajta
//rum osztály konstruktorok
Fajta::Fajta(size_t tipus, std::ostream &os, std::istream &is) : SzeszesItalok(tipus, os, is) {//inizalitálo listán meghivom az SzeszesItalok konstruktorát
    Fajta_bekeres(os, is); //a fajtajat beallito fuggveny
}


//konstruktor nevvel es tipussal
Fajta::Fajta(String nev_kap, size_t tipus, std::ostream &os, std::istream &is):SzeszesItalok(nev_kap,tipus, os ,is) {//inizalitálo listán meghivom az SzeszesItalok konstruktorát
    Fajta_bekeres(os, is); //a fajtajat beallito fuggveny
}

//getter a fajtajahoz
String Fajta::getFajta() const {
    return fajta;
}

//bekeres a fajtajahoz
void Fajta::Fajta_bekeres( std::ostream &os, std::istream &is) {
    os<< "Adja meg a "<<getTipusNev() <<" fajtajt: "<< std::endl;
    try {
        setFajta(Komunikacio::szoveg_beolvas(is));
    }catch (const char *hiba) {
        os << hiba << std::endl;
        Fajta_bekeres(os, is);
    }
}

//setter fajtajahoz ami kap egy stringet es beálitja a fajtat
void Fajta::setFajta(String kap) {
    if(Elenorzes::ures_string(kap))
        throw "Nem lehet ures a fajta!";
    fajta=kap;
}

//a fajta osztály adatait kirjuk az outputra
void Fajta::kiir(std::ostream &os) const {
    SzeszesItalok::kiir( os); //kiirja az ital adatait
    os << " Fajta: " << fajta; //kiirja a fajtat
}

//a fajta osztály adatait lehet modositani
void Fajta::modosit( std::ostream &os, std::istream &is) {
    size_t valasz;
    do {
        kiir(os); //kiirja az ital adatait
        Menu::modosit_menu_fajta(os); //kiirja a modositasi menut
        Menu::menu_vege(os);
        valasz=Komunikacio::size_beolvas( os, is);
        switch (valasz) {
            case 1:
                nev_bekeres(os,is);
            break;
            case 2:
                gyarto_bekeres(os,is);
            break;
            case 3:
                alkohol_bealit(os, is);
            break;
            case 4:
                Fajta_bekeres(os, is);
            break;
            case 0: return; //ha 0 akkor viszater
            default: Menu::hibba(os);
            break;
        }
    }while (valasz!=0);
}

Fajta::~Fajta() {} //üres nemincsen dinaminus memória

//gyumolcslev
//gyumolcsle osztály konstruktorok
Gyumolcsle::Gyumolcsle(size_t ital_tipus,std::ostream &os, std::istream &is) : Ital(ital_tipus, os,is) {//inizalitálo listán meghivom az Ital konstruktorát
    gyumolcs_beker(os,is); //az gyumolcsszazalekot bekérő fuggveny
}


Gyumolcsle::Gyumolcsle(String nev_kap, size_t tipus, std::ostream & os, std::istream &is):Ital(nev_kap,tipus, os ,is) {//inizalitálo listán meghivom az Ital konstruktorát
    gyumolcs_beker(os,is); //az gyumolcsszazalekot bekérő fuggveny
}


//getter a gyumolcsszazalekhez
unsigned int Gyumolcsle::getGyumolcsszazalek() const {
    return gyumolcsszazalek;
}

//gyumolcsszazalek bekerese
void Gyumolcsle::gyumolcs_beker(std::ostream &os, std::istream &is) {
    os << "Adja meg a gyumolcsszazalekot: " << std::endl; //kiirjuk a felhasznalonak hogy adja meg a gyumolcsszazalekot
    try {
        setGyumolcsszazalek(Komunikacio::unsigned_int_beolvas(os,is)); //beolvasunk egy unsigned intet es beallitjuk a gyumolcsszazalleknak
    }catch (const char *hiba) {
        os << hiba << std::endl; //ha hibas akkor hibat irunk ki
        gyumolcs_beker(os, is); //es ujra beolvasunk
    }
}

void Gyumolcsle::setGyumolcsszazalek(unsigned int kap) {
    Tesztek::szazalek_tests(kap); //elenorizzuk a gyumolcsszazalekot
    gyumolcsszazalek=kap; //beallitjuk
}

//a gyumolcsle osztály adatait kirjuk az outputra
void Gyumolcsle::kiir(std::ostream &os) const {
    Ital::kiir(os); //kiirja az ital adatait
    os << " Gyumolcsszazalek: " << gyumolcsszazalek; //kiirja a gyumolcsszazalekot
}

//a gyumolcsle osztály adatait lehet modositani
void Gyumolcsle::modosit(std::ostream &os, std::istream &is) {
    size_t valasz;
    do {
        kiir(os); //kiirja az ital adatait
        Menu::modosit_menu_gyumolcsle(os); //kiirja a modositasi menut
        Menu::menu_vege(os);
        valasz=Komunikacio::size_beolvas(os, is); //beolvasunk egy szamot
        switch (valasz) {
            case 1:
                nev_bekeres(os, is); //ha 1 akkor a nevet allitjuk at
                break;
            case 2:
                gyarto_bekeres(os, is); //ha 2 akkor a gyartot allitjuk at
                break;
            case 3:
                gyumolcs_beker(os, is); //ha 3 akkor a gyumolcsszazalekot allitjuk at
                break;
            case 0: return; //ha 0 akkor viszalep
            default: Menu::hibba(os); //ha nem megfelelo a bemenet akkor hibat irunk ki és ujra kezdjük
                break;
        }
    }while (valasz!=0);
}


//os adatok kiíráas
std::ostream& operator<<(std::ostream& os, const Ital& ital) {
    ital.kiir(os);
    return os;
}
