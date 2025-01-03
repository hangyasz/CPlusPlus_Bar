//
// Created by Zoli on 2024. 04. 18..
//

#include "faljkezel.h"
#include <iostream>
#include <fstream>
#include "bevitel_kezel.h"
#include "Ital.h"
#include <limits>
#include "fugvenyek.hpp"
#include "memtrace.h"




//Az ittal osztály altal tárolt adaokat kiirja egy fajlba <tipus(száma)><nev><gyarto> formátumban
void Ital::kiirF(std::ofstream& os) const {
    os<<tipus<<"<"<<nev<<"><"<<gyarto<<">";
}

//A SzesszesItalok osztály altal tárolt adatokat kiirja egy fajlba <alkoholTartalom> formátumban
void SzeszesItalok::kiirF(std::ofstream& os) const {
    Ital::kiirF(os);//Ital osztály adatok kiirása
    os<<"<"<<alkoholTartalom<<">";
}
//A Whiskey osztály altal tárolt adatokat kiirja egy fajlba <jeleg><erleses> formátumban
void Wiskey::kiirF(std::ofstream& os) const {
    Fajta::kiirF(os);//SzeszesItalok osztály adatok kiirása
    os<<"<"<<erleses<<">";
}


//A Gin osztály altal tárolt adatokat kiirja egy fajlba <szin(száma)><iz> formátumban
void Gin::kiirF(std::ofstream& os) const {
    Fajta::kiirF(os);//Fajta osztály adatok kiirása
    os<<"<";
    if(iz.size()!=0) //ha nem üres a string akkor kerul kiirásra
        os<<iz;
    os<<">";
}


//A Fajta osztály altal tárolt adatokat kiirja egy fajlba <fajta(száma)> formátumban
void Fajta::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os); //SzeszesItalok osztály adatok kiirása
    os<<"<"<<fajta<<">";
}


//A Gyumolcsle osztály altal tárolt adatokat kiirja egy fajlba <gyumolcsszazalek> formátumban
void Gyumolcsle::kiirF(std::ofstream& os) const {
    Ital::kiirF(os); //Ital osztály adatok kiirása
    os<<"<"<<gyumolcsszazalek<<">";
}


//A Bor osztály altal tárolt adatokat kiirja egy fajlba <evjarat><szin(száma)><fajta_db><fajta> formátumban
void Bor::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os); //SzeszesItalok osztály adatok kiirása
    os<<"<"<<evjarat<<"><"<<szin<<"><"<<fajta_db<<"><";
    if(fajta_db>=1)
        os<<fajta[0];
    for(size_t i=1;i<fajta_db;i++){
        os<<"><"<<fajta[i]; //ha tobb fajta van akkor a kovetkezo fajta kiirasa
    }
    os<<">";
}

//Az Italok osztály altal tárolt adatokat kiirja egy fajlba
 void Italok::kiirF() const{
    std::ofstream file;
    file.open("italok.txt"); //megnyitjuk a fajlt
    if (!file.is_open())
        throw"nem nyilt meg az italok.txt";
    for(size_t i=0;i<db;i++){
        file<<getItal(i)<<"\n"; //kiirjuk az italokat a fajlba
    }
    file.close(); //fajl bezarasa
}

//szam_olvas függvény ami egy fajlban található számot olvasbe
int Faljkezel::szam_olvas(std::ifstream &file) {
    char kacsacsor1;
    char kacsacsor2;
    int szam;
    file>>kacsacsor1>>szam>>kacsacsor2; //kacsacsorok közötti szám olvasása
    if(kacsacsor1!='<' or kacsacsor2!='>') //ha nem kacsacsorok között van a szám akkor hibát dob
        throw "Hibás formátum!";
    return szam; //szam viszadása
}
//unsigned int_olvas függvény ami egy fajlban található unsigned int számot olvasbe
unsigned int Faljkezel::uszam_olvas(std::ifstream &file) {
    char kacsacsor1;
    char kacsacsor2;
    unsigned int szam;
    file>>kacsacsor1>>szam>>kacsacsor2; //kacsacsorok közötti szám olvasása
    if(kacsacsor1!='<' or kacsacsor2!='>') //ha nem kacsacsorok között van a szám akkor hibát dob
        throw "Hibás formátum!";
    return szam; //szam viszadása
}

