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
    // koktel kiirasa fajlba
    void kiirF(std::ofstream& os) const;
    //ittal tartalmazó koktel neve
    bool tartalmaz_e(Ital* kap) const;
    ~Koktle(); //destruktor ami felszabadítja a dinamikus memóriát
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
    ~Koktlok();
};


std::ofstream& operator<<(std::ofstream& os,const Koktle &koktel);



#endif //KOKTLE_H
