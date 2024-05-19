//
// Created by Zoli on 2024. 05. 17..
//

#ifndef FUGVENYEK_HPP
#define FUGVENYEK_HPP

#include <iostream>
#include <fstream>
#include "string5.h"
#include "memtrace.h"
#include "koktle.h"
#include "Ital.h"


template<typename T>
void din_atmasol(T *temp, T *forras, size_t meret) {
    for (size_t i = 0; i < meret; i++) {
        temp[i] = forras[i];
    }
}

template<typename T>
void din_atmasol(T *temp, T *forras, size_t meret, size_t torlendo) {
    din_atmasol(temp, forras, torlendo);
    for (size_t i = torlendo; i < meret-1; i++) {
        temp[i] = forras[i + 1];
    }
}

template<typename T>
void szazalek_tests(T szazalek) {
    if(szazalek>100 or szazalek<0) {
        throw "Hibas szazalek! Adjon meg egy helyes szazalekot!";
    }
}


template<class T>
Ital *italok_bevitel(size_t tipus,std::ostream &os, std::istream &is) {
    return  new T(tipus,os,is);
}


//italok letrehozasa függvény nevel és tipus alapján
template<class T>
Ital *italok_bevitel(String nev,size_t tipus,std::ostream &os, std::istream &is) {
    return  new T(nev,tipus,os,is);
}

template<class T>
Ital *italok_olvas(std::ifstream &file,size_t tipus, std::ostream &os, std::istream &is) {
    return new T(file,tipus,os,is);
}

#endif //FUGVENYEK_HPP
