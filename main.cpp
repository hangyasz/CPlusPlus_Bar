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
        Komunikacio::adatok_kiirasa(hibba,std::cout);
    }
    Koktlok k;
    try {
        k.olvasF(i,std::cout,std::cin);
    }catch (const char *hibba) {
        Komunikacio::adatok_kiirasa(hibba, std::cout);
    }
    do {
        std::cout<<"1 - Italok kezelese\n2 - Koktelok kezeles\n3 - veleteln koktel\n4 - koktel alapanyag szerint\n0 - Kilepes"<<std::endl;
        std::cout<<"Mit szeretnel csinalni? ";
        valasz=Komunikacio::size_beolvas(std::cout, std::cin);
        switch (valasz) {
            case 1:
                i.modosit(k, std::cout, std::cin);
                break;
            case 2:
                k.modosit(i, std::cout, std::cin);
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
    char ertek_hibba[]="Nem adja vissza a megfelelo erteket";
    char nev_hiba[]="Nem adja vissza a megfelelo nevet";
    char gyarto_hiba[]="Nem adja vissza a megfelelo gyartot";
    char tipus_hiba[]="Nem adja vissza a megfelelo tipust";
    char alkohol_hiba[]="Nem adja vissza a megfelelo alkohol tartalmat";
    char olvas_hiba[]="Hiba tortent az olvasas soran";
    char hiba_nem_kene[]="hibat dob";
    char hiba_kell[]="Nem dobot hibat";
    char hiba_lista[]="Nem ures a lista";
    char hiba_nem_tar[]="Nem tartalmazza az italt";
    char hiba_tar[]="Taralmazza az italt";
    char hiba_elter[]="Nem egyezik az elvartal";
    char hiba_szoveg[]="Nem adja vissza a megfelelo szoveget";

    TEST(Hibadobas, hibadobas) {
        EXPECT_THROW(TipusInfo::get_tipus_nev_str(TipusInfo::db+1),const char *)<<hiba_kell;
        EXPECT_THROW(Bor_szin::get_szin_nev_str(TipusInfo::db+1),const char *)<<hiba_kell;
        std::ostringstream oss;
        std::istringstream iss("Javitit nev\nGyarto\n");
        String s;
        Ital i(s,9,oss,iss);
        EXPECT_STREQ("Javitit nev",i.getNev().c_str())<<nev_hiba;
        EXPECT_STREQ("Gyarto",i.getGyarto().c_str())<<gyarto_hiba;
        EXPECT_THROW(i.setTipus(TipusInfo::db+1),const char *)<<hiba_kell;
        iss.str("Pia\nvalaki\101\n100\n");
        SzeszesItalok pia(9,oss,iss);
        EXPECT_STREQ("Pia",pia.getNev().c_str())<<nev_hiba;
        EXPECT_THROW(Elenorzes::alapanyag_szam(1),const char *)<<hiba_kell;

    }ENDM;

    Italok *i3=new Italok;
    TEST(Italok, olvasF) {
        std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        EXPECT_NO_THROW(i3->olvasF(oss, std::cin)); //elenőrzés, hogy nem dob kivételt a beolvasás
        EXPECT_EQ(10,i3->getdb())<<ertek_hibba; //ellenőrzés, hogy a beolvasott adatok száma megfelelő
        //ellenőrzés, hogy a beolvasott adatok megfelelőek
        EXPECT_EQ(2,i3->getItal(0).getTipus())<<alkohol_hiba;
        EXPECT_STREQ("Nev",i3->getItal(0).getNev().c_str())<<nev_hiba
        ;
        EXPECT_STREQ("Gyarto",i3->getItal(0).getGyarto().c_str())<<gyarto_hiba;
        EXPECT_EQ(1,i3->getItal(3).getTipus())<<alkohol_hiba;
        EXPECT_STREQ("Bor_zolk",i3->getItal(3).getNev().c_str())<<nev_hiba;
        EXPECT_STREQ("en",i3->getItal(3).getGyarto().c_str())<<gyarto_hiba;
    }ENDM;


    Koktlok *k2=new Koktlok;
    TEST(Italok, javitot_torles) {
    std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        for(int i=0;i<3;i++) {
            std::istringstream iss("8\n");
            i3->removeItal(*k2,oss,iss); //töröljük az italt
        }
        EXPECT_EQ(7,i3->getdb())<<ertek_hibba; //ellenőrzés, hogy a beolvasott adatok száma megfelelő
    }ENDM;

    TEST(Koktlok, olvas) {
        std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        EXPECT_NO_THROW(k2->olvasF(*i3, oss, std::cin)) << olvas_hiba; //ellenőrzés, hogy nem dob kivételt a beolvasás
        EXPECT_EQ(10,k2->getKoktelDb())<<ertek_hibba; //ellenőrzés, hogy a beolvasott adatok száma megfelelő
        //ellenőrzés, hogy a beolvasott adatok megfelelőek
        EXPECT_STREQ("Kedvenc",k2->getKoktel(0).getNev().c_str())<<nev_hiba;
        EXPECT_STREQ("Test_1",k2->getKoktel(1).getNev().c_str())<<nev_hiba;
        EXPECT_STREQ("Test_2",k2->getKoktel(2).getNev().c_str())<<nev_hiba;
        EXPECT_EQ(8,i3->getItal(4).getTipus())<<alkohol_hiba;
        //bolvasunk egy masik helyre elnörizük hogy a megfelelo adatok kerültek kiírva
        Italok i2;
        oss.str("");
        EXPECT_NO_THROW(i2.olvasF(oss, std::cin)) << olvas_hiba;
        EXPECT_STREQ("", oss.str().c_str())<<hiba_nem_kene;
        //ellenőrzés, hogy a beolvasott adatok megfelelőek
        EXPECT_EQ(i3->getdb(),i2.getdb())<<ertek_hibba;
        EXPECT_STREQ("hiba_Wiskey",i3->getItal(7).getNev().c_str())<<nev_hiba
        ;
        EXPECT_STREQ("key",i3->getItal(7).getGyarto().c_str())<<gyarto_hiba;
        EXPECT_STREQ("hiba_bor",i3->getItal(8).getNev().c_str())<<nev_hiba
        ;
        EXPECT_STREQ("hiba_gin",i3->getItal(9).getNev().c_str())<<nev_hiba
        ;
        EXPECT_STREQ("hiba_rum",i3->getItal(10).getNev().c_str())<<nev_hiba
        ;
        EXPECT_STREQ("hiba_tequila",i3->getItal(11).getNev().c_str())<<nev_hiba
        ;
        EXPECT_STREQ("hiba_sor",i3->getItal(12).getNev().c_str())<<nev_hiba
        ;
        EXPECT_STREQ("hiba_gyumolcsle",i3->getItal(13).getNev().c_str())<<nev_hiba
        ;
        EXPECT_STREQ("hiba_alkohols",i3->getItal(14).getNev().c_str())<<nev_hiba
        ;
        EXPECT_STREQ("hiba_alkohol_mentes",i3->getItal(15).getNev().c_str())<<nev_hiba
        ;

        //ellenőrzés, hogy a kijavitot adatokat írjuk ki a fáljba
        Koktlok k3;
        std::ostringstream oss2;
        std::istringstream iss("1\n");
        EXPECT_NO_THROW(k3.olvasF(i2,oss2,iss))<<hiba_nem_kene;
        EXPECT_STREQ("",oss2.str().c_str())<<"Nem ures a kimenet volt valami hibba a beolvasás során";
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

    //Teszteljuk ha egy koktel öszetevöjét töröljük
    TEST(Italok + Koktlok, torles) {
        std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        i3->modosit(*k2, oss, std::cin);  //tolrlünk pár italt italt
        k2->modosit(*i3, oss, std::cin); //torlünk pár koktelt
        EXPECT_EQ(14, i3->getdb()) << "Nem torote az alapnyagot"; //Enernörizük a darabszámot
        EXPECT_EQ(8, k2->getKoktelDb()) << "Nem torolte a koktelt"; //Enernörizük a darabszámot
    }ENDM;

    //Töröljük az összes kotelt
    TEST(Koktle, torlles) {
        std::ostringstream oss1; //csak hogy jobban nézen ki a kimenet
        while (k2->getKoktelDb()) { //amig van koktel toroljuk
            std::istringstream iss("1\n");
            k2->removeKoktel(oss1, iss); //mindid az elso elemet toroljuk
        }
        std::ostringstream oss;
        k2->removeKoktel(oss,std::cin); //toroljuk valamit
        EXPECT_STREQ("Nincsen koktelok\n",oss.str().c_str())<<hiba_lista; //azt várjuk hogy azt irja ki hogy üres a lista

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

    //megézük hogy helyesen müködik e az Italok konstruktora
    TEST(Italok, konstruktor) {
        Italok i;
        //ellenőrzés, hogy a konstruktor helyesen inicializálja a db számot
        EXPECT_EQ(0, i.getdb()) << ertek_hibba;
        EXPECT_THROW(i.getItal(0),const char *)<<hiba_kell; //hibbát kell dovnia
    } ENDM;
    //megézük hogy helyesen müködik e a Koktlok konstruktora
    TEST(Koktlok, konstruktor) {
        Koktlok k;
        //ellenőrzés, hogy a konstruktor helyesen inicializálja a db számot
        EXPECT_THROW(k.getKoktel(0),const char *) << olvas_hiba; //hibbát kell dovnia
        EXPECT_EQ(0, k.getKoktelDb()) << ertek_hibba; //ellenőrzés, hogy a konstruktor helyesen inicializálja a db számot
    }ENDM;



    Italok i;
    Koktlok k;
    TEST(Italok, addital) {
        std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        i.modosit(k, oss, std::cin); //hozzáadunk egy italt
        EXPECT_EQ(1, i.getdb()) << ertek_hibba;
        SzeszesItalok *test;
        //ellenőrzés, hogy a hozzáadott ital megfelelő-ek e az adatai
        EXPECT_NO_THROW(test=dynamic_cast<SzeszesItalok *>( &i.getItal(0))) << hiba_nem_kene;
        EXPECT_STREQ("Teszt", test->getNev().c_str()) <<nev_hiba;
        EXPECT_STREQ("Gyarto", test->getGyarto().c_str()) << alkohol_hiba;
        EXPECT_EQ(8, test->getTipus()) << tipus_hiba;
        EXPECT_EQ(10, test->getAlkoholTartalom()) << alkohol_hiba;
        //hozadunk minen tipusbol egy italt
        i.modosit(k, oss, std::cin);
        EXPECT_EQ(9, i.getdb()) << ertek_hibba; //megézük hogy sikerült mindegyiket hozzá adni
        //elenőrzizük az utolsó elemet
        EXPECT_EQ(1, i.getItal(8).getTipus())<<tipus_hiba; //tipusát
        EXPECT_STREQ("Bor", i.getItal(8).getNev().c_str()) <<nev_hiba; //nevet
    }ENDM;

    TEST(Ital , set) {
        std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        i.modosit(k, oss, std::cin); //átálijuk az osztályok adatait
        //elenöritük hogy ezek sikeresek volteak e?
        SzeszesItalok *test;
        EXPECT_NO_THROW(test=dynamic_cast<SzeszesItalok *>( &i.getItal(0))) << hiba_nem_kene;
        EXPECT_STREQ("Proba", test->getNev().c_str()) <<nev_hiba;
        EXPECT_STREQ("Valaki", test->getGyarto().c_str()) << alkohol_hiba;
        EXPECT_EQ(8, test->getTipus()) << tipus_hiba;
        EXPECT_EQ(15, test->getAlkoholTartalom()) << alkohol_hiba;
        Ital *test2;
        EXPECT_NO_THROW(test2 = &i.getItal(1)) << hiba_nem_kene;
        EXPECT_STREQ("Miranda", test2->getNev().c_str()) <<nev_hiba;
        EXPECT_STREQ("Pepsi", test2->getGyarto().c_str()) << alkohol_hiba;
        EXPECT_EQ(9, test2->getTipus()) << tipus_hiba;
        Gyumolcsle *test3;
        EXPECT_NO_THROW(test3=dynamic_cast<Gyumolcsle *>( &i.getItal(2))) << hiba_nem_kene;
        EXPECT_STREQ("Oszi", test3->getNev().c_str()) <<nev_hiba;
        EXPECT_STREQ("Marka", test3->getGyarto().c_str()) << gyarto_hiba;
        EXPECT_EQ(7, test3->getTipus()) << tipus_hiba;
        EXPECT_EQ(1, test3->getGyumolcsszazalek()) << ertek_hibba;
        Fajta *test4;
        EXPECT_NO_THROW(test4=dynamic_cast<Fajta *>( &i.getItal(3))) << hiba_nem_kene;
        EXPECT_STREQ("Nem sor", test4->getFajta().c_str()) << tipus_hiba;
        Gin *test5;
        EXPECT_NO_THROW(test5=dynamic_cast<Gin *>( &i.getItal(6))) << hiba_nem_kene;
        EXPECT_STREQ("feher", test5->getFajta().c_str()) <<nev_hiba;
        EXPECT_EQ(0,test5->getIz().size()) << ertek_hibba;
        Wiskey *test6;
        EXPECT_NO_THROW(test6=dynamic_cast<Wiskey *>( &i.getItal(7))) << hiba_nem_kene;
        EXPECT_STREQ("kukorica", test6->getFajta().c_str()) << tipus_hiba;
        EXPECT_EQ(5, test6->getErleses()) << ertek_hibba;
        Bor *test7;
        EXPECT_NO_THROW(test7=dynamic_cast<Bor *>( &i.getItal(8))) << hiba_nem_kene;
        EXPECT_EQ(3, test7->getSzin()) << ertek_hibba;
        EXPECT_EQ(2023, test7->getEvjarat()) << hiba_nem_tar;
        EXPECT_EQ(1, test7->getFajta_db()) << ertek_hibba;
    }ENDM;
    TEST(Koktlok, add) {
        std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        k.modosit(i, oss, std::cin); //hozzáadunk egy koktelt
        EXPECT_EQ(1, k.getKoktelDb()) << ertek_hibba; //ellenőrizük a db számot
        Koktle *test;
        //elenőrzüka az adatokat
        EXPECT_NO_THROW(test=&k.getKoktel(0)) << hiba_nem_kene;
        EXPECT_STREQ("Uj koktel", test->getNev().c_str()) <<nev_hiba;
        EXPECT_EQ(1,test->tartalmaz_e(&i.getItal(7)))<<hiba_nem_tar; //teszteljük a tartalmazás elnörzést alapanyagra
        EXPECT_TRUE(test->tartalmaz_e(2))<<hiba_nem_tar; //teszteljük a tartalmazás elnörzést tipisra

    }ENDM;

    TEST( Koktle, modosit) {
        std::ostringstream oss; //csak hogy jobban nézen ki a kimenet
        k.modosit(i, oss, std::cin);
        Koktle *test;
        //mostám letudjuk kérni az első elemet
        EXPECT_NO_THROW(test=&k.getKoktel(0)) << hiba_nem_kene;
        std::istringstream iss("0\n");
        oss.str(""); //itmár használjuk
        test->removeAlapanyag(oss, iss); //alapanyag törlés 0 eseteén viszalépünk
        //ellenőrzük hogy a modositás helyes e
        EXPECT_STREQ("Koktel neve: Mas nev [1] alapanyag: Alkohol mentes Miranda Mennyiseg: 2 [2] alapanyag: Alkohols Proba Mennyiseg: 1 [3] alapanyag: Gin Gin Mennyiseg: 7 [4] alapanyag: Alkohol mentes Valami Mennyiseg: 9\nTorolni kivant Alapanyag index: ",oss.str().c_str())<<hiba_elter;
        //külön a nevet is
        EXPECT_STREQ("Mas nev", test->getNev().c_str()) <<nev_hiba;
        //és hogy milyen italaok is vannak benne
        EXPECT_FALSE(test->tartalmaz_e(2))<<hiba_tar;
        EXPECT_TRUE(test->tartalmaz_e(3))<<hiba_nem_tar;
        EXPECT_TRUE(test->tartalmaz_e(9))<<hiba_nem_tar;
    }ENDM;


    //teszteljük a koktel egy  alapanyagának kiirását tulindexelés esstén
    TEST(Koktle, alapanyagok_adatok_index) {
        Koktle*test = &k.getKoktel(0);
        std::ostringstream oss;
        std::istringstream iss("10\n0");
        test->alapanyagok_adatok(oss, iss);
        EXPECT_STREQ("Koktel neve: Mas nev [1] alapanyag: Alkohol mentes Miranda Mennyiseg: 2 [2] alapanyag: Alkohols Proba Mennyiseg: 1 [3] alapanyag: Gin Gin Mennyiseg: 7 [4] alapanyag: Alkohol mentes Valami Mennyiseg: 9\nAlapanyag index: Hibas index!\nKoktel neve: Mas nev [1] alapanyag: Alkohol mentes Miranda Mennyiseg: 2 [2] alapanyag: Alkohols Proba Mennyiseg: 1 [3] alapanyag: Gin Gin Mennyiseg: 7 [4] alapanyag: Alkohol mentes Valami Mennyiseg: 9torolni kivant Alapanyag index: ",oss.str().c_str())<<hiba_elter;

    }ENDM;

    TEST(Kokte, torles) {
        std::ostringstream oss1; //csak hogy jobban nézen ki a kimenet
        k.addKoktel(i,oss1, std::cin);
        Koktle *test=&k.getKoktel(1);
        std::istringstream iss("0\n");
        test->removeAlapanyag(oss1,iss); //0 eseteén viszalépünk teszt
        test->removeAlapanyag(&i.getItal(0)); //egy adot alapanyagot törölünk a koktélbol
        EXPECT_FALSE(test->tartalmaz_e(8))<<hiba_tar;
        //egy alapnyagot adunk a koktelhoz
        test->addAlapanyag(i,oss1, std::cin);
        EXPECT_TRUE(test->tartalmaz_e(8))<<hiba_nem_tar;
        test->removeAlapanyag(oss1, std::cin);
        test->removeAlapanyag(oss1, std::cin);
        //most az inputrol vallo törlést teszteljük
        EXPECT_FALSE(test->tartalmaz_e(8))<<hiba_tar;
        std::ostringstream oss;
        //töröljük a koktel öszes hozávaloját
        iss.str("");
        test->removeAlapanyag(oss,iss);
        EXPECT_STREQ("A koktelnak nincsen alapnyagai!\n",oss.str().c_str())<<hiba_lista; //az várjuk hogy azt irja ki hogy nicsenek öszetevöi
        //egy adot alapanyagot adatai lekére ha nincsen alapanyaga
        std::istringstream iss2("4\n0\n");
        oss.str("");
        test->modosit(i,oss,iss2);
        EXPECT_STREQ("Mit szeretne csinalni?\n1 - alapanyag hozzaadasa\n2 - alapanyag torlese\n3 - Nev modositasa\n4 - alapanyag adatok\n0 - viszalepes\nAdja meg az utasitas szamat: A koktelnak nincsen alapnyagai!\nMit szeretne csinalni?\n1 - alapanyag hozzaadasa\n2 - alapanyag torlese\n3 - Nev modositasa\n4 - alapanyag adatok\n0 - viszalepes\nAdja meg az utasitas szamat: ",oss.str().c_str())<<hiba_lista;
        //választás tesztelése
        std::istringstream iss3("7\n0");
        oss.str("");
        test->modosit(i,oss,iss3);
       EXPECT_STREQ("Mit szeretne csinalni?\n1 - alapanyag hozzaadasa\n2 - alapanyag torlese\n3 - Nev modositasa\n4 - alapanyag adatok\n0 - viszalepes\nAdja meg az utasitas szamat: Hibas bemenet!\nMit szeretne csinalni?\n1 - alapanyag hozzaadasa\n2 - alapanyag torlese\n3 - Nev modositasa\n4 - alapanyag adatok\n0 - viszalepes\nAdja meg az utasitas szamat: ",oss.str().c_str())<<hiba_elter;
        //töroljuk az uj koktelt index alapján
        k.removeKoktel(1);
       // EXPECT_THROW(k.getKoktel(1),const char *)<<hiba_nem_kene;
    }ENDM;

    TEST(Koktlok, ajanlas_alapanyag) {
        //kerjük hogy ajánljon egy koktelt olyat amiben van ez az alapnyag
        std::ostringstream oss;
        std::istringstream iss("2\n");
        //azt várjuk hogy ilyen nelegyen
        k.lista_alapanyagok_szerint(oss,iss); //keresünk egy veletelen koktel ajánlást
        EXPECT_STREQ("Valassz egy ital tipust!\n1. Bor 2. Whiskey 3. Gin 4. Rum 5. Tequila 6. Sor 7. Gyumolcsle 8. Alkohols 9. Alkohol mentes \nNincsen ilyen alapanyagot tartalmazo koktelok\nNyomjon meg az enter-t a folytatashoz...",oss.str().c_str())<<"Megis van ilyen tipus";

    }ENDM;

    TEST(Koktlok , remove_index_adatal) {
        //koktel törölése index alapján (tulistexelés)
        EXPECT_THROW(k.removeKoktel(5),const char *)<<hiba_nem_kene;
    }ENDM;

    TEST(Koktle, ajalas) {
        std::ostringstream oss;
        std::istringstream iss0("\n");
        k.veltel_ajanlas(oss, iss0);
        //egy véleteln ajánlást kérünk csak egy lehet
        EXPECT_STREQ("Koktel neve: Mas nev [1] alapanyag: Alkohol mentes Miranda Mennyiseg: 2 [2] alapanyag: Alkohols Proba Mennyiseg: 1 [3] alapanyag: Gin Gin Mennyiseg: 7 [4] alapanyag: Alkohol mentes Valami Mennyiseg: 9\nNyomjon meg az enter-t a folytatashoz...",oss.str().c_str())<<"Csak ez az egy lehet benne";
        std::istringstream iss("3\n"); //gint szeretnénk
        oss.str("");
        //teszeljük hogy ipus szerinti ajánlást
        k.lista_alapanyagok_szerint(oss,iss);
        EXPECT_STREQ("Valassz egy ital tipust!\n1. Bor 2. Whiskey 3. Gin 4. Rum 5. Tequila 6. Sor 7. Gyumolcsle 8. Alkohols 9. Alkohol mentes \nKoktel neve: Mas nev [1] alapanyag: Alkohol mentes Miranda Mennyiseg: 2 [2] alapanyag: Alkohols Proba Mennyiseg: 1 [3] alapanyag: Gin Gin Mennyiseg: 7 [4] alapanyag: Alkohol mentes Valami Mennyiseg: 9\nNyomjon meg az enter-t a folytatashoz...",oss.str().c_str())<<hiba_elter;
        oss.str("");
        std::istringstream iss2("3\n");
        //teszeljuk hogy jo adatokat ír ki a válsztot italhoz
        k.getKoktel(0).alapanyagok_adatok(oss, iss2);
        EXPECT_STREQ("Koktel neve: Mas nev [1] alapanyag: Alkohol mentes Miranda Mennyiseg: 2 [2] alapanyag: Alkohols Proba Mennyiseg: 1 [3] alapanyag: Gin Gin Mennyiseg: 7 [4] alapanyag: Alkohol mentes Valami Mennyiseg: 9\nAlapanyag index: Nev: Gin Gyarto: Gines Tipusa: Gin Alkohol tartalom: 40 Fajta: feher\nNyomjon meg az enter-t a folytatashoz...",oss.str().c_str())<<hiba_elter;
    }ENDM;


    TEST(Italok ,remove) {
        std::ostringstream oss1; //csak hogy jobban nézen ki a kimenet
        i.modosit(k, oss1, std::cin);
        //Torlés olyan esteben ha szerepel az ital a koktelben
        EXPECT_EQ(9, i.getdb()) << "Nem torote az alapnyagot"; //az uj alapanyag szám
        EXPECT_EQ(0, k.getKoktelDb())<<"Nem torolte a koktelt"; // a kotélok száma legyen nulla
        EXPECT_THROW(k.getKoktel(0),const char *)<<hiba_nem_kene;
        //ellenöriuk a törléstről hogy helyes e
        EXPECT_TRUE(i.tartaalmaz("Bor",1))<<hiba_nem_tar;
        EXPECT_FALSE(i.tartaalmaz("Gin",3))<<hiba_tar;
        //az öszes italt töröljük
        while (i.getdb()!=0) {
            std::istringstream iss("1");
            i.removeItal(k, oss1, iss);
        }
        std::ostringstream oss;
        i.kiir_index(oss);
        //ellenőrzük hogy az összes italt törölte esteén helyes e a kiírás
        EXPECT_STREQ("Nincs ital a listaban!\n",oss.str().c_str())<<hiba_lista;
    }ENDM

    TEST(Koktlok , remove_index_ures) {
        //koktel törölése index nincsenek koktélok
        EXPECT_THROW(k.removeKoktel(0),const char *)<<hiba_nem_kene;
    }ENDM;

    //koktel ajálás ugy hogy nincek koktelok
    TEST(Koktlok , ajanlas_ures) {
        std::ostringstream oss;
        std::istringstream iss("\n");
        k.veltel_ajanlas(oss,iss); //keresünk egy veletelen koktel ajánlást
        EXPECT_STREQ("Nincsenek koktelok\n",oss.str().c_str())<<hiba_lista; //azt várjuk hogy azt irja ki hogy üres a lista
        oss.str("1");
        iss.str("\n");
        k.lista_alapanyagok_szerint(oss,iss); //keresünk egy koktel ajánlást alapanyag szerint
        EXPECT_STREQ("Nincsenek koktelok\n",oss.str().c_str())<<hiba_lista; //azt várjuk hogy azt irja ki hogy üres a lista
    }ENDM;

    //a beolvaasos fügvényeim tesztelése
    TEST(beolvas, teszt) {
        std::ostringstream oss;
        std::istringstream iss("Z\n0\n");
        int szam=Komunikacio::int_beolvas(oss,iss);
        EXPECT_EQ(0,szam)<<ertek_hibba;
        EXPECT_STREQ("Hibas bemenet. Kerlek, adj meg egy szamot!\n",oss.str().c_str())<<hiba_szoveg;
        std::ostringstream oss2;
        float szam2;
         iss.str("Z\n0.1\n");
        szam2=Komunikacio::float_beolvas(oss2,iss);
        EXPECT_TRUE(szam2==static_cast<float>(0.1))<<szam2<<ertek_hibba;
        EXPECT_STREQ("Hibas bemenet. Kerlek, adj meg egy tizedes szamot!\n",oss2.str().c_str())<<hiba_szoveg;
        oss.str("");
        iss.str("-Z\n3\n");
        unsigned int szam3=Komunikacio::unsigned_int_beolvas(oss,iss);
        EXPECT_STREQ("Hibas bemenet. Kerlek, adj meg egy elojel szamot!\n",oss.str().c_str())<<hiba_szoveg;
        EXPECT_EQ(3,szam3)<<ertek_hibba;
        oss.str("");
        iss.str("Z\n1\n");
        bool szam4=Komunikacio::bool_beolvas(oss,iss);
        EXPECT_STREQ("Hibas bemenet. Kerlek, adj meg egy 0 vagy 1-t!\n",oss.str().c_str())<<hiba_szoveg;
        EXPECT_TRUE(szam4)<<ertek_hibba;
        oss.str("");
        iss.str("Z\n2\n");
        size_t szam5=Komunikacio::size_beolvas(oss,iss);
        EXPECT_STREQ("Hibas bemenet. Kerlek, adj meg egy szamot!\n",oss.str().c_str())<<hiba_szoveg;
        EXPECT_EQ(2,szam5)<<ertek_hibba;
        oss.str("");

    }ENDM;

#endif
    return 0;
}
