//
// Created by Zoli on 2024. 04. 17..
//

#include "bevitel_kezel.h"
#include <iostream>
#include <cstring>
#include <limits>

/*
char* hoszusor_olvas() {
    char *s = new char[1];
    strcpy(s,"");
    size_t db = 0;
    char c;
    std::cin.clear();
    if(std::cin.get(c) && c!='\n') {
        char *uj = new char[2+db];
        strcpy(uj,s);
        delete [] s;
        s=uj;
        s[db++]=c;
        s[db]='\0';
    }
    while(std::cin.get(c) && c!='\n'){
        char *uj = new char[2+db];
        strcpy(uj,s);
        delete [] s;
        s=uj;
        s[db++]=c;
        s[db]='\0';
    }
    return s;
   /* char *beolvasott=new char[100];
    std::cin.getline(beolvasott,100);*/
    //return beolvasott;
//}

char* hoszusor_olvas() {
    size_t capacity = 25;  // Kezdeti kapacitás
    char* s = new char[capacity];
    size_t length = 0;  // A tömb jelenlegi hossza
    std::cin.clear();
    char c;
    std::cin.get(c);
    if(c!='\n'){
        s[length++]=c;
    }
    while (std::cin.get(c) && c != '\n') {
        if (length + 1 == capacity) {  // Ha betelt a tömb
            capacity *= 2;  // Duplázzuk a kapacitást
            char* temp = new char[capacity];
            strcpy(temp,s); // Másoljuk az eddigi karaktereket
            delete[] s;
            s = temp;
        }
        s[length++] = c;
    }
    s[length] = '\0';  // Lezárjuk a stringet
    return s;
}


int int_beolvas() {
    int olvas;
    while(!(std::cin >> olvas)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
    }
    return olvas;
}

float float_beolvas() {
    float olvas;
    while(!(std::cin >> olvas)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
    }
    return olvas;
}

unsigned int unsigned_int_beolvas() {
    unsigned int olvas;
    while(!(std::cin >> olvas)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
    }
    return olvas;
}

size_t size_beolvas() {
    size_t olvas;
    while(!(std::cin >> olvas)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Hibas bemenet. Kerlek, adj meg egy szamot!" << std::endl;
    }
    return olvas;
}

void vait() {
    std::cout << "Nyomjon meg az enetert a folytatashoz...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getchar();
}




