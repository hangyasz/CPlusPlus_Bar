//
// Created by Zoli on 2024. 04. 17..
//

#ifndef BEVITEL_KEZEZ_H
#define BEVITEL_KEZEZ_H

#include <iostream>
#include "string5.h"

struct Komunikacio{
    //bemeneti puffer torlese
   static void bufer_torles(std::istream &is);
    //szam beolvasasa
    static int int_beolvas(std::ostream &os, std::istream &is);
    //float beolvasasa
    static float float_beolvas(std::ostream &os, std::istream &is);
    //unsigned int beolvasasa
    static unsigned int unsigned_int_beolvas(std::ostream &os, std::istream &is);
    //size_t beolvasasa
    static size_t size_beolvas(std::ostream &os, std::istream &is);
    //várakozás a billentyű lenyomására
    static void vait(std::ostream &os, std::istream &is);
    //bool beolvasasa
    static bool bool_beolvas(std::ostream &os, std::istream &is);
    //tipus valaszto az italnak
    static size_t tipus_valszto(std::ostream & os,std::istream &is);
    //Szöveg beolvasása
    static String szoveg_beolvas(std::istream &is);
    //adatok kiirasa outputara
    static void adatok_kiirasa(const char* szoveg, std::ostream &os);
    //menyiseg bekerese
    static unsigned int mennyiseg_beker(std::ostream &os, std::istream &is);
    //alapanyagok db bekerese
    static size_t db_bekeres(std::ostream &os, std::istream &is);
};




#endif //BEVITEL_KEZEZ_H
