//
// Created by Zoli on 2024. 04. 12..
//

#ifndef ITALOK_H
#define ITALOK_H


#include <iostream>
#include <cstring>
#include "bevitel_kezel.h"
#include "string5.h"

struct TipusInfo {
    const char italkok[9][20] = {"Bor", "Whiskey", "Gin", "Rum", "Tequila", "Sor", "Gyumolcsle", "Alkohols", "Alkohol mentes"};
    const size_t meret=9;
};

//elöre deklarációk
class Koktlok;

const char* get_tipus_nev_str(size_t tipus);
size_t get_tipusok_szam();

//italok osztalya
class Ital {
    String nev; //ital neve kerül eltárolásta dinamikus memóriába
    String gyarto; //ital gyártója kerül eltárolásta dinamikus memóriába
    size_t tipus; //ital tipusa 1 bor 2 wiskey 3 gin 4 rum 5 tequila 6 sor 7 gyumolcsle 8 alkoholos italok 9 alkoholmentes italok

public:
    //konstruktor ami beállítja az ital nevét, gyártóját és tipusát
    Ital(size_t tipus,std::ostream &os,std::istream &is);
    Ital(String nev_kap, size_t tipus,std::ostream &os,std::istream &is);
    //konstruktor fájlból beolvasáshoz
    Ital(std::ifstream &file,size_t tipus,std::ostream &os, std::istream &is);
    //desturktor ami felszabadítja a dinamikus memóriát
    virtual ~Ital();
    //visszaadja az ital nevét
    String getNev() const;

    //visszaadja az ital gyártóját
    String getGyarto() const;

    //visszaadja az ital tipusát
    size_t getTipus() const ;
    //visszaadja az ital tipusát szövegesen
    const char*  getTipusNev() const;
    //beálitja/átálitja az ital nevét
    void setNev(std::ostream &os,std::istream &is);

    //beálitja/átálitja az ital gyártóját
    void setGyarto(std::ostream &os,std::istream &is);

    //beálitja/átálitja az ital tipusát
    void setTipus(size_t kap);
    //kiirja az ital adatait
    virtual void kiir(std::ostream &os) const;
    //kiirja az ital adatait fájlba
    virtual void kiirF(std::ofstream& os) const;
    //valtoztatas menü
    virtual void Set(std::ostream &os, std::istream &is);


};
// ez az osztály a szeszes italokat reprezentálja
class SzeszesItalok : public Ital {
    float alkoholTartalom;

public:
    //konstruktor ami beállítja az alkohol tartalmat
    SzeszesItalok(size_t tipus,std::ostream &os, std::istream &is);
    SzeszesItalok(String nev_kap, size_t tipus, std::ostream &os, std::istream &is);
    //konstruktor fájlból beolvasáshoz
    SzeszesItalok(std::ifstream &file,size_t tipus,std::ostream &os, std::istream &is);

    virtual void intput(std::ostream &os, std::istream &is);

    //viszaadja az alkohol tartalmat
    float getAlkoholTartalom() const;

    //átálitja az alkohol fokot
    void setAlkoholTartalom(std::ostream &os, std::istream &is);
    void setAlkoholTartalom(float kap);

    //ki írja az itall alkohol tartalmat
    virtual void kiir(std::ostream &os) const;
    //kiirja az ital adatait fájlba
    virtual void kiirF(std::ofstream& os) const;
    //valtoztatas menü
    virtual void Set(std::ostream & os, std::istream& is);
};

//Bor osztály
class Bor : public SzeszesItalok {
    String *fajta; //bor fajtái tartalmatát
    size_t fajta_db;  //bor fajtáinak száma
    int evjarat;  //bor éjrára
    size_t szin; //bor szine 1 voros 2 rozé 3 fehér

public:
    //bor konstruktor
    Bor(size_t tipus,std::ostream &os, std::istream &is);
    Bor(String nev_kap, size_t tipus, std::ostream &os, std::istream &is);
    //konstruktor fájlból beolvasáshoz
    Bor(std::ifstream &file, size_t tipus, std::ostream &os, std::istream &is);

    //bor destruktor
    ~Bor();

    //bekerjek az adatokat a bor letrehozásához
    void intput(std::ostream &os, std::istream &is);

    //visza adja az éjráratot
    int getEvjarat() const;

    //bor szine visza adása
    size_t getSzin() const;
    //bor szine nevének visza adása
    const char* getSzinNev()const;

    //éjrárat beálitása
    void setEvjarat(std::ostream &os, std::istream &is );
    void setEvjarat(int kap);
    //bor szine átalitása
    void setSzin(std::ostream &os, std::istream &is);
    void setSzin(size_t kap);
    //fajta hozzá adása
    void addFajta(std::ostream &os, std::istream &is);

    //fajtak kirasa indexelve
    void fajtakiir_index( std::ostream &os) const;

    //fajta törlése
    void removeFajta(std::ostream &os, std::istream &is);
    //fajta db visza adása
    size_t getFajta_db() const;
    //borok adatai kiirása
    void kiir(std::ostream &os) const;
    //kiirja az ital adatait fájlba
    void kiirF(std::ofstream& os) const;
    //valtoztatas menü
    void Set(std::ostream & os, std::istream& is);
};


//Wiskey osztály
class Wiskey : public SzeszesItalok {
    String jeleg; //wiskey tipusa pl: single malt, blended
    unsigned int erleses; //wiskey erleses éve

public:
    //wiskey konstruktor
    Wiskey(size_t ital_tipus,std::ostream & os, std::istream &is);
    Wiskey(String nev_kap, size_t tipus, std::ostream &os, std::istream &is);
    //konstruktor fájlból beolvasáshoz
    Wiskey(std::ifstream &file,size_t tipus,std::ostream &os, std::istream &is);
    //destruktor
    ~Wiskey();

