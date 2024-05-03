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
    Ital *i = new Ital();
    EXPECT_STREQ(i->getNev(), nullptr)<<"a nev nem nullptr";
    delete i;
}

void test_Ital_setnev() {
    Ital *i = new Ital();
    i->setNev("Teszt");
    EXPECT_STREQ(i->getNev(), "Teszt")<<"a nev nem egyezeik a beallitottal";
    delete i;
}

void test_Bor_index() {
    Bor *b = new Bor();
    b->setFajta_db(2);
    EXPECT_ANY_THROW(b->getFajtaindex(5))<<"Nem dob kivetelt";
    delete b;

}

void test_Italok_hozadas() {
    Italok k;
    k.addItal();
    EXPECT_EQ(k.getdb(), 1)<<"Nem adja vissza a megfelelo erteket";
}

void test_Italok_torles() {
    Italok k;
    k.addItal();
    k.removeItal();
    EXPECT_EQ(0, k.getdb())<<"Nem adja vissza a megfelelo erteket";
}





