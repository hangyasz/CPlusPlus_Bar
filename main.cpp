#include <iostream>

#include "Ital.h"
#include "memtrace.h"
#include "faljkezel.h"



int main() {

    Italok italok;
    italok.addItal();
    italok.addItal();
    italok.kiir_index();
    std::cout<<italok.getItal(0)<<std::endl;
    return 0;
}
