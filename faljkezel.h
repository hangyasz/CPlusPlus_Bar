//
// Created by Zoli on 2024. 04. 18..
//

#ifndef FALJKEZEL_H
#define FALJKEZEL_H

#include <fstream>
#include "koktle.h"
#include "Ital.h"

struct Faljkezel {
    //egy számot olvas be
    static int szam_olvas(std::ifstream &file);
    //egy unsigned számot olvas be
    static unsigned int uszam_olvas(std::ifstream &file);
    //menyiség olvasása
    static unsigned int menyiseg_olvas(std::ifstream &file);
    //egy méretet olvas be
    static size_t size_olvas(std::ifstream &file);
    //egy float számot olvas be
    static float float_olvas(std::ifstream &file);
    //egy stringet olvas be
    static String string_olvas(std::ifstream &file);
    //adatok kiírása
    static void adatok_kiir(std::ostream &os, const Ital &ital);
};


#endif //FALJKEZEL_H
