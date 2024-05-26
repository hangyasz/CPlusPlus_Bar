//
// Created by Zoli on 2024. 04. 13..
//

#include <iostream>
#include "bevitel_kezel.h"
#include "Ital.h"
#include "koktle.h"
#include "fugvenyek.hpp"
#include "memtrace.h"

//Italok osztaly parameter nelkuli konstruktora
Italok::Italok() :ListaItalok(nullptr), db(0) {} //inicilitálo listan ListaItalok nullpointerre állítása és db 0-ra állítása

//Italok osztaly destruktor
Italok::~Italok() {
    for (size_t i = 0; i < db; i++) {
        delete ListaItalok[i];  //minden tarolt ittal torlese
    }
    delete [] ListaItalok; //lista torlese
}


//megmindja hogy az adott ital tipus szerepel e a listaban
bool Italok::tartaalmaz(String nev, size_t tipus) const {
    for(size_t i=0;i<db;i++){ //vegig megy a listan
        if(ListaItalok[i]->getTipus()==tipus and ListaItalok[i]->getNev()==nev )
            return true; //ha megtalalja az adott italt akkor igazt add visza
    }
    return false; //kulonben hamisat
}


//Uj ittal hozzadas
void Italok::addItal(std::ostream &os, std::istream &is) {
    Ital **uj=new Ital*[db+1]; // egyel nagyobb tomb foglalas
    //atmasoljuk az adatokat;
    Dinamikus::din_atmasol(uj,ListaItalok,db);
    typedef Ital* (*CreateItalFunction)(size_t tipus,std::ostream &, std::istream &); //letrehozunk egy pointert ami egy fuggvenyt mutat
    //letrehozunk egy tombot ami a fuggvenyeket tartalmazza
    CreateItalFunction createItalFunction[]={Dinamikus::italok_bevitel<Bor>,Dinamikus::italok_bevitel<Wiskey>,Dinamikus::italok_bevitel<Gin>,Dinamikus::italok_bevitel<Fajta>,Dinamikus::italok_bevitel<Fajta>,Dinamikus::italok_bevitel<Fajta>,Dinamikus::italok_bevitel<Gyumolcsle>,Dinamikus::italok_bevitel<SzeszesItalok>,Dinamikus::italok_bevitel<Ital>};
    size_t tipus=Komunikacio::tipus_valszto(os,is); //ital tipus valasztasa
    uj[db]=createItalFunction[tipus-1](tipus,os,is); //uj ital hozzaadasa
    delete [] ListaItalok; //regi tomb törlése
    ListaItalok=uj;     //tomb legyen az uj tobb
    db++;   //db növelése
}

//a kapot italt beleteszi a tombe
void Italok::addItal(Ital *kap) {
    Ital **uj=new Ital*[db+1]; //uj tomb foglalas
    //adatok atmasolas
    Dinamikus::din_atmasol(uj,ListaItalok,db);
    uj[db]=kap; //az uj tomb utols eleme legyen a kap ittal
    delete [] ListaItalok; //toroljuk a tombot
    ListaItalok=uj;     //a tomb legyen egynlő az uj tombel
    db++;
}

//uj italt adunk a listához aminek  már tudjuk a nevét és a tipusat
void Italok::addItal(String nev, size_t tipus, std::ostream &os, std::istream &is) {
    if(!tartaalmaz(nev,tipus)) {
        typedef Ital* (*CreateItalFunction)(String, size_t, std::ostream &, std::istream &);
        CreateItalFunction createItalFunction[]={Dinamikus::italok_bevitel<Bor>,Dinamikus::italok_bevitel<Wiskey>,Dinamikus::italok_bevitel<Gin>,Dinamikus::italok_bevitel<Fajta>,Dinamikus::italok_bevitel<Fajta>,Dinamikus::italok_bevitel<Fajta>,Dinamikus::italok_bevitel<Gyumolcsle>,Dinamikus::italok_bevitel<SzeszesItalok>,Dinamikus::italok_bevitel<Ital>};
        addItal(createItalFunction[tipus-1](nev,tipus,os,is));
    }
}

//visza addja a tarolt italok db szamat
size_t Italok::getdb() const {
    return db;
}

//kiirja az osszes italt indexükell együt
void Italok::kiir_index(std::ostream &os) const {
    if(db==0){//ha nincs ital a listaban
        os<<"Nincs ital a listaban!"<<std::endl; //kiirja hogy nincs ital
        return;
    }
    for(size_t i=0;i<db;i++){ //vegig megy a listan
        os<<"\n["<<1+i<<"] "<<*ListaItalok[i]; //kiirja az ital indexet es az ital adatait
    }
    os<<std::endl;
}