//menyiseg_olvas függvény ami egy fajlban található unsigned int számot olvasbe
unsigned int Faljkezel::menyiseg_olvas(std::ifstream &file) {
    unsigned int olvasot=uszam_olvas(file); //szam beolvasása
    if(olvasot==0) //ha a szam 0 akkor hibát dob
        throw "Nem lehet 0 a mennyiseg!";
    return olvasot; //szam viszadása
}

//size_t_olvas függvény ami egy fajlban található size_t számot olvasbe
size_t Faljkezel::size_olvas(std::ifstream &file) {
    char kacsacsor1;
    char kacsacsor2;
    size_t szam;
    file>>kacsacsor1>>szam>>kacsacsor2; //kacsacsorok közötti szám olvasása
    if(kacsacsor1!='<' or kacsacsor2!='>') //ha nem kacsacsorok között van a szám akkor hibát dob
        throw "Hibás formátum!";
    return szam; //szam viszadása
}

//float_olvas függvény ami egy fajlban található float számot olvasbe
float Faljkezel::float_olvas(std::ifstream &file) {
    char kacsacsor1;
    char kacsacsor2;
    float szam;
    file>>kacsacsor1>>szam>>kacsacsor2; //kacsacsorok közötti szám olvasása
    if(kacsacsor1!='<' or kacsacsor2!='>') //ha nem kacsacsorok között van a szám akkor hibát dob
        throw "Hibás formátum!";
    return szam; //szam viszadása
}

//string_olvas függvény ami egy fajlban található stringet olvasbe
String Faljkezel::string_olvas(std::ifstream &file) {
    String olvas;
    file>>olvas; //string olvasása
    return olvas; //string viszadása
}

void Faljkezel::adatok_kiir(std::ostream &os, const Ital &ital) {
    os<<"Nev: "<<ital.getNev()<<" Gyarto: "<<ital.getGyarto()<<" Tipus: "<<ital.getTipusNev()<<std::endl; //ital adatok kiirása
}

//Ital osztály konstruktora ami egy fajlban található adatokat olvas be
Ital::Ital(std::ifstream &file,size_t tipus,std::ostream &os, std::istream &is) {
    try{
        setTipus(tipus); //tipus beállítása
    } catch (const char *hiba) {
        Komunikacio::vait(os, is);
        throw hiba;
    }
    setTipus(tipus); //tipus beállítása
    setNeve(Faljkezel::string_olvas(file)); //nev beolvasása
    String gyarto=Faljkezel::string_olvas(file); //gyarto beolvasása
    try{
    setGyarto(gyarto); //gyarto beolvasása}
    } catch (const char *hiba) {
        os<<hiba<<std::endl;
        Faljkezel::adatok_kiir(os, *this); //ha hibás a gyarto akkor kiirja az adatotk
        gyarto_bekeres(os, is); //ha hibás a gyarto akkor megkeri a felhasználót hogy adja meg kezel
    }

}


//SzeszesItalok osztály konstruktora ami egy fajlban található adatokat olvas be
SzeszesItalok::SzeszesItalok(std::ifstream &file,size_t tipus,std::ostream &os, std::istream &is):Ital(file,tipus,os,is) {//inicializálo listán ital konstruktor hívása
    float szazalek=Faljkezel::float_olvas(file); //szazalek beolvasása
    try {
        setAlkoholTartalom(szazalek); //alkohol tartalom beállítása
    } catch (const char *hiba) {
        os<<hiba<<std::endl;
        Faljkezel::adatok_kiir(os, *this); //ha hibás az alkohol tartalom akkor kiirja az adatotk
        alkohol_bealit(os, is); //ha hibás az alkohol tartalom akkor megkeri a felhasználót hogy adja meg kezel
    }
}

