#include <iostream>

#include "Ital.h"
#include "bevitel_kezel.h"
#include "koktle.h"
#include "tesztek.h"
#include "memtrace.h"

int main() {
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
    //oszes_teszt();
    return 0;
}