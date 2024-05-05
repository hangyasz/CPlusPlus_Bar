//
// Created by Zoli on 2024. 05. 02..
//

#include "tesztek.h"
#include "Ital.h"
#include "koktle.h"
#include "memtrace.h"
#include "gtest_lite.h"
#include <iostream>


//itall letrehozasa
void test_Ital(){
    Ital i;
    EXPECT_EQ(i.getNev(),nullptr) << "a nev nem nullptr";
    EXPECT_EQ(i.getGyarto(),nullptr) << "a gyarto nem nullptr";
}
//ital nevenek beallitasa
void test_Ital_setnev() {
    Ital i;
    EXPECT_STREQ("Teszt", i.getNev())<<"a nev nem egyezeik a beallitottal";
}
//bor tulindexeles
void test_Bor_index_hibba() {
    Bor *b = new Bor();
    b->setFajta_db(2);
    EXPECT_ANY_THROW(b->getFajtaindex(5))<<"Nem dob kivetelt";
    delete b;

}

//italok uj ital hozzaadasa
void test_Italok_hozadas() {
    Italok k;
    k.addItal();
    EXPECT_EQ(1,k.getdb())<<"Nem adja vissza a megfelelo erteket";
}

//italok ital torlese
void test_Italok_torles() {
    Italok k;
    k.addItal();
    k.removeItal();
    EXPECT_EQ(0, k.getdb())<<"Nem adja vissza a megfelelo erteket";
}

//koktel hozzaadasa
void test_Koktel_hozzaadas() {
}

//koktel torlese
void test_Koktel_torles() {
}

//koktel osszetevok hozzaadasa
void test_Koktel_osszetevok_hozzaadasa() {
}

//koktel osszetevok torlese
void test_Koktel_osszetevok_torlese() {
}