//Bor osztály konstruktora ami egy fajlban található adatokat olvasbe
Bor::Bor(std::ifstream &file,size_t tipus, std::ostream &os, std::istream &is):SzeszesItalok(file,tipus,os,is),fajta(nullptr) { //inicializálo listán szeszes italok konstruktor hívása és fajta nullptr-ra állítása
    int evjarat=Faljkezel::szam_olvas(file); //evjarat beolvasása
try {
        setEvjarat(evjarat); //evjarat beállítása
    } catch (const char *hiba) {
        os<<hiba<<std::endl;
        Faljkezel::adatok_kiir(os, *this); //ha hibás az alkohol tartalom akkor kiirja az adatotk
        Evjarat_bevitel(os, is); //ha hibás az evjarat akkor megkeri a felhasználót hogy adja meg kezel
    }
    size_t szin=Faljkezel::size_olvas(file); //szin beolvasása
    try {
        setSzin(szin); //szin beállítása
    }catch (const char *hiba) {
        os<<hiba<<std::endl;
        Faljkezel::adatok_kiir(os, *this); //ha hibás az alkohol tartalom akkor kiirja az adatotk
        Szin_bevitel(os, is); //ha hibás a szin akkor megkeri a felhasználót hogy adja meg kezel
    }
    fajta_db=Faljkezel::size_olvas(file); //fajta db beolvasása
    if(fajta_db!=0) {
        String *fajatk=new String[fajta_db]; //fajta db méretű string tömb létrehozása
        for(size_t i=0;i<fajta_db;i++) {
            try{
                file>>fajatk[i]; //fajtak beolvasása a tömbbe
            }catch (const char *hiba) {
                os<<hiba<<std::endl;
                os<<"nem sikerult beolvasni a fajtakat\n"; //kirjuk hogy a fajtákal van a gond
                delete [] fajatk; //töröljük a dinamikusan lefoglalt memóriát
                fajta_db=0; //fajta db 0-ra állítása
                fajatk=nullptr; //fajta tömb nullptr-ra állítása
                break; //kilépünk a ciklusból
            }
        }
        fajta=fajatk; //fajta tömb legyen a fajatk
    }
}

//Whiskey osztály konstruktora ami egy fajlban található adatokat olvasbe
Wiskey::Wiskey(std::ifstream &file,size_t tipus,std::ostream &os, std::istream &is):Fajta(file, tipus ,os,is) { //inicializálo listán SzeszesItalok konstruktor hívása
    try {
        unsigned int erleses=Faljkezel::uszam_olvas(file); //erleses beolvasása
        setErleses(erleses); //erleses beolvasása és beállítása
    }catch (const char *hiba) {
        os<<hiba<<std::endl;
        Faljkezel::adatok_kiir(os, *this); //ha hibás az alkohol tartalom akkor kiirja az adatotk
        Erleles_bekeres(os, is); //ha hibás az erleses akkor megkeri a felhasználót hogy adja meg kezel
    }
}


//Gin osztály konstruktora ami egy fajlban található adatokat olvasbe
Gin::Gin(std::ifstream &file,size_t tipus,std::ostream &os, std::istream &is):Fajta(file,tipus, os,is) {
    //inicializálo listán SzeszesItalok konstruktor hívása
    try{String iz=Faljkezel::string_olvas(file); //iz beolvasása
        setIz(iz); //iz beállítása
    }catch (const char *hiba) {
            os<<hiba<<std::endl;
            Faljkezel::adatok_kiir(os,*this); //ha hibás az alkohol tartalom akkor kiirja az adatotk
            Iz_bekeres(os, is); //ha hibás az erleses akkor megkeri a felhasználót hogy adja meg kezel
    }
}

//Fajta osztály konstruktora ami egy fajlban található adatokat olvasbe
Fajta::Fajta(std::ifstream &file,size_t tipus,std::ostream &os, std::istream &is):SzeszesItalok(file,tipus,os,is) { //inicializálo listán SzeszesItalok konstruktor hívása
    String fajta=Faljkezel::string_olvas(file); //fajta beolvasása
    try {
        setFajta(fajta); //fajta beállítása
    }catch (const char *hiba) {
        os<<hiba<<std::endl;
        Faljkezel::adatok_kiir(os, *this); //ha hibás az alkohol tartalom akkor kiirja az adatotk
        Fajta_bekeres(os, is); //ha hibás az erleses akkor megkeri a felhasználót hogy adja meg kezel
    }
}


