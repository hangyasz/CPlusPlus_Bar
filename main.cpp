#include <iostream>

#include "Ital.h"
#include "memtrace.h"
#include "faljkezel.h"
#include "koktle.h"


int main() {
    Italok italok2;
    italok2.olvasF();
    Koktlok kok;
    kok.addKoktel(italok2);
    kok.addKoktel(italok2);
    kok.kiir_index();
    kok.kiirF();
    return 0;
}