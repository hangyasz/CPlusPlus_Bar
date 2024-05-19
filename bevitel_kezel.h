//
// Created by Zoli on 2024. 04. 17..
//

#ifndef BEVITEL_KEZEZ_H
#define BEVITEL_KEZEZ_H

#include <iostream>

//bemeneti puffer torlese
void bufer_torles(std::istream &is);
//szam beolvasasa
int int_beolvas(std::ostream &os, std::istream &is);
//float beolvasasa
float float_beolvas(std::ostream &os, std::istream &is);
//unsigned int beolvasasa
unsigned int unsigned_int_beolvas(std::ostream &os, std::istream &is);
//size_t beolvasasa
size_t size_beolvas(std::ostream &os, std::istream &is);
//várakozás a billentyű lenyomására
void vait(std::ostream &os, std::istream &is);
//bool beolvasasa
bool bool_beolvas(std::ostream &os, std::istream &is);
//tipus valaszto az italnak
size_t tipus_valszto(std::ostream & os,std::istream &is);
//adatok kiirasa outputara
void adatok_kiirasa(const char* szoveg, std::ostream &os);



#endif //BEVITEL_KEZEZ_H
