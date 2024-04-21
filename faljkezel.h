//
// Created by Zoli on 2024. 04. 18..
//

#ifndef FALJKEZEL_H
#define FALJKEZEL_H

#include <fstream>
#include "koktle.h"
#include "Ital.h"


void ital_kiir(const Ital &ital);


int getTipusszam(ital_tipus tipus);
int getBorSzin(szinek_bor szin);
int getGinSzin(gin_szin szin);
int getRumtipus(rum_fajta fajta);
int getTequilaTipus(tequli_fajta fajta);
std::ofstream& operator<<(std::ofstream& os,const Ital &ital);
std::ofstream& operator<<(std::ofstream& os,const SzeszesItalok &ital);
std::ofstream& operator<<(std::ofstream& os,const Bor &ital);
std::ofstream& operator<<(std::ofstream& os,const Wiskey &ital);
std::ofstream& operator<<(std::ofstream& os,const Gin &ital);
std::ofstream& operator<<(std::ofstream& os,const Rum &ital);
std::ofstream& operator<<(std::ofstream& os,const Tequila &ital);
std::ofstream& operator<<(std::ofstream& os,const Sor &ital);
std::ofstream& operator<<(std::ofstream& os,const Gyumolcsle &ital);




#endif //FALJKEZEL_H
