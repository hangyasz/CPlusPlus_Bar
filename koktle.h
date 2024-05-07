//
// Created by Zoli on 2024. 04. 13..
//

#ifndef KOKTLE_H
#define KOKTLE_H


#include  "Ital.h"
#include "faljkezel.h"
#include <fstream>

//koktelok osztalya
class Koktle {
    char *nev; //koktel neve
	size_t alapanyag_db; //alapanyagok száma
    Ital** alapanyagok; //alapanyagok tömbje
    unsigned int *menyiseg; //alapanyagok mennyisége menyi kell belőle
public:
    //konstruktor ami beállítja a koktel
    Koktle();
    Koktle(Italok &italok);
    // ezt használom a fajbol beolvasnal
    Koktle(char *nev, size_t alapanyag_db, Ital** alapanyagok, unsigned int *menyiseg);
    //kiirja a koktelokat
    void kiir() const;
    //alapanayg hozzá adása
    void addAlapanyag(Italok &italok);
    //alapanyag torlese
    void removeAlapanyag();
    void removeAlapanyag(Ital *ital);
    // koktel kiirasa fajlba
    void kiirF(std::ofstream& os) const;
    //koktel tartalmaz e adott italt
    bool tartalmaz_e(Ital* kap) const;
    //koktel tartalmaz e adott alapanyagot
    bool tartalmaz_e(const ital_tipus tipus) const;
    //koktel atnevezese
    void setNev();
    //visszaadja a koktel nevét
    char *getNev() const;
    //koktel belaites mennü
    void Set(Italok &italok);
    //destruktor ami felszabadítja a dinamikus memóriát
    ~Koktle();
};

//ez kezeli a koktelokat egy osztalyban
class Koktlok {
    Koktle** koktelok; //koktelok tömbje
    size_t koktel_db; //koktelok száma
public:
    //konstruktor ami beállítja a koktelokat
    Koktlok();
    //visszaadja a koktelok számát
    size_t getKoktelDb() const;
    //visszaadja a koktelokat
    Koktle* getKoktel_csilag(size_t index) const;
    Koktle &getKoktel(size_t index) const;
    //kiirja a koktelokat
    void kiir() const;
    //koktel hozzá adása
    void addKoktel(Koktle* kap);
    void addKoktel(Italok &italok);
    //koktel törlése
    void removeKoktel();
    void removeKoktel(size_t index);
    //koktelok kiirása index kell
    void kiir_index() const;
    //koktelok kiirása fájlba
    void kiirF() const;
    //koktelok beolvasása fájlból
    void olvasF(Italok &italok);
    //viszaadja az ittalt ha létezik külöben felveszük
    Ital* ital_letezik_e(Italok &italok, char *nev, ital_tipus tipus);
    //koktelok beolvasása
    void Set(Italok &italok);
    //veletlen szerü köktel ajánlás
    void veltel_ajanlas();
    //adott alapanyagot tartalmazó koktelok kiirása
    void lista_alapanyagok_szerint() const;
    //destruktor ami felszabadítja a dinamikus memóriát
    ~Koktlok();
    //alapanyagot törlünk az italokboll
    bool removeAlapanyag_Italok(size_t index,Ital *alpanyg);
};


std::ofstream& operator<<(std::ofstream& os,const Koktle &koktel);



#endif //KOKTLE_H
