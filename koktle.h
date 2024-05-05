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
    Koktle(Italok &italok);
    // Koktle(Italok &italok,char const *nev, size_t alapanyag_db, Ital** alapanyagok, unsigned int *menyiseg);// ezt használom a fajbol beolvasnal
    Koktle(Italok &italok,char *nev, size_t alapanyag_db, Ital** alapanyagok, unsigned int *menyiseg);
    //kiirja a koktelokat
    void kiir() const;
    //alapanayg hozzá adása
    void addAlapanyag(Italok &italok);
    //alapanyag torlese
    void removeAlapanyag();
    // koktel kiirasa fajlba
    void kiirF(std::ofstream& os) const;
    //koktel tartalmaz e adott italt
    bool tartalmaz_e(const Ital* const kap) const;
    //koktel tartalmaz e adott alapanyagot
    bool tartalmaz_e(const ital_tipus tipus) const;
    //koktel atnevezese
    void setNev();
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
    Koktle& getKoktel(size_t index) const;
    //kiirja a koktelokat
    void kiir() const;
    //koktel hozzá adása
    void addKoktel(Italok &italok, Koktle* kap);
    void addKoktel(Italok &italok);
    //koktel törlése
    void removeKoktel();
    //koktelok kiirása index kell
    void kiir_index() const;
    //koktelok kiirása fájlba
    void kiirF() const;
    //koktelok beolvasása fájlból
    void olvasF(Italok &italok);
    //koktelok beolvasása
    void Set(Italok &italok);
    //veletlen szerü köktel ajánlás
    void veltel_ajanlas();
    //adott alapanyagot tartalmazó koktelok kiirása
    void lista_alapanyagok_szerint() const;
    //destruktor ami felszabadítja a dinamikus memóriát
    ~Koktlok();
};


std::ofstream& operator<<(std::ofstream& os,const Koktle &koktel);



#endif //KOKTLE_H
