//
// Created by Zoli on 2024. 04. 12..
//

#ifndef ITALOK_H
#define ITALOK_H


#include <iostream>
#include <cstring>
#include "string_kezez.h"


//italok tipusai
enum ital_tipus {
    alkohols, alkohol_mentes, bor, whiskey, gin, rum, tequila, sor, gyumolcsle
};

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
    char* nev; //ital neve kerül eltárolásta dinamikus memóriába
    char* gyarto; //ital gyártója kerül eltárolásta dinamikus memóriába
    ital_tipus tipus; //ital tipusa

public:
    //konstruktor ami beállítja az ital nevét, gyártóját és tipusát
    Ital(ital_tipus tipus);

    //desturktor ami felszabadítja a dinamikus memóriát
    virtual ~Ital();

    //visszaadja az ital nevét
    char *getNev() const;

    //visszaadja az ital gyártóját
    char *getGyarto() const;

    //visszaadja az ital tipusát
    ital_tipus getTipus() const ;

    //visszaadja az ital tipusát szövegesen
    const char* getTipusNev(ital_tipus tipus) const;

    //beálitja/átálitja az ital nevét
    void setNev();
    void setNev(char* kap );

    //beálitja/átálitja az ital gyártóját
    void setGyarto();
    void setGyarto(char* kap);

    //beálitja/átálitja az ital tipusát
    void setTipus();
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
    char **fajta; //bor fajtái tartalmatát
    size_t fajta_db;  //bor fajtáinak száma
    unsigned int evjarat;  //bor éjrára
    szinek_bor szin; //bor szine

public:
    //bor konstruktor
    Bor(ital_tipus tipus);

    //bor destruktor
    ~Bor();

    //visza adja az éjráratot
    unsigned int getEvjarat() const;

    //bor szine visza adása
    szinek_bor getSzin() const;

    //bor szine nevének visza adása
    const char* getSzinNev(szinek_bor szin)const;

    //éjrárat beálitása
    void setEvjarat();
    void setEvjarat(unsigned int kap);
    //bor szine átalitása
    void setSzin();
    void setSzin(szinek_bor kap);
    //fajta db beálitása
    void setFajta_db(size_t kap);

    void setFajta_string(char **kap);
    //fajta hozzá adása
    void addFajta();

    //fajta kiirása
    void fajtakiir() const;

    //fajta törlése
    void removeFajta();

    //fajata index alapján visza adása
    char *getFajtaindex(size_t index) const;

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
    char *tipus; //wiskey tipusa pl: single malt, blended
    unsigned int erleses; //wiskey erleses éve

public:
    //wiskey konstruktor
    Wiskey(ital_tipus ital_tipus);

    //destruktor
    ~Wiskey();

    //tipus visza adása
    char *getTipus_wiskey() const;

    //erleses visza adása
    unsigned int getErleses() const;

    //tipus beálitása
    void setTipus_wiskey();
    void setTipus_wiskey(char * kap);

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
    char *iz; //gin iz ha nem borokás

public:
    //gin konstruktor
    Gin(ital_tipus ital_tipus);

    //gin szin visza adása
    gin_szin getSzin() const;

    //gin szine visza adása szöbegekben
    const char* getSzinNev(gin_szin szin)const;

    //gin szin beálitása
    void setSzin();
    void setSzin(gin_szin kap);

    //gin iz visza adása
    const char *getIz() const;

    // gin iz beálitása
    void setIz();
    void setIz(char* kap);

    //gin adatok kiirása
    void kiir() const;

    //kiirja az ital adatait fájlba
    void kiirF(std::ofstream& os) const;
    //valtoztatas menü
    void Set();
};
//Rum osztály
class Rum : public SzeszesItalok {
    rum_fajta fajta; //rum fajta

public:
    //rum konstruktor
    Rum(ital_tipus ital_tipus);

    //rum fajta visza adása
    rum_fajta getFajta() const;
    //rum fajta beálitása
    void setFajta();
    void setFajta(rum_fajta kap);

    //rum fajta nevének visza adása
    const char* getFajtaNev(rum_fajta fajta) const;

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

    //Tequila fajta visza adása
    tequli_fajta getFajta() const;

    //Tequila fajta beálitása
    void setFajta();
    void setFajta(tequli_fajta kap);

    //Tequila fajta nevének visza adása
    const char* getFajtaNev(tequli_fajta fajta) const;

    //Tequila adatainak kiirása
    void kiir() const;

    //kiirja az ital adatait fájlba
    void kiirF(std::ofstream& os) const;

    //valtoztatas menü
    void Set();
};
//Sor osztály
class Sor : public SzeszesItalok {
    char *tipus_sor; //sor tipusa stringként

public:
    //Sor konstruktor
    Sor(ital_tipus tipuss);

    //Sor tipus visza adása
    char *getTipus_sor() const;

    //Sor tipus beálitása
    void setTipus_sor();
    void setTipus_sor(char *kap);

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
    void removeItal(); //ital törlése
    void kiir_index(); //italok kiirása index kell
    size_t getdb() const; //italok számának kiirása
    Ital &getItal(size_t index) const; //ital vissza adása index alapján
    void setItalok(); //ital beálitása men
};
//os stream operatorokkal kiiratás
std::ostream& operator<<(std::ostream& os, const Ital& ital);
/*
std::ostream& operator<<(std::ostream& os, const SzeszesItalok& ital);
std::ostream& operator<<(std::ostream& os, const Bor& ital);
std::ostream& operator<<(std::ostream& os, const Wiskey& ital);
std::ostream& operator<<(std::ostream& os, const Gin& ital);
std::ostream& operator<<(std::ostream& os, const Rum& ital);
std::ostream& operator<<(std::ostream& os, const Tequila& ital);
std::ostream& operator<<(std::ostream& os, const Sor& ital);
std::ostream& operator<<(std::ostream& os, const Gyumolcsle& ital);
*/

#endif //ITALOK_H
