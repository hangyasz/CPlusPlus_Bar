//
// Created by Zoli on 2024. 04. 12..
//

#ifndef ITALOK_H
#define ITALOK_H


#include <iostream>
#include <cstring>
#include "bevitel_kezel.h"
#include "string5.h"

//elöre deklarációk
class Koktlok;

//italok tipusai
enum ital_tipus {
    alkohols, alkohol_mentes, bor, whiskey, gin, rum, tequila, sor, gyumolcsle
};

//italok tipusainak nevei
const char* get_tipus_nev_str(ital_tipus tipus);

//bor szinei
enum szinek_bor {
    voros, rose, feher
};

//gin szinei
enum gin_szin {
    szintelen, pink, egyeb
};

//rum fajtai
enum rum_fajta {
    fuszeres_rum, fekete_rum, arany_rum, feher_rum
};

//tequila fajtai
enum tequli_fajta {
    silver, gold, aged
};

//italok osztalya
class Ital {
    String nev; //ital neve kerül eltárolásta dinamikus memóriába
    String gyarto; //ital gyártója kerül eltárolásta dinamikus memóriába
    ital_tipus tipus; //ital tipusa

public:
    //konstruktor ami beállítja az ital nevét, gyártóját és tipusát
    Ital(ital_tipus tipus);
    Ital();
    Ital(String nev_kap, ital_tipus tipus);
    //konstruktor fájlból beolvasáshoz
    Ital(std::ifstream &file);
    //desturktor ami felszabadítja a dinamikus memóriát
    virtual ~Ital();

    //visszaadja az ital nevét
    String getNev() const;

    //visszaadja az ital gyártóját
    String getGyarto() const;

    //visszaadja az ital tipusát
    ital_tipus getTipus() const ;
    //az ital tipusát számá alakitja
    int getTipus_Szam() const;

    //visszaadja az ital tipusát szövegesen
    const char*  getTipusNev() const;
    const char* getTipusNev(ital_tipus tipus_kap) const;

    //beálitja/átálitja az ital nevét
    void setNev();
    void setNev(String kap );

    //beálitja/átálitja az ital gyártóját
    void setGyarto();
    void setGyarto(String kap);

    //beálitja/átálitja az ital tipusát
    void setTipus();
    void setTipus(ital_tipus kap);
    //kiirja az ital adatait
    virtual void kiir() const;
    //kiirja az ital adatait fájlba
    virtual void kiirF(std::ofstream& os) const;
    //valtoztatas menü
    virtual void Set();


};
// ez az osztály a szeszes italokat reprezentálja
class SzeszesItalok : public Ital {
    float alkoholTartalom;

public:
    //konstruktor ami beállítja az alkohol tartalmat
    SzeszesItalok(ital_tipus tipus);
    SzeszesItalok();
    SzeszesItalok(String nev_kap, ital_tipus tipus);
    //konstruktor fájlból beolvasáshoz
    SzeszesItalok(std::ifstream &file);

    //viszaadja az alkohol tartalmat
    float getAlkoholTartalom() const;

    //átálitja az alkohol fokot
    void setAlkoholTartalom();
    void setAlkoholTartalom(float kap);

    //ki írja az itall alkohol tartalmat
    virtual void kiir() const;
    //kiirja az ital adatait fájlba
    virtual void kiirF(std::ofstream& os) const;
    //valtoztatas menü
    virtual void Set();
};

//Bor osztály
class Bor : public SzeszesItalok {
    String *fajta; //bor fajtái tartalmatát
    size_t fajta_db;  //bor fajtáinak száma
    int evjarat;  //bor éjrára
    szinek_bor szin; //bor szine

public:
    //bor konstruktor
    Bor(ital_tipus tipus);
    Bor();
    Bor(String nev_kap, ital_tipus tipus);
    //konstruktor fájlból beolvasáshoz
    Bor(std::ifstream &file);

    //bor destruktor
    ~Bor();

    //visza adja az éjráratot
    int getEvjarat() const;

