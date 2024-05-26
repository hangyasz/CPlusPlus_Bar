//
// Created by Zoli on 2024. 04. 13..
//

#ifndef KOKTLE_H
#define KOKTLE_H


#include  "Ital.h"
#include <fstream>

//koktelok osztalya
class Koktle {
    String nev; //koktel neve
	size_t alapanyag_db; //alapanyagok száma
    Ital** alapanyagok; //alapanyagok tömbje
    unsigned int *menyiseg; //alapanyagok mennyisége menyi kell belőle
public:
    //konstruktor ami beállítja a koktel
    Koktle(Italok &italok, std::ostream &os, std::istream &is);
    // ezt használom a fajbol beolvasnal
    Koktle(String nev_kap, size_t alapanyag_db_kap, Ital** alapanyagok_kap, unsigned int *menyiseg_kap);
    //kiirja a koktelokat
    void kiir(std::ostream &os) const;
    //seter a mennyiseg beallitasahoz
    void setMennyiseg(unsigned int *kap);
    //seter az alapanyagok beallitasahoz
    void setAlapanyagok(Ital** kap);
    //alapanyag számának beállítása
    void setAlapanyagDb(size_t db);
    //alapanyagok bekerese
    void alapanyagok_beker(Italok &italok, std::ostream &os, std::istream &is);
    //alapanayg hozzá adása
    void addAlapanyag(Italok &italok, std::ostream &os, std::istream &is);
    //alapanyag torlese
    void removeAlapanyag(std::ostream &os, std::istream &is);
    void removeAlapanyag(Ital *ital);
    void removeAlapanyag(); //csak a tombb egy elemü
    // koktel kiirasa fajlba
    void kiirF(std::ofstream& os) const;
    //koktel tartalmaz e adott italt és viszaadja az indexet
    size_t tartalmaz_e(Ital* kap) const;
    //koktel tartalmaz e adott alapanyagot
    bool tartalmaz_e(size_t tipus) const;
    //koktel nevenek bekerese
    void Nev_bevitel(std::ostream &os, std::istream &is);
    //koktel nevenek beallitasa
    void setNev(String kap);
    //visszaadja a koktel nevét
    String getNev() const;
    //koktel belaites mennü
    void modosit(Italok &italok, std::ostream &os, std::istream &is);
    //destruktor ami felszabadítja a dinamikus memóriát
    ~Koktle();
    //egy kiválasztott alapanyag adatai kiirasa
    void alapanyagok_adatok(std::ostream &os, std::istream &is) const;
};

//ez kezeli a koktelokat egy osztalyban
class Koktlok {
    Koktle** koktelok; //koktelok tombje
    size_t koktel_db; //koktelok szama
public:
    //konstruktor ami beállítja a koktelokat
    Koktlok();
    //visszaadja a koktelok számát
    size_t getKoktelDb() const;
    //visszaadja a megindexelt koktelt
    Koktle &getKoktel(size_t index) const;
    //koktel hozzá adása
    void addKoktel(Koktle* kap);
    void addKoktel(Italok &italok, std::ostream &os, std::istream &is);
    //koktel törlése
    void removeKoktel(std::ostream &os, std::istream &is);
    void removeKoktel(size_t index);
    void removeKoktel(); //csak ha a tombb egy elemü
    //koktelok kiirása index kell
    void kiir_index(std::ostream& os) const;
    //koktelok kiirása fájlba
    void kiirF() const;
    //koktelok beolvasása fájlból
    void olvasF(Italok &italok, std::ostream &os, std::istream &is);
    //viszaadja az ittalt ha létezik külöben felveszük
    Ital* ital_letezik_e(Italok &italok, String nev, size_t tipus, std::ostream &os, std::istream &is) const;
    //koktelok beolvasása
    void modosit(Italok &italok, std::ostream &os, std::istream &is);
    //veletlen szerü köktel ajánlás
    void veltel_ajanlas(std::ostream &os, std::istream &is) const;
    //adott alapanyagot tartalmazó koktelok kiirása
    void lista_alapanyagok_szerint(std::ostream &os, std::istream &is) const;
    //destruktor ami felszabadítja a dinamikus memóriát
    ~Koktlok();
    //alapanyagot törlünk az italokboll
    bool removeAlapanyag_Italok(size_t index,Ital *alpanyg, std::ostream &os, std::istream &is);
};
//ki írja a koktelt a fájba
std::ofstream& operator<<(std::ofstream& os,const Koktle &koktel);


#endif //KOKTLE_H
