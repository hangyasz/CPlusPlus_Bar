//
// Created by Zoli on 2024. 05. 17..
//

#ifndef FUGVENYEK_HPP
#define FUGVENYEK_HPP

#include <iostream>
#include <fstream>
#include "string5.h"
#include "memtrace.h"
#include "Ital.h"

struct Tesztek {
    //elemörzi hogy jo-e a százalék
    template<typename T>
    static void szazalek_tests(T szazalek);
};


struct Dinamikus {

    template<typename T> //atmásolja a forrás tömböt a temp tömbbe
    static void din_atmasol(T *temp, T *forras, size_t meret);
    template<typename T> //kihagy torlendo elemet az átmásolásbol
    static void din_atmasol(T *temp, T *forras, size_t meret, size_t torlendo);
    template<class T> //italok letrehozasa függvény tipus alapján
    static Ital *italok_bevitel(size_t tipus,std::ostream &os, std::istream &is);
    template<class T>  //italok letrehozasa függvény nevel és tipus alapján
    static Ital *italok_bevitel(String nev,size_t tipus,std::ostream &os, std::istream &is);
    template<class T> //italok letrehozasa függvény fáljbeolvasáshoz
    static Ital *italok_olvas(std::ifstream &file,size_t tipus, std::ostream &os, std::istream &is);


};

template<typename T>
void Tesztek::szazalek_tests(T szazalek) {
    if(szazalek>100 or szazalek<0) {
        throw "Hibas szazalek! Adjon meg egy helyes szazalekot!";
    }
}


//átmasolja a forrás tömböt a temp tömbbe
template<typename T>
void Dinamikus::din_atmasol(T *temp, T *forras, size_t meret) {
    for (size_t i = 0; i < meret; i++) {
        temp[i] = forras[i];
    }
}
//kihagy torlendo elemet az átmásolásbol
template<typename T>
void Dinamikus::din_atmasol(T *temp, T *forras, size_t meret, size_t torlendo) {
    din_atmasol(temp, forras, torlendo); //átmasolja a forrás tömböt a temp tömbbe a torlendo elemig
    for (size_t i = torlendo; i < meret-1; i++) {//ki hagyja a torlendo elemet
        temp[i] = forras[i + 1];  //és átmásolja az adatokat
    }
}

//italok letrehozasa függvény tipus alapján
template<class T>
Ital * Dinamikus::italok_bevitel(size_t tipus,std::ostream &os, std::istream &is) {
    return  new T(tipus,os,is); //megivja a mefele tipushoz a kunstrukorát
}


//italok letrehozasa függvény nevel és tipus alapján
template<class T>
Ital * Dinamikus::italok_bevitel(String nev,size_t tipus,std::ostream &os, std::istream &is) {
    return  new T(nev,tipus,os,is); //megivja a mefele tipushoz a kunstrukorát
}
//italok letrehozasa függvény fáljbeolvasáshoz
template<class T>
Ital * Dinamikus::italok_olvas(std::ifstream &file,size_t tipus, std::ostream &os, std::istream &is) {
    return new T(file,tipus,os,is); //megivja a mefele tipushoz a kunstrukorát
}

#endif //FUGVENYEK_HPP