//removeItal fuggveny ami egyelemü listabol torol
void Italok::removeItal() {
    delete ListaItalok[0];
    delete [] ListaItalok;
    ListaItalok=nullptr; //a listat nullpointerre allitjuk
    db=0; //db 0-ra allitjuk
}

//ital törlése a listáboll
void Italok::removeItal(Koktlok &k, std::ostream &os, std::istream &is) {
    kiir_index(os); //kiirja az italokat indexukkel egyutt
    size_t index;
    os << "\nAdja meg a torolni kivant ital indexet: ";
    index = Komunikacio::size_beolvas(os, is); //beolvasuk a torolni kivant ital indexet
    while (index > db) {
        os << "Hibas index!" << std::endl;
        index = Komunikacio::size_beolvas(os, is); //ha hibas indexet adott meg akkor ujra beolvas
    }
    if (index == 0) //0 akkor viszalepunk
        return;
    --index; //atalakitas 0-tol vallo indexelesre
    for(size_t i=0; i<k.getKoktelDb();++i) { //vegig megy a koktelokon
        Koktle* koktle=&k.getKoktel(i);
        if(koktle->tartalmaz_e(ListaItalok[index])!=0) {   //ha az ital szerepel a koktelben
            if(k.removeAlapanyag_Italok(i,ListaItalok[index],os, is))  //megkerdezuk hogy toroljuk az italt vagy hogy bizosan toroljuk
                return; //ha megesem akarjuk torolni akkor viszalépunk
        }
    }
    if(db-1==0) { //ha csak egy ital van a listaban akkor toroljuk az italt
       removeItal();
        return; //viszalepunk
    }
    Ital **tmp = new Ital*[db - 1]; //letrehozunk egy uj tombot egyel kisebbel
    Dinamikus::din_atmasol(tmp, ListaItalok, db, index); //atmasoljuk az adatokat
    delete ListaItalok[index]; //toroljuk a kivalsztot  italt
    db--; //csokentjuk a tatolr italok db szamat
    delete[] ListaItalok; //toroljuk a regi tombot
    ListaItalok = tmp; //a lista legyen az uj tomb
}

//viszaadja az adott indexu italt
Ital &Italok::getItal(size_t index) const {
    if (index >= db) {
        throw "Hibas index!";
    }
    return *ListaItalok[index];
}


//Italok osztaly adatait lehet alitani
void Italok::modosit(Koktlok &k, std::ostream &os, std::istream &is) {
    size_t valaszto;
    size_t index;
    do{
        os<<"Mit szeretne csinalni?\n1 - Ital hozzaadasa\n2 - Ital torlese\n3 - Ital modositasa\n4 - Italok kiiras";
        Menu::menu_vege(os); //kiirjuk a menut
        valaszto=Komunikacio::size_beolvas(os, is); //beolvasuk a felhasznalo valasztasat
        switch (valaszto) {
            case 1:
                addItal(os, is); //ha 1 akkor uj ital hozzaadasa
                break;
            case 2:
                removeItal(k, os, is); //ha 2 akkor ital torlese
                break;
            case 3: //ha 3 akkor ital modositasa
                kiir_index(os); //kiirjuk az italokat indexukkel egyutt
                os<<"\nAdja meg a modositani kivant ital indexet: ";
                index=Komunikacio::size_beolvas(os,is); //beolvasuk a modositani kivant ital indexet
                if(index>db){
                    os<<"Hibas index!"<<std::endl;
                    break;
                }
                if(index==0) //ha 0 akkor viszalepunk
                    break;
                try {
                    getItal(index-1).modosit(os,is); //az adott indexu ital adatainak modositasa
                }catch (const char *s){
                    os<<s<<std::endl;
                }
                break;
            case 4:
                this->kiir_index(os); //ha 4 akkor kiirjuk az italokat
                break;
            case 0: //ha 0 akkor viszalepunk
                break;;
            default: Menu::hibba(os); //ha hibas bemenetet kapunk akkor hibat irunk ki
                break;
        }

    }while (valaszto!=0);
    try {
        kiirF(); //kiirjuk az italokat a fajlba
    } catch (const char *s) {
        os << s << std::endl;
        os<<"Nem sikerult az italokat kiirni a fajlba!"<<std::endl;
        Komunikacio::vait(os, is); //varakozas
    }
}


