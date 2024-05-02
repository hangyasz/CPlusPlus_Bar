#include <iostream>

#include "Ital.h"
#include "memtrace.h"
#include "faljkezel.h"
#include "koktle.h"


int main() {
    Italok italok2;
    italok2.olvasF();
    Koktlok koktlok;
    koktlok.olvasF(italok2);
    koktlok.kiir_index();
    return 0;
}