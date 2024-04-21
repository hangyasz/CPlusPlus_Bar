//
// Created by Zoli on 2024. 04. 13..
//

#ifndef KOKTLE_H
#define KOKTLE_H


#include  "Ital.h"

struct Koktle {
    char *nev;
	size_t alapanyag_db;
    Ital** alapanyagok;
    unsigned int *menyiseg;
    Koktle* kov;
    Koktle* elo;
};

//kotelok láncolat lista bovitése
//Koktle* koktle_lancol(alapnyag_lanc * lista);

//alapnyag_lanc* alapanyag_letezik(char const *nev, alapnyag_lanc* lista);


#endif //KOKTLE_H
