//
// Created by Zoli on 2024. 05. 02..
//

#ifndef TESZTEK_H
#define TESZTEK_H

#include "Ital.h"
#include "koktle.h"
#include "memtrace.h"
#include <iostream>

//meghivja a tesz fügvényeket
void oszes_teszt();

//itall letrehozasa
void test_Ital();

//ital nevenek beallitasa
void test_Ital_setnev();

//bor tulindexeles
void test_Bor_index_hibba();

//italok hozzaadasa
void test_Italok_hozadas();
//italok torlese
void test_Italok_torles();

//koktel hozzaadasa
void test_Koktel_hozzaadas();

//koktel torlese
void test_Koktel_torles();

//koktel osszetevok hozzaadasa
void test_Koktel_osszetevok_hozzaadasa();

//koktel osszetevok torlese
void test_Koktel_osszetevok_torlese();

#endif //TESZTEK_H
