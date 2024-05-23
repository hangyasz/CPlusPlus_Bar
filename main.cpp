#include <iostream>

#include "Ital.h"
#include "bevitel_kezel.h"
#include "koktle.h"
#include "gtest_lite.h"
#include "memtrace.h"

#include <sstream>
#include <cstring>



#ifndef CPORTA
#define CPORTA
#endif

int main() {
#ifndef CPORTA
    size_t valasz;
    Italok i;
    try {
        i.olvasF(std::cout,std::cin);
    }catch (const char *hibba) {
        adatok_kiirasa(hibba,std::cout);
    }
    Koktlok k;
    try {
        k.olvasF(i,std::cout,std::cin);
    }catch (const char *hibba) {
        adatok_kiirasa(hibba, std::cout);
    }
    do {
        std::cout<<"1 - Italok kezelese\n2 - Koktelok kezeles\n3 - veleteln koktel\n 4 - koktel alapanyag szerint\n 0 - Kilepes"<<std::endl;
        std::cout<<"Mit szeretnel csinalni? ";
        valasz=size_beolvas(std::cout, std::cin);
        switch (valasz) {
            case 1:
                i.setItalok(k, std::cout, std::cin);
                break;
            case 2:
                k.Set(i, std::cout, std::cin);
                break;
            case 3:
                k.veltel_ajanlas(std::cout, std::cin);
                break;
            case 4:
                k.lista_alapanyagok_szerint(std::cout, std::cin);
                break;
            case 0:
                break;
        }
    }while (valasz!=0);
#else

    Italok *i3=new Italok;
    TEST(Italok, olvasF) {
        std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        EXPECT_NO_THROW(i3->olvasF(oss, std::cin));
        EXPECT_EQ(7,i3->getdb())<<"Nem adja vissza a megfelelo erteket";
        EXPECT_EQ(2,i3->getItal(0).getTipus())<<"Nem adja vissza a megfelelo alkohol tartalmat";
        EXPECT_STREQ("Nev",i3->getItal(0).getNev().c_str())<<"Nem adja vissza a megfelelo nevet";
        EXPECT_STREQ("Gyarto",i3->getItal(0).getGyarto().c_str())<<"Nem adja vissza a megfelelo gyartot";
        EXPECT_EQ(1,i3->getItal(3).getTipus())<<"Nem adja vissza a megfelelo alkohol tartalmat";
        EXPECT_STREQ("Bor_zolk",i3->getItal(3).getNev().c_str())<<"Nem adja vissza a megfelelo nevet";
        EXPECT_STREQ("en",i3->getItal(3).getGyarto().c_str())<<"Nem adja vissza a megfelelo gyartot";
    }ENDM;

    Koktlok *k2=new Koktlok;
    TEST(Koktlok, olvas) {
        std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        EXPECT_NO_THROW(k2->olvasF(*i3, oss, std::cin)) << "Hiba tortent az olvasas soran";
        EXPECT_EQ(11,k2->getKoktelDb())<<"Nem adja vissza a megfelelo erteket";
        EXPECT_STREQ("Kedvenc",k2->getKoktel(0).getNev().c_str())<<"Nem adja vissza a megfelelo nevet";
        EXPECT_STREQ("Test_0",k2->getKoktel(1).getNev().c_str())<<"Nem adja vissza a megfelelo nevet";
        EXPECT_STREQ("Test_1",k2->getKoktel(2).getNev().c_str())<<"Nem adja vissza a megfelelo nevet";
        EXPECT_EQ(8,i3->getItal(4).getTipus())<<"Nem adja vissza a megfelelo alkohol tartalmat";
        Italok i2;
        EXPECT_NO_THROW(i2.olvasF(oss, std::cin)) << "Hiba tortent az olvasas soran";

        EXPECT_EQ(i3->getdb(),i2.getdb())<<"Nem adja vissza a megfelelo erteket a falj es a tarolt ertek";
        EXPECT_STREQ("hiba_Wiskey",i3->getItal(7).getNev().c_str())<<"Nem adja vissza a megfelelo nevet";
        EXPECT_STREQ("key",i3->getItal(7).getGyarto().c_str())<<"Nem adja vissza a megfelelo gyartot";
        EXPECT_STREQ("hiba_bor",i3->getItal(8).getNev().c_str())<<"Nem adja vissza a megfelelo nevet";
        EXPECT_STREQ("hiba_gin",i3->getItal(9).getNev().c_str())<<"Nem adja vissza a megfelelo nevet";
        EXPECT_STREQ("hiba_rum",i3->getItal(10).getNev().c_str())<<"Nem adja vissza a megfelelo nevet";
        EXPECT_STREQ("hiba_tequila",i3->getItal(11).getNev().c_str())<<"Nem adja vissza a megfelelo nevet";
        EXPECT_STREQ("hiba_sor",i3->getItal(12).getNev().c_str())<<"Nem adja vissza a megfelelo nevet";
        EXPECT_STREQ("hiba_gyumolcsle",i3->getItal(13).getNev().c_str())<<"Nem adja vissza a megfelelo nevet";
        EXPECT_STREQ("hiba_alkohols",i3->getItal(14).getNev().c_str())<<"Nem adja vissza a megfelelo nevet";
        EXPECT_STREQ("hiba_alkohol_mentes",i3->getItal(15).getNev().c_str())<<"Nem adja vissza a megfelelo nevet";
        /*
        std::ostringstream oss;
        i3->kiir_index(oss);
        String toss=oss.str().c_str();
        std::ostringstream oss2;
        i2.kiir_index(oss2);
        String toss2=oss2.str().c_str();
        EXPECT_STREQ(toss.c_str(),toss2.c_str())<<"Nem egyezik a ket kiiras";
        //JPorta nem engedte
        */
    }ENDM;

    TEST(Italok + Koktlok, torles) {
        std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        i3->setItalok(*k2, oss, std::cin);
        k2->Set(*i3, oss, std::cin);
        EXPECT_EQ(14, i3->getdb()) << "Nem torote az alapnyagot";
        EXPECT_EQ(8, k2->getKoktelDb()) << "Nem torolte a koktelt";
    }ENDM;

    TEST(Koktle, torlles) {
        std::ostringstream oss1; //csak hogy jobban nézen ki a kimenet
        while (k2->getKoktelDb()) {
            std::istringstream iss("1");
            k2->removeKoktel(oss1, iss);
        }
        std::ostringstream oss;
        k2->removeKoktel(oss,std::cin);
        EXPECT_STREQ("Nincsen koktelok\n",oss.str().c_str())<<"Nem ures a lista";

    }ENDM;

    delete i3;
    delete k2;
    std::ofstream file;
    file.open("koktelok.txt"); //fajl megnyitása koktelok.txt
    file<<"";//toroljuk a tartalmat
    file.close();
    file.open("italok.txt"); //fajl megnyitása italok.txt
    file<<""; //toroljuk a tartalmat
    file.close();

    TEST(Italok, konstruktor) {
        Italok i;
        EXPECT_EQ(0, i.getdb()) << "Nem nulla az elemei szama";
        EXPECT_ANY_THROW(i.getItal(0))<<"Nem dobot hibat";
    } ENDM;
    TEST(Koktlok, konstruktor) {
        Koktlok k;
        EXPECT_ANY_THROW(k.getKoktel(0)) << "Hiba tortent az olvasas soran";
        EXPECT_EQ(0, k.getKoktelDb()) << "Nem nulla az elemei szama";
    }ENDM;

    Italok i;
    Koktlok k;
    TEST(Italok, addital) {
        std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        i.setItalok(k, oss, std::cin);
        EXPECT_EQ(1, i.getdb()) << "Nem egy az elemei szama";
        SzeszesItalok *test;
        EXPECT_NO_THROW(test=dynamic_cast<SzeszesItalok *>( &i.getItal(0))) << "dob kivetelt";
        EXPECT_STREQ("Teszt", test->getNev().c_str()) << "Nem egyezik a nev";
        EXPECT_STREQ("Gyarto", test->getGyarto().c_str()) << "Nem egyezik az alkohol";
        EXPECT_EQ(8, test->getTipus()) << "Nem egyezik az ar";
        EXPECT_EQ(10, test->getAlkoholTartalom()) << "Nem egyezik az alkohol";
        i.setItalok(k, oss, std::cin);
        EXPECT_EQ(9, i.getdb()) << "Nem 9 az elemei szama";
        EXPECT_EQ(1, i.getItal(8).getTipus())<<"Nem egyezik a tipus";
        EXPECT_STREQ("Bor", i.getItal(8).getNev().c_str()) << "Nem egyezik a nev";
    }ENDM;

    TEST(Ital , set) {
        std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        i.setItalok(k, oss, std::cin);
        SzeszesItalok *test;
        EXPECT_NO_THROW(test=dynamic_cast<SzeszesItalok *>( &i.getItal(0))) << "dob kivetelt";
        EXPECT_STREQ("Proba", test->getNev().c_str()) << "Nem egyezik a nev";
        EXPECT_STREQ("Valaki", test->getGyarto().c_str()) << "Nem egyezik az alkohol";
        EXPECT_EQ(8, test->getTipus()) << "Nem egyezik az ar";
        EXPECT_EQ(15, test->getAlkoholTartalom()) << "Nem egyezik az alkohol";
        Ital *test2;
        EXPECT_NO_THROW(test2 = &i.getItal(1)) << "dob kivetelt";
        EXPECT_STREQ("Miranda", test2->getNev().c_str()) << "Nem egyezik a nev";
        EXPECT_STREQ("Pepsi", test2->getGyarto().c_str()) << "Nem egyezik az alkohol";
        EXPECT_EQ(9, test2->getTipus()) << "Nem egyezik az ar";
        Gyumolcsle *test3;
        EXPECT_NO_THROW(test3=dynamic_cast<Gyumolcsle *>( &i.getItal(2))) << "dob kivetelt";
        EXPECT_STREQ("Oszi", test3->getNev().c_str()) << "Nem egyezik a nev";
        EXPECT_STREQ("Marka", test3->getGyarto().c_str()) << "Nem egyezik a marka";
        EXPECT_EQ(7, test3->getTipus()) << "Nem egyezik a tipus";
        EXPECT_EQ(1, test3->getGyumolcsszazalek()) << "Nem egyezik a gyumocs tartalom";
        Fajta *test4;
        EXPECT_NO_THROW(test4=dynamic_cast<Fajta *>( &i.getItal(3))) << "dob kivetelt";
        EXPECT_STREQ("Nem sor", test4->getFajta().c_str()) << "Nem egyezik a tipus";
        Gin *test5;
        EXPECT_NO_THROW(test5=dynamic_cast<Gin *>( &i.getItal(6))) << "dob kivetelt";
        EXPECT_STREQ("feher", test5->getSzin().c_str()) << "Nem egyezik a nev";
        EXPECT_EQ(0,test5->getIz().size()) << "Nem egyezik az a szoveg hosza";
        Wiskey *test6;
        EXPECT_NO_THROW(test6=dynamic_cast<Wiskey *>( &i.getItal(7))) << "dob kivetelt";
        EXPECT_STREQ("kukorica", test6->getJeleg_wiskey().c_str()) << "Nem egyezik a fajtaja";
        EXPECT_EQ(5, test6->getErleses()) << "Nem egyezik a erleles";
        Bor *test7;
        EXPECT_NO_THROW(test7=dynamic_cast<Bor *>( &i.getItal(8))) << "dob kivetelt";
        EXPECT_EQ(2, test7->getSzin()) << "Nem egyezik a szin";
        EXPECT_EQ(2023, test7->getEvjarat()) << "Nem egyezik az evjarat";
        EXPECT_EQ(1, test7->getFajta_db()) << "Nem egyezik a fajtaszam";
    }ENDM;

    TEST(Koktlok, add) {
        std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        k.Set(i, oss, std::cin);
        EXPECT_EQ(1, k.getKoktelDb()) << "Nem egy az elemei szama";
        Koktle *test;
        EXPECT_NO_THROW(test=&k.getKoktel(0)) << "dob kivetelt";
        EXPECT_STREQ("Uj koktel", test->getNev().c_str()) << "Nem egyezik a nev";
        EXPECT_EQ(1,test->tartalmaz_e(&i.getItal(7)))<<"Nem tartalmazza az italt";
        EXPECT_TRUE(test->tartalmaz_e(2))<<"Nem tartalmazza az italt";

    }ENDM;

    TEST( Koktle, modosit) {
        std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        k.Set(i, oss, std::cin);
        Koktle *test;
        EXPECT_NO_THROW(test=&k.getKoktel(0)) << "dob kivetelt";
        EXPECT_STREQ("Mas nev", test->getNev().c_str()) << "Nem egyezik a nev";
        EXPECT_FALSE(test->tartalmaz_e(2))<<"tartalmazza az italt";
        EXPECT_TRUE(test->tartalmaz_e(3))<<"nem tartalmazza az italt";
        EXPECT_TRUE(test->tartalmaz_e(9))<<"nem tartalmazza az italt";
    }ENDM;

    TEST(Kokte, torles) {
        std::ostringstream oss2; //csak hogy jobban nézen ki a kimenet
        k.addKoktel(i,oss2, std::cin);
        Koktle *test=&k.getKoktel(1);
        test->removeAlapanyag(&i.getItal(0));
        EXPECT_FALSE(test->tartalmaz_e(8))<<"Tartalmazza az italt";
        test->addAlapanyag(i,oss2, std::cin);
        EXPECT_TRUE(test->tartalmaz_e(8))<<"Nem tartalmazza az italt";
        test->removeAlapanyag(oss2, std::cin);
        EXPECT_FALSE(test->tartalmaz_e(8))<<"Tartalmazza az italt";
        std::ostringstream oss;
        test->removeAlapanyag(oss,std::cin);
        EXPECT_STREQ("A koktelnak nincsen alapnyagai!\n",oss.str().c_str())<<"Nem ures a lista";
        k.removeKoktel(1);
        EXPECT_ANY_THROW(k.getKoktel(1))<<"Nem dob hibat";
    }ENDM;

    TEST(Koktle, ajalas) {
        std::ostringstream oss;
        k.veltel_ajanlas(oss, std::cin);
        EXPECT_STREQ("Koktel neve: Mas nev [1] alapanyag: Alkohol mentes Miranda Mennyiseg: 2 [2] alapanyag: Alkohols Proba Mennyiseg: 1 [3] alapanyag: Gin Gin Mennyiseg: 7 [4] alapanyag: Alkohol mentes Valami Mennyiseg: 9\nNyomjon meg az enter-t a folytatashoz...",oss.str().c_str())<<"Csak ez az egy lehet benne";
        std::istringstream iss("3");
        oss.str("");
        k.lista_alapanyagok_szerint(oss,iss);
        EXPECT_STREQ("Valassz egy ital tipust!\n1. Bor 2. Whiskey 3. Gin 4. Rum 5. Tequila 6. Sor 7. Gyumolcsle 8. Alkohols 9. Alkohol mentes \nKoktel neve: Mas nev [1] alapanyag: Alkohol mentes Miranda Mennyiseg: 2 [2] alapanyag: Alkohols Proba Mennyiseg: 1 [3] alapanyag: Gin Gin Mennyiseg: 7 [4] alapanyag: Alkohol mentes Valami Mennyiseg: 9\nNyomjon meg az enter-t a folytatashoz...",oss.str().c_str())<<"nem egyezik az elvartal";
        oss.str("");
        std::istringstream iss2("3");
        k.getKoktel(0).alapanyagok_adatok(oss, iss2);
        EXPECT_STREQ("Koktel neve: Mas nev [1] alapanyag: Alkohol mentes Miranda Mennyiseg: 2 [2] alapanyag: Alkohols Proba Mennyiseg: 1 [3] alapanyag: Gin Gin Mennyiseg: 7 [4] alapanyag: Alkohol mentes Valami Mennyiseg: 9\nAlapanyag index: Nev: Gin Gyarto: Gines Fajtaja: Gin Alkohol tartalom: 40 Szin: feher\nNyomjon meg az enter-t a folytatashoz...",oss.str().c_str())<<"Nem egyezik az elvartal";
    }ENDM;

    TEST(Italok ,remove) {
        std::ostringstream oss2; //csak hogy jobban nézen ki a kimenet
        i.setItalok(k, oss2, std::cin);
        EXPECT_EQ(9, i.getdb()) << "Nem torote az alapnyagot";
        EXPECT_EQ(0, k.getKoktelDb())<<"Nem torolte a koktelt";
        EXPECT_ANY_THROW(k.getKoktel(0))<<"Nem dob hibat";
        EXPECT_TRUE(i.tartaalmaz("Bor",1))<<"Az ittal nem tartlmaza az utolso elemet";
        EXPECT_FALSE(i.tartaalmaz("Gin",3))<<"Rosz elem torlese";
        while (i.getdb()!=0) {
            std::istringstream iss("1");
            i.removeItal(k, oss2, iss);
        }
        std::ostringstream oss;
        i.kiir_index(oss);
        EXPECT_STREQ("Nincs ital a listaban!\n",oss.str().c_str())<<"Nem ures a lista";
    }ENDM

    TEST(beolvas, teszt) {
        std::ostringstream oss;
        int szam=int_beolvas(oss,std::cin);
        EXPECT_EQ(0,szam)<<"Nem adja vissza a megfelelo erteket";
        EXPECT_STREQ("Hibas bemenet. Kerlek, adj meg egy szamot!\n",oss.str().c_str())<<"Nem adja vissza a megfelelo szoveget";
        oss.str("");
        float szam2;
        szam2=float_beolvas(oss,std::cin);
        EXPECT_TRUE(szam2==static_cast<float>(0.1))<<szam2<<"Nem adja vissza a megfelelo erteket";
        EXPECT_STREQ("Hibas bemenet. Kerlek, adj meg egy tizedes szamot!\n",oss.str().c_str())<<"Nem adja vissza a megfelelo szoveget";
        oss.str("");
        unsigned int szam3=unsigned_int_beolvas(oss,std::cin);
        EXPECT_STREQ("Hibas bemenet. Kerlek, adj meg egy elojel szamot!\n",oss.str().c_str())<<"Nem adja vissza a megfelelo szoveget";
        EXPECT_EQ(3,szam3)<<"Nem adja vissza a megfelelo erteket";
        oss.str("");
        bool szam4=bool_beolvas(oss,std::cin);
        EXPECT_STREQ("Hibas bemenet. Kerlek, adj meg egy 0 vagy 1-t!\n",oss.str().c_str())<<"Nem adja vissza a megfelelo szoveget";
        EXPECT_TRUE(szam4)<<"Nem adja vissza a megfelelo erteket";
        oss.str("");
        size_t szam5=size_beolvas(oss,std::cin);
        EXPECT_STREQ("Hibas bemenet. Kerlek, adj meg egy szamot!\n",oss.str().c_str())<<"Nem adja vissza a megfelelo szoveget";
        EXPECT_EQ(2,szam5)<<"Nem adja vissza a megfelelo erteket";
        oss.str("");
        adatok_kiirasa("zoli",oss);
        EXPECT_STREQ("zoli\n",oss.str().c_str())<<"Nem adja vissza a megfelelo szoveget";
    }ENDM;


#endif
    return 0;
}
