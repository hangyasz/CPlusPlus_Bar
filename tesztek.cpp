//
// Created by Zoli on 2024. 05. 02..
//

#include "tesztek.h"
#include "Ital.h"
#include "koktle.h"
#include "gtest_lite.h"
#include <iostream>
#include "memtrace.h"

//meghivja a tesz fügvényeket
void oszes_teszt() {
    test_Ital();
    test_Ital_setnev();
    test_Bor_index_hibba();
    test_Italok_hozadas();
    test_Italok_torles();
    test_Koktel_hozzaadas();
    test_Koktel_torles();
    test_Koktel_osszetevok_hozzaadasa();
    Italok* i= test_Italok_beolvasas();
    Koktlok *k=test_Koktelok_beolvasas(i);
    delete k;
    delete i;
}



//itall letrehozasa
void test_Ital(){
    Ital i;
    EXPECT_EQ(i.getNev(),nullptr) << "a nev nem nullptr";
    EXPECT_EQ(i.getGyarto(),nullptr) << "a gyarto nem nullptr";
}
//ital nevenek beallitasa
void test_Ital_setnev() {
    Ital i;
    i.setNev();
    EXPECT_STREQ("Teszt", i.getNev())<<"a nev nem egyezeik a beallitottal";
}
//bor tulindexeles
void test_Bor_index_hibba() {
    Bor b;
    b.addFajta();
    EXPECT_ANY_THROW(b.getFajtaindex(5))<<"Nem dob kivetelt";
}

//italok uj ital hozzaadasa
void test_Italok_hozadas() {
    Italok i;
    i.addItal();
    i.kiir_index();
    EXPECT_EQ(1,i.getdb())<<"Nem adja vissza a megfelelo erteket";
}

//italok ital torlese
void test_Italok_torles() {
    Italok i;
    i.addItal();
    i.removeItal();
    EXPECT_EQ(0, i.getdb())<<"Nem adja vissza a megfelelo erteket";
}

//koktel hozzaadasa
void test_Koktel_hozzaadas() {
    Italok i;
    i.addItal();
    i.addItal();
    Koktlok koktlok;
    koktlok.addKoktel(i);
    EXPECT_EQ(1, koktlok.getKoktelDb())<<"Nem adja vissza a megfelelo alapanyag szamot";
    EXPECT_STREQ("RumB",koktlok.getKoktel(0).getNev())<<"Nem adja vissza a megfeleloen a nevet";
}

//koktel torlese
void test_Koktel_torles() {
    Italok i;
    i.addItal();
    i.addItal();
    Koktlok koktlok;
    koktlok.addKoktel(i);
    koktlok.removeKoktel();
    EXPECT_EQ(0,koktlok.getKoktelDb())<<"nem csokent a koktelok darbszama";
}

//koktel osszetevok hozzaadasa
void test_Koktel_osszetevok_hozzaadasa() {
    Italok i;
    i.addItal();
    i.addItal();
    Koktlok koktlok;
    koktlok.addKoktel(i);
    Koktle *koktle= koktlok.getKoktel_csilag(0);
    koktle->addAlapanyag(i);
    EXPECT_EQ(true, koktle->tartalmaz_e(i.getItalCsilag(1)))<<"nem sikerult a hozadas";
}

//koktel osszetevok torlese
void test_Koktel_osszetevok_torlese() {
    Italok i;
    i.addItal();
    i.addItal();
    Koktlok koktlok;
    koktlok.addKoktel(i);
    Koktle *koktle= koktlok.getKoktel_csilag(0);
    koktle->removeAlapanyag();
    EXPECT_EQ(false, koktle->tartalmaz_e(i.getItalCsilag(1)))<<"nem sikerult a torles";
}


//Italok beolvasasa_filebol
Italok* test_Italok_beolvasas() {
    Italok *i=new  Italok();
    i->olvasF();
    EXPECT_EQ(4,i->getdb())<<"Nem adja vissza a megfelelo erteket";
    EXPECT_EQ(2,i->getItal(0).getTipus_Szam())<<"Nem adja vissza a megfelelo alkohol tartalmat";
    EXPECT_STREQ("Nev",i->getItal(0).getNev())<<"Nem adja vissza a megfelelo nevet";
    EXPECT_STREQ("Gyarto",i->getItal(0).getGyarto())<<"Nem adja vissza a megfelelo gyartot";
    EXPECT_EQ(1,i->getItal(3).getTipus_Szam())<<"Nem adja vissza a megfelelo alkohol tartalmat";
    EXPECT_STREQ("Bor_zolk",i->getItal(3).getNev())<<"Nem adja vissza a megfelelo nevet";
    EXPECT_STREQ("en",i->getItal(3).getGyarto())<<"Nem adja vissza a megfelelo gyartot";
    return  i;
}

Koktlok *test_Koktelok_beolvasas(Italok *i) {
    Koktlok *k=new Koktlok();
    k->olvasF(*i);
    EXPECT_EQ(3,k->getKoktelDb())<<"Nem adja vissza a megfelelo erteket";
    EXPECT_STREQ("Kedvenc",k->getKoktel(0).getNev())<<"Nem adja vissza a megfelelo nevet";
    EXPECT_STREQ("Test_1",k->getKoktel(1).getNev())<<"Nem adja vissza a megfelelo nevet";
    EXPECT_STREQ("Test_2",k->getKoktel(2).getNev())<<"Nem adja vissza a megfelelo nevet";
    EXPECT_EQ(2,i->getItal(4).getTipus_Szam())<<"Nem adja vissza a megfelelo alkohol tartalmat";
    Italok i2;
    i2.olvasF();
    EXPECT_EQ(5,i->getdb())<<"Nem adja vissza a megfelelo erteket";
    EXPECT_STREQ("hibaa",i->getItal(4).getNev())<<"Nem adja vissza a megfelelo nevet";
    EXPECT_STREQ("Iker",i->getItal(4).getGyarto())<<"Nem adja vissza a megfelelo gyartot";
    return k;
}



