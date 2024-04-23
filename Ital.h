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

    //beálitja/átálitja az ital gyártóját
    void setGyarto();

    //kiirja az ital adatait
    virtual void kiir();


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

    //ki írja az itall alkohol tartalmat
    virtual void kiir();
};

class Bor : public SzeszesItalok {
    char **fajta;
    size_t fajta_db;
    unsigned int evjarat;
    szinek_bor szin;

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

    //bor szine átalitása
    void setSzin();

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
    void kiir();
};

class Wiskey : public SzeszesItalok {
    char *tipus;
    unsigned int erleses;

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
    void setTipus();

    //ereleses beálitása
    void setErleses();

    //wiksey adatainak kiirása
    void kiir();
};


class Gin : public SzeszesItalok {
    gin_szin szin;
    char *iz;

public:
    //gin konstruktor
    Gin(ital_tipus ital_tipus);

    //gin szin visza adása
    gin_szin getSzin() const;

    //gin szine visza adása szöbegekben
    const char* getSzinNev(gin_szin szin)const;

    //gin szin beálitása
    void setSzin();

    //gin iz visza adása
    const char *getIz() const;

    // gin iz beálitása
    void setIz();

    //gin adatok kiirása
    void kiir();
};

class Rum : public SzeszesItalok {
    rum_fajta fajta;

public:
    //rum konstruktor
    Rum(ital_tipus ital_tipus);

    //rum fajta visza adása
    rum_fajta getFajta() const;
    //rum fajta beálitása
    void setFajta();

    //rum fajta nevének visza adása
    const char* getFajtaNev(rum_fajta fajta) const;

    //rum adatainak kiirása
    void kiir();
};

class Tequila : public SzeszesItalok {
    tequli_fajta fajta;

public:
    //Tequila konstruktor
    Tequila(ital_tipus ital_tipus);

    //Tequila fajta visza adása
    tequli_fajta getFajta() const;

    //Tequila fajta beálitása
    void setFajta();

    //Tequila fajta nevének visza adása
    const char* getFajtaNev(tequli_fajta fajta) const;

    //Tequila adatainak kiirása
    void kiir();
};

class Sor : public SzeszesItalok {
    char *tipus_sor;

public:
    //Sor konstruktor
    Sor(ital_tipus tipuss);

    //Sor tipus visza adása
    char *getTipus_sor() const;

    //Sor tipus beálitása
    void setTipus(char *tipus);

    //Sor adatainak kiirása
    void kiir();

    //sor destruktor
    ~Sor();
};

class Gyumolcsle : public Ital {
    unsigned int gyumolcsszazalek;

public:
    //konstruktor
    Gyumolcsle(ital_tipus ital_tipus);

    //visza adja a gyumolcsszazalekot
    unsigned int getGyumolcsszazalek() const;

    //gyumolcsszazalek beálitása
    void setGyumolcsszazalek();

    //kiirja a gyumolcsle adatait
    void kiir();
};


//alapnyagok osztálya;
class Italok {
    Ital** ListaItalok;
    size_t db;
    Ital* italok_bevitel();
public:
    Italok();
    ~Italok();
    Italok(const Italok &italok);
    Italok &operator=(const Italok &italok);
    void addItal();
    void removeItal();
    void kiir_index();
    Ital &getItal(size_t index);
    void setItal(size_t index);
};

std::ostream& operator<<(std::ostream& os, const Ital& ital);
std::ostream& operator<<(std::ostream& os, const SzeszesItalok& ital);
std::ostream& operator<<(std::ostream& os, const Bor& ital);
std::ostream& operator<<(std::ostream& os, const Wiskey& ital);
std::ostream& operator<<(std::ostream& os, const Gin& ital);
std::ostream& operator<<(std::ostream& os, const Rum& ital);
std::ostream& operator<<(std::ostream& os, const Tequila& ital);
std::ostream& operator<<(std::ostream& os, const Sor& ital);
std::ostream& operator<<(std::ostream& os, const Gyumolcsle& ital);



#endif //ITALOK_H
