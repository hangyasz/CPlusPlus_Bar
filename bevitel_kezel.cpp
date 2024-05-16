//
// Created by Zoli on 2024. 04. 17..
//

#include "bevitel_kezel.h"
#include <iostream>
#include <cstring>
#include <limits>
#include "memtrace.h"


void bufer_torles() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


int int_beolvas() {
    int olvas;
    while(!(std::cin >> olvas)){
        bufer_torles();
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
    }
    return olvas;
}

float float_beolvas() {
    float olvas;
    while(!(std::cin >> olvas)){
        bufer_torles();
        std::cout << "Hibas bemenet. Kerlek, adj meg egy tizedes szamot!" << std::endl;
    }
    return olvas;
}

unsigned int unsigned_int_beolvas() {
    unsigned int olvas;
    while(!(std::cin >> olvas)){
        bufer_torles();
        std::cout << "Hibas bemenet. Kerlek, adj meg egy elojel szamot!" << std::endl;
    }
    return olvas;
}

size_t size_beolvas() {
    size_t olvas;
    while(!(std::cin >> olvas)){
        bufer_torles();
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
    }
    return olvas;
}

void vait() {
    std::cout << "Nyomjon meg az enetert a folytatashoz...";
    bufer_torles();
    std::getchar();
}




