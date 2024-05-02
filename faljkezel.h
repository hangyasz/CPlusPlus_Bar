//
// Created by Zoli on 2024. 04. 18..
//

#ifndef FALJKEZEL_H
#define FALJKEZEL_H

#include <fstream>
#include "koktle.h"
#include "Ital.h"

//az ital tipusát számá alakitja
int getTipusszam(ital_tipus tipus);
//a bor szinét számá alakitja
int getBorSzin(szinek_bor szin);
//a bor számát sziné alakitja
szinek_bor getSzinBor(int szin);
//a Gin szinét számá alakitja
int getGinSzin(gin_szin szin);
//a Gin számát sziné alakitja
gin_szin getSzinGin(int szin);
//a rum tipusát számá alakitja
int getRumtipus(rum_fajta fajta);
//a rum számát tipusá alakitja
rum_fajta getFajtaRum(int fajta);
//a tequila tipusát számá alakitja
int getTequilaTipus(tequli_fajta fajta);
//a tequila számát tipusá alakitja
tequli_fajta getFajtaTequila(int fajta);
//ki írja az italt a fájba
std::ofstream& operator<<(std::ofstream& os,const Ital &ital);
//egy szoveg részt olvas be
char *szoveg_olvas(std::ifstream &file);
//egy számot olvas be
int szam_olvas(std::ifstream &file);
//egy unsigned számot olvas be
unsigned int uszam_olvas(std::ifstream &file);
//egy méretet olvas be
size_t size_olvas(std::ifstream &file);
//egy float számot olvas be
float float_olvas(std::ifstream &file);
//italt olavas be és tárolja el
Ital* ital_olvas(std::ifstream &file);
//szeszes italot olvas be és tárolja el
SzeszesItalok * szeszes_olvas(std::ifstream &file);
//bort olvas be és tárolja el
Bor* bor_olvas(std::ifstream &file);
//wiskeyt olvas be és tárolja el
Wiskey* wiskey_olvas(std::ifstream &file);
//gint olvas be és tárolja el
Gin* gin_olvas(std::ifstream &file);
//rumot olvas be és tárolja el
Rum* rum_olvas(std::ifstream &file);
//tequilat olvas be és tárolja el
Tequila* tequila_olvas(std::ifstream &file);
//sört olvas be és tárolja el
Sor* sor_olvas(std::ifstream &file);
//gyumolcslet olvas be és tárolja el
Gyumolcsle* gyumolcsle_olvas(std::ifstream &file);

//viszaadja az ittalt ha létezik külöben felveszük
Ital* ital_letezik_e(Italok &italok, char *nev, ital_tipus tipus);

/*
std::ofstream& operator<<(std::ofstream& os,const SzeszesItalok &ital);
std::ofstream& operator<<(std::ofstream& os,const Bor &ital);
std::ofstream& operator<<(std::ofstream& os,const Wiskey &ital);
std::ofstream& operator<<(std::ofstream& os,const Gin &ital);
std::ofstream& operator<<(std::ofstream& os,const Rum &ital);
std::ofstream& operator<<(std::ofstream& os,const Tequila &ital);
std::ofstream& operator<<(std::ofstream& os,const Sor &ital);
std::ofstream& operator<<(std::ofstream& os,const Gyumolcsle &ital);
*/


#endif //FALJKEZEL_H