    //adatok bekese
    void intput(std::ostream &os, std::istream &is);
    //jeleg visza adása
    String getJeleg_wiskey() const;

    //erleses visza adása
    unsigned int getErleses() const;
    //jeleg beálitása
    void setJeleg_wiskey(std::ostream & os, std::istream &is);

    //ereleses beálitása
    void setErleses(std::ostream &os, std::istream &is);
    void setErleses(unsigned int kap);
    //wiksey adatainak kiirása
    void kiir(std::ostream &os) const;

    //kiirja az ital adatait fájlba
    void kiirF(std::ofstream& os) const;

    //valtoztatas menü
    void Set(std::ostream &os,std::istream &is);
};

// Gin osztály
class Gin : public SzeszesItalok {
    String szin;//gin szine
    String iz; //gin iz ha nem borokás

public:
    //gin konstruktor
    Gin(size_t ital_tipus, std::ostream &os,std::istream &is);
    Gin(String nev_kap, size_t tipus,std::ostream &os,std::istream &is);
    //konstruktor fájlból beolvasáshoz
    Gin(std::ifstream &file,size_t tipus,std::ostream &os, std::istream &is);
    //adatok bekese
    void intput(std::ostream &os, std::istream &is);
    //gin szin visza adása
    String getSzin() const;
    //gin szin beálitása
    void setSzin(std::ostream &os,std::istream &is);
    //a kapot számát sziné alakitja
    void setSzin(int kap);
    //gin iz visza adása
    String getIz() const;

    // gin iz beálitása
    void setIz(std::ostream &os,std::istream &is);

    //gin adatok kiirása
    void kiir(std::ostream &os) const;

    //kiirja az ital adatait fájlba
    void kiirF(std::ofstream& os) const;
    //valtoztatas menü
    void Set(std::ostream &os,std::istream &is);
    //gin destruktor
    ~Gin();
};


//Fajtas italaok olyan alkoholos italok amiknek csak fajtaja van pl: rum, tequila, sor
class Fajta : public SzeszesItalok {

    String fajta; //rum fajta 1 füszeres 2 fekete 3 arany 4 fehér

public:
    //Fajtak konstruktor
    Fajta(size_t tipus, std::ostream &os, std::istream &is);
    Fajta(String nev_kap, size_t tipus,std::ostream &os, std::istream &is);
    //konstruktor fájlból beolvasáshoz
    Fajta(std::ifstream &file,size_t tipus, std::ostream &os, std::istream &is);

    //adatok bekese
    void intput(std::ostream &os, std::istream &is);
    //a fajta visza adása
    String getFajta() const;
    // fajta beálitása
    void setFajta(std::ostream &os, std::istream &is);
    // adatainak kiirása
    void kiir(std::ostream &os) const;
    //kiirja az ital adatait fájlba
     void kiirF(std::ofstream& os) const;
    //valtoztatas menü
    void Set( std::ostream &os, std::istream &is);
};


//gyumolcsle osztály
class Gyumolcsle : public Ital {
    unsigned int gyumolcsszazalek; //gyumolcsszazalek

public:
    //konstruktor
    Gyumolcsle(size_t ital_tipus, std::ostream &os, std::istream &is);
    Gyumolcsle(String nev_kap, size_t tipus, std::ostream &os, std::istream &is);
    //konstruktor fájlból beolvasáshoz
    Gyumolcsle(std::ifstream &file,size_t tipus, std::ostream &os, std::istream &is);
    //adatok bekese
    void intput(std::ostream &os, std::istream &is);
    //visza adja a gyumolcsszazalekot
    unsigned int getGyumolcsszazalek() const;

    //gyumolcsszazalek beálitása
    void setGyumolcsszazalek(std::ostream &os, std::istream &is);
    void setGyumolcsszazalek(unsigned int kap);

    //kiirja a gyumolcsle adatait
    void kiir(std::ostream &os) const;

    //kiirja az ital adatait fájlba
    void kiirF(std::ofstream& os) const;

    //valtoztatas menü
    void Set(std::ostream& os, std::istream &is);
};

//alapnyagok osztálya;
class Italok {
    //italok listája dinamikus memóriában
    Ital** ListaItalok;
    // italok száma
    size_t db;
public:
    //konstruktor
    Italok();
    //destruktor
    ~Italok();
    //tartalmazza az adot nevü és tipusú italt
    bool tartaalmaz(String nev, size_t tipus) const;
    //ital hozzá adása
    void addItal(std::ostream &os, std::istream &is);
    void addItal(Ital* kap);
    void addItal(String nev, size_t tipus,std::ostream &os, std::istream &is);
    //ital törlése
    void removeItal(Koktlok &k, std::ostream & os, std::istream &is);
    //italok kiirása index kell
    void kiir_index(std::ostream &os) const;
    //italok kiirása fájlba
    void kiirF() const;
    //italok beolvasása fájlból
    void olvasF(std::ostream & os ,std::istream &is);
    //italok számának visza adása
    size_t getdb() const;
    //ital vissza adása index alapján
    Ital &getItal(size_t index) const;
    //ital beálitása
    void setItalok(Koktlok &k, std::ostream &os, std::istream &is);
};
//os stream operatorokkal kiiratás
std::ostream& operator<<(std::ostream& os, const Ital& ital);

//bor éjrárat elenöriz;
void evjarat_teszt(int evjarat);
// emberiseg enyiideje készit alkoholt
void alkohol_keszul(unsigned int ido);




#endif //ITALOK_H
