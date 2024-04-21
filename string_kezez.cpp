//
// Created by Zoli on 2024. 04. 17..
//

#include "string_kezez.h"
#include <iostream>
#include <cstring>



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
}