    //bor szine visza adása
    szinek_bor getSzin() const;
    //a bor szinét számá alakitja
    int getSzin_Szam() const;

    //bor szine nevének visza adása
    const char* getSzinNev()const;

    //éjrárat beálitása
    void setEvjarat();
    void setEvjarat(int kap);
    //bor szine átalitása
    void setSzin();
    void setSzin(szinek_bor kap);
    //a kapot számát sziné alakitja
    void setSzin(int kap);
    //fajta db beálitása
    void setFajta_db(size_t kap);

    void setFajta_string(String *kap);
    //fajta hozzá adása
    void addFajta();

    //fajta kiirása
    void fajtakiir() const;

    //fajta törlése
    void removeFajta();

    //fajata index alapján visza adása
    String getFajtaindex(size_t index) const;

    //fajta db visza adása
    size_t getFajta_db() const;


    //borok adatai kiirása
    void kiir() const;
    //kiirja az ital adatait fájlba
    void kiirF(std::ofstream& os) const;
    //valtoztatas menü
    void Set();
};

//Wiskey osztály
class Wiskey : public SzeszesItalok {
    String jeleg; //wiskey tipusa pl: single malt, blended
    unsigned int erleses; //wiskey erleses éve

public:
    //wiskey konstruktor
    Wiskey(ital_tipus ital_tipus);
    Wiskey();
    Wiskey(String nev_kap, ital_tipus tipus);
    //konstruktor fájlból beolvasáshoz
    Wiskey(std::ifstream &file);
    //destruktor
    ~Wiskey();

    //jeleg visza adása
    String getJeleg_wiskey() const;

    //erleses visza adása
    unsigned int getErleses() const;

    //jeleg beálitása
    void setJeleg_wiskey();
    void setJeleg_wiskey(char * kap);

    //ereleses beálitása
    void setErleses();
    void setErleses(unsigned int kap);
    //wiksey adatainak kiirása
    void kiir() const;

    //kiirja az ital adatait fájlba
    void kiirF(std::ofstream& os) const;

    //valtoztatas menü
    void Set();
};

// Gin osztály
class Gin : public SzeszesItalok {
    gin_szin szin;//gin szine
    String iz; //gin iz ha nem borokás

public:
    //gin konstruktor
    Gin(ital_tipus ital_tipus);
    Gin();
    Gin(String nev_kap, ital_tipus tipus);
    //konstruktor fájlból beolvasáshoz
    Gin(std::ifstream &file);
    //gin szin visza adása
    gin_szin getSzin() const;
    //a Gin szinét számá alakitja
    int getGinSzin() const;
    //gin szine visza adása szöbegekben
    const char* getSzinNev()const;
    //gin szin beálitása
    void setSzin();
    void setSzin(gin_szin kap);
    //a kapot számát sziné alakitja
    void setSzin(int kap);
    //gin iz visza adása
    String getIz() const;

    // gin iz beálitása
    void setIz();
    void setIz(String kap);

    //gin adatok kiirása
    void kiir() const;

    //kiirja az ital adatait fájlba
    void kiirF(std::ofstream& os) const;
    //valtoztatas menü
    void Set();
    //gin destruktor
    ~Gin();
};
//Rum osztály
class Rum : public SzeszesItalok {
    rum_fajta fajta; //rum fajta

public:
    //rum konstruktor
    Rum(ital_tipus tipus);
    Rum();
    Rum(String nev_kap, ital_tipus tipus);
    //konstruktor fájlból beolvasáshoz
    Rum(std::ifstream &file);
    //rum fajta visza adása
    rum_fajta getFajta() const;
    //a rum tipusát számá alakitja
    int getFajta_Szam() const;
    //rum fajta nevének visza adása
    const char* getFajtaNev() const;
    //rum fajta beálitása
    void setFajta();
    void setFajta(rum_fajta kap);
    //a kapot számát fajta alakitja
    void setFajta(int kap);
    //rum adatainak kiirása
    void kiir() const;
    //kiirja az ital adatait fájlba
    void kiirF(std::ofstream& os) const;
    //valtoztatas menü
    void Set();
};
//Tequila osztály
class Tequila : public SzeszesItalok {
    tequli_fajta fajta; //tequila fajta

public:
    //Tequila konstruktor
    Tequila(ital_tipus ital_tipus);
    Tequila();
    Tequila(String nev_kap, ital_tipus tipus);
    //konstruktor fájlból beolvasáshoz
    Tequila(std::ifstream &file);
    //Tequila fajta visza adása
    tequli_fajta getFajta() const;
    //a tequila tipusát számá alakitja
    int getFajta_Szam() const;
    //Tequila fajta nevének visza adása
    const char* getFajtaNev() const;
    //Tequila fajta beálitása
    void setFajta();
    void setFajta(tequli_fajta kap);
    //a kapot számát fajta alakitja
    void setFajta(int kap);
    //Tequila adatainak kiirása
    void kiir() const;