//Gyumolcsle osztály konstruktora ami egy fajlban található adatokat olvasbe
Gyumolcsle::Gyumolcsle(std::ifstream &file,size_t tipus, std::ostream &os, std::istream &is):Ital(file,tipus, os,is) {
    unsigned int szazlel=Faljkezel::uszam_olvas(file); //szazalek beolvasása
    try {
        setGyumolcsszazalek(szazlel); //szazalek beállítása
    }catch (const char * hiba) {
        os<<hiba<<std::endl;
        Faljkezel::adatok_kiir(os, *this); //ha hibás az alkohol tartalom akkor kiirja az adatotk
        gyumolcs_beker(os, is); //ha hibás az erleses akkor megkeri a felhasználót hogy adja meg kezel

    }
}

//Italok osztály fáljbol olvaso függvénye
void Italok::olvasF(std::ostream & os, std::istream &is) {
    std::ifstream file;
    file.open("italok.txt"); //fajl megnyitása italok.txt
    if (!file.is_open())
        throw"nem nyilt meg az italok.txt";
    size_t tipus; //tipus szám beolvasására
    typedef Ital* (*CreateItalFunction)(std::ifstream &,size_t,std::ostream&,std::istream&); //letrehozunk egy pointert ami egy fuggvenyt mutat
    //letrehozunk egy tombot ami a fuggvenyeket tartalmazza
    CreateItalFunction createItalFunction[]={Dinamikus::italok_olvas<Bor>,Dinamikus::italok_olvas<Wiskey>,Dinamikus::italok_olvas<Gin>,Dinamikus::italok_olvas<Fajta>,Dinamikus::italok_olvas<Fajta>,Dinamikus::italok_olvas<Fajta>,Dinamikus::italok_olvas<Gyumolcsle>,Dinamikus::italok_olvas<SzeszesItalok>,Dinamikus::italok_olvas<Ital>};
    size_t max_tipus=TipusInfo::db;
    while (file>>tipus){ //tipus szám beolvasása
        if(tipus<=max_tipus and tipus!=0) {
            //akkor ugrunk a következő sorba ha a tipus szám nem megfelelő
            try {
                addItal(createItalFunction[tipus-1](file,tipus,os,is)); //uj ital hozzaadasa
            } catch (const char *hiba) {
                os<<hiba<<std::endl;
                os<<"kerem nezze majd att a beolvasos italokt mivel nem sikerult teljesen beolvasni";
                Komunikacio::vait(os, is);
            }
        }
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //elhadjuk a az beolvasot adatok utani részt
    }
    try {
        kiirF();
    }catch (const char *hiba) {
        os<<hiba<<std::endl;
        os<<"nem sikerult kiirni az italokat a fajlba";
        Komunikacio::vait(os,is);
    }
}

//Koktel osztály fáljba vallo kiíro fugvénye
void Koktle::kiirF(std::ofstream &os) const {
    os<<alapanyag_db; //alapanyagok számának kiirása
    os<<"<"<<nev<<">"; //nev kiirása kacsacsorok között
    for (size_t i=0; i<alapanyag_db; i++){ //alapanyagok kiirása
        os<<"<"<<alapanyagok[i]->getTipus()<<"><"<<alapanyagok[i]->getNev()<<"><"; //tipus szám, nev kiirása
        os<<menyiseg[i]<<">"; //menyiseg kiirása
    }
}

//Koktolok osztály fáljba vallo kiíro fugvénye
void Koktlok::kiirF() const {
    std::ofstream file;
    file.open("koktelok.txt"); //fajl megnyitása koktelok.txt
    if (!file.is_open())
        throw"nem nyilt meg a koktelok.txt";
    for (size_t i=0; i<koktel_db; i++){ //vegik megyünk a koktelok tobjén és kiirjuk oket a fajlba
        file<<getKoktel(i);
        file<<"\n"; //sor végének kiirása
    }
}

