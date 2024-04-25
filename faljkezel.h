//
// Created by Zoli on 2024. 04. 18..
//

#ifndef FALJKEZEL_H
#define FALJKEZEL_H

#include <fstream>
#include "koktle.h"
#include "Ital.h"

void ital_kiir(const Italok &kap);
int getTipusszam(ital_tipus tipus);
int getBorSzin(szinek_bor szin);
szinek_bor getSzinBor(int szin);
int getGinSzin(gin_szin szin);
gin_szin getSzinGin(int szin);
int getRumtipus(rum_fajta fajta);
rum_fajta getFajtaRum(int fajta);
int getTequilaTipus(tequli_fajta fajta);
tequli_fajta getFajtaTequila(int fajta);
std::ofstream& operator<<(std::ofstream& os,const Ital &ital);
//ittalok beolvasasa
void italok_beolvas(Italok &kap);
char *szoveg_olvas(std::ifstream &file);
int szam_olvas(std::ifstream &file);
unsigned int uszam_olvas(std::ifstream &file);
size_t size_olvas(std::ifstream &file);
float float_olvas(std::ifstream &file);
Ital* ital_olvas(std::ifstream &file);
SzeszesItalok * szeszes_olvas(std::ifstream &file);
Bor* bor_olvas(std::ifstream &file);
Wiskey* wiskey_olvas(std::ifstream &file);
Gin* gin_olvas(std::ifstream &file);
Rum* rum_olvas(std::ifstream &file);
Tequila* tequila_olvas(std::ifstream &file);
Sor* sor_olvas(std::ifstream &file);
Gyumolcsle* gyumolcsle_olvas(std::ifstream &file);

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