    //kiirja az ital adatait fájlba
    void kiirF(std::ofstream& os) const;

    //valtoztatas menü
    void Set();
};
//Sor osztály
class Sor : public SzeszesItalok {
    String tipus_sor; //sor tipusa stringként

public:
    //Sor konstruktor
    Sor(ital_tipus tipuss);
    Sor();
    Sor(String nev_kap, ital_tipus tipus);
    //konstruktor fájlból beolvasáshoz
    Sor(std::ifstream &file);
    //Sor jeleg visza adása
    String getTipus_sor() const;

    //Sor jeleg beálitása
    void setTipus_sor();
    void setTipus_sor(String kap);

    //Sor adatainak kiirása
    void kiir() const;

    //kiirja az ital adatait fájlba
    void kiirF(std::ofstream& os) const;

    //sor destruktor
    ~Sor();

    //valtoztatas menü
    void Set();
};
//gyumolcsle osztály
class Gyumolcsle : public Ital {
    unsigned int gyumolcsszazalek; //gyumolcsszazalek

public:
    //konstruktor
    Gyumolcsle(ital_tipus ital_tipus);
    Gyumolcsle();
    Gyumolcsle(String nev_kap, ital_tipus tipus);
    //konstruktor fájlból beolvasáshoz
    Gyumolcsle(std::ifstream &file);
    //visza adja a gyumolcsszazalekot
    unsigned int getGyumolcsszazalek() const;

    //gyumolcsszazalek beálitása
    void setGyumolcsszazalek();
    void setGyumolcsszazalek(unsigned int kap);

    //kiirja a gyumolcsle adatait
    void kiir() const;

    //kiirja az ital adatait fájlba
    void kiirF(std::ofstream& os) const;

    //valtoztatas menü
    void Set();
};

//alapnyagok osztálya;
class Italok {
    Ital** ListaItalok; //italok listája dinamikus memóriában
    size_t db;// italok száma
    Ital* italok_bevitel(); //private függvény ami beolvas egy italt
public:
    Italok(); //konstruktor
    ~Italok(); //destruktor
    Italok(const Italok &italok); //másoló konstruktor
    Italok &operator=(const Italok &italok); //másoló értékadás
    void addItal(); //ital hozzá adása
    void addItal(Ital* kap); //ital hozzá adása
    void addItal(String nev, ital_tipus tipus); //ital hozzá adása
    void removeItal(Koktlok &k); //ital törlése
    void removeItal(); //ital törlése
    void kiir_index(); //italok kiirása index kell
    void kiirF() const; //italok kiirása fájlba
    void olvasF(); //italok beolvasása fájlból
    size_t getdb() const; //italok számának kiirása
    Ital &getItal(size_t index) const; //ital vissza adása index alapján
    Ital *getItalCsilag(size_t index) const; //ital vissza adása index alapján
    void setItalok(Koktlok &kap); //ital beálitása
};
//os stream operatorokkal kiiratás
std::ostream& operator<<(std::ostream& os, const Ital& ital);

//bor éjrárat elenöriz;
bool evjarat_teszt(int evjarat);
//italok tipusának választása(bvitele)
ital_tipus tipus_valszto();

#endif //ITALOK_H
