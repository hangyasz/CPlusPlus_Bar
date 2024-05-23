//
// Created by Zoli on 2024. 04. 18..
//

#ifndef FALJKEZEL_H
#define FALJKEZEL_H

#include <fstream>
#include "koktle.h"
#include "Ital.h"


//ki írja az italt a fájba
std::ofstream& operator<<(std::ofstream& os,const Ital &ital);
//ki írja a koktelt a fájba
std::ofstream& operator<<(std::ofstream& os,const Koktle &koktel);
//egy számot olvas be
int szam_olvas(std::ifstream &file);
//egy unsigned számot olvas be
unsigned int uszam_olvas(std::ifstream &file);
//egy méretet olvas be
size_t size_olvas(std::ifstream &file);
//egy float számot olvas be
float float_olvas(std::ifstream &file);




#endif //FALJKEZEL_H
