#include <iostream>

#include "Ital.h"
#include "memtrace.h"
#include "faljkezel.h"
#include "koktle.h"
#include "tesztek.h"

int main() {
    /*size_t valasz;
    Italok i;
    i.olvasF();
    Koktlok k;
    k.olvasF(i);
    do {
        std::cout<<"1 - Italok kezelese\n2 - Koktelok kezeles\n3 - veleteln koktel\n 4 - koktel alapanyag szerint\n 0 - Kilepes"<<std::endl;
        std::cout<<"Mit szeretnel csinalni? ";
        valasz=size_beolvas();
        switch (valasz) {
            case 1:
                i.setItalok(k);
                break;
            case 2:
                k.Set(i);
                break;
            case 3:
                k.veltel_ajanlas();
                break;
            case 4:
                k.lista_alapanyagok_szerint();
                break;
            case 0:
                break;
        }
    }while (valasz!=0);
*/
    Italok i;
    i.olvasF();
    i.kiir_index();
    //test_Italok_hozadas();
    return 0;
}