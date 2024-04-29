#include <iostream>

#include "Ital.h"
#include "memtrace.h"
#include "faljkezel.h"



int main() {
    Italok italok2;
    italok_beolvas(italok2);
    Koktle koktel(italok2);
    koktel.kiir();
    /*Italok italok;
    italok.addItal();
    italok.kiir_index();*/
    return 0;
}
