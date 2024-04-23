//
// Created by Zoli on 2024. 04. 13..
//

#ifndef KOKTLE_H
#define KOKTLE_H


#include  "Ital.h"

//koktelok tipusai
struct Koktle {
    char *nev; //koktel neve
	size_t alapanyag_db; //alapanyagok száma
    Ital** alapanyagok; //alapanyagok tömbje
    unsigned int *menyiseg; //alapanyagok mennyisége menyi kell belőle
};

//kotelok láncolat lista bovitése
//Koktle* koktle_lancol(alapnyag_lanc * lista);

//alapnyag_lanc* alapanyag_letezik(char const *nev, alapnyag_lanc* lista);


#endif //KOKTLE_H