//Koktelok osztály fáljbol olvaso függvénye
void Koktlok::olvasF(Italok &italok, std::ostream &os, std::istream &is) {
    std::ifstream file;
    file.open("koktelok.txt"); //fajl megnyitása koktelok.txt
    if (!file.is_open())
        throw"nem nyilt meg a koktelok.txt";
    size_t alapanyag_db;
    Ital **alapanyagok=nullptr;
    unsigned int *menyiseg=nullptr;
    String nev;
    while (file>>alapanyag_db){ //alapanyagok számának beolvasása
        try {
            alapanyagok=new Ital*[alapanyag_db]; //alapanyagok tömb létrehozása
            menyiseg=new unsigned int[alapanyag_db]; //menyiseg tömb létrehozása
            file>>nev; //nev beolvasása0
            for (size_t i=0; i<alapanyag_db; i++){
                size_t tipus=Faljkezel::size_olvas(file); //tipus szám beolvasása
                String nev_ital=Faljkezel::string_olvas(file); //nev beolvasása
                alapanyagok[i]=ital_letezik_e(italok,nev_ital,tipus, os,is); //ital létezik e függvény meghívása
                menyiseg[i]=Faljkezel::menyiseg_olvas(file); //menyiseg beolvasása
            }
            addKoktel(new Koktle(nev,alapanyag_db,alapanyagok,menyiseg)); //hozzáadjuk a koktelt a tömbhöz és létrehozzuk a kotelt a konstruktorral
        }catch (const char *hiba) {
            //ha hibás a beolvasa akkor töröljük a dinamikusan lefoglalt memóriát
            delete [] alapanyagok;
            delete [] menyiseg;
            os<<hiba<<std::endl;
            os<<"kerem nezze majd att a beolvasos italokt mivel nem sikerult teljesen beolvasni";
            Komunikacio::vait(os, is);
        }
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ha eldobjuk a sorban lévő adatokat

    }
    try {
        kiirF();
    }catch (const char *hiba) {
        os<<hiba<<std::endl;
        os<<"nem sikerult kiirni a koktelokat a fajlba";
        Komunikacio::vait(os,is);
    }
}

//Az italok tömbben nézuk hogy egy alapanyag benne van e ha nincsen hozzáadjuk
Ital* Koktlok::ital_letezik_e(Italok &italok, String nev, size_t tipus, std::ostream &os, std::istream &is) const{
    size_t db=italok.getdb();
    if(tipus==0 or tipus>TipusInfo::db) //ha hibás a tipus akkor hibát dob
        throw "Hibas tipus! ital tipus: ";
    for(size_t i=0; i<db; i++){
        Ital *akt=&italok.getItal(i);
        if(akt->getTipus()==tipus and nev==akt->getNev()){ //ha a tipus és a nev megegyezik akkor visszaadjuk az italt
            return akt;
        }
    }
    os<<"\nNem talalhato az ital!: most hozaadjuk a tipus: "<<TipusInfo::get_tipus_nev_str(tipus)<<" Nev: "<<nev<<std::endl;
    italok.addItal(nev,tipus,os ,is); //ha nem találjuk az italt akkor hozzáadjuk
    try{
        italok.kiirF(); //kiirjuk az italokat a fajlba
    } catch (const char *hiba) {
        os<<hiba<<std::endl;
        os<<"nem sikerult kiirni az italokat a fajlba";
        Komunikacio::vait(os,is);
    }
    return &italok.getItal(db); //visszaadjuk az ujonal hozzáadott italt ami az utolsó helyen van
}

//felüldefiniált << operátor az Ital osztályhoz hogy kiirhassuk az adatokat egy fajlba
std::ofstream& operator<<(std::ofstream& os,const Ital &ital) {
    ital.kiirF(os); //kiirF függvény meghívása az adoott italra
    return os;
}


//felüldefiniált << operátor az Koktle osztályhoz hogy kiirhassuk az adatokat egy fajlba
std::ofstream& operator<<(std::ofstream& os,const Koktle &koktle) {
    koktle.kiirF(os);
    return os;
}


