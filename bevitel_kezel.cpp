//
// Created by Zoli on 2024. 04. 17..
//

#include "bevitel_kezel.hpp"
#include <iostream>
#include <cstring>
#include <limits>
#include "memtrace.h"

//Buffer torlese
void bufer_torles() {
    std::cin.clear(); //hibaflag torlese
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //beolvasott adatok torlese
}

//szamam beolvasasa
int int_beolvas() {
    int olvas;
    while(!(std::cin >> olvas)){ //amig nem sikerul beolvasni egy szamot
        bufer_torles(); //buffer torlese
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
    }
    return olvas; //visszater a beolvasott szammal
}
//float beolvasasa
float float_beolvas() {
    float olvas;
    while(!(std::cin >> olvas)){ //amig nem sikerul beolvasni egy float szamot
        bufer_torles(); //buffer torlese
        std::cout << "Hibas bemenet. Kerlek, adj meg egy tizedes szamot!" << std::endl;
    }
    return olvas; //visszater a beolvasott float szammal
}
//unsigned int beolvasasa
unsigned int unsigned_int_beolvas() {
    unsigned int olvas;
    while(!(std::cin >> olvas)){ //amig nem sikerul beolvasni egy unsigned int szamot
        bufer_torles(); //buffer torlese
        std::cout << "Hibas bemenet. Kerlek, adj meg egy elojel szamot!" << std::endl;
    }
    return olvas;//visszater a beolvasott unsigned int szammal
}
//size_t beolvasasa
size_t size_beolvas() {
    size_t olvas;
    while(!(std::cin >> olvas)){ //amig nem sikerul beolvasni egy size_t
        bufer_torles(); //buffer torlese
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
    }
    return olvas; //visszater a beolvasott size_t
}
//vait fuggveny
void vait() {
    std::cout << "Nyomjon meg az enetert a folytatashoz...";
    bufer_torles(); //buffer torlese
    std::getchar(); //enter lenyomasara var
}




