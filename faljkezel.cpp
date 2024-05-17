//
// Created by Zoli on 2024. 04. 18..
//

#include "faljkezel.h"
#include <iostream>
#include <fstream>
#include "Ital.h"
#include <limits>
#include "memtrace.h"

//Ital tipust alakitja szama
int Ital::getTipus_Szam() const {
    switch (tipus) {
        case bor: return 1;
        case whiskey: return 2;
        case gin: return 3;
        case rum: return 4;
        case tequila: return 5;
        case sor: return 6;
        case gyumolcsle: return 7;
        case alkohols: return 8;
        case alkohol_mentes: return 9;
        default:
            std::cerr<<"Hibás típus!"<<std::endl;
        break;
    }
    return 0; //ha nem sikerult 0 adunk vissza
}


//Az ittal osztály altal tárolt adaokat kiirja egy fajlba <tipus(száma)><nev><gyarto> formátumban
void Ital::kiirF(std::ofstream& os) const {
    os<<getTipus_Szam()<<"<"<<nev<<"><"<<gyarto<<">";
}

//A SzesszesItalok osztály altal tárolt adatokat kiirja egy fajlba <alkoholTartalom> formátumban
void SzeszesItalok::kiirF(std::ofstream& os) const {
    Ital::kiirF(os);//Ital osztály adatok kiirása
    os<<"<"<<alkoholTartalom<<">";
}
//A Whiskey osztály altal tárolt adatokat kiirja egy fajlba <jeleg><erleses> formátumban
void Wiskey::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os);//SzeszesItalok osztály adatok kiirása
    os<<"<"<<jeleg<<"><"<<erleses<<">";
}
//A Gin szinét számra alakítja
int Gin::getSzin_szam() const {
    switch (szin) {
        case szintelen: return 1;
        case pink: return 2;
        case egyeb: return 3;
        default: std::cerr<< "Hibás szín!"<<std::endl;
        break;
    }
    return 0; //ha nem sikerult 0 adunk vissza
}
//A Gin osztály altal tárolt adatokat kiirja egy fajlba <szin(száma)><iz> formátumban
void Gin::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os);//SzeszesItalok osztály adatok kiirása
    os<<"<"<<getSzin_szam()<<"><";
    if(iz.size()!=0) //ha nem üres a string akkor kerul kiirásra
        os<<iz;
    os<<">";
}

//A Rum fajtáját számra alakítja
int Rum::getFajta_Szam() const {
    switch (fajta) {
        case fuszeres_rum: return 1;
        case fekete_rum: return 2;
        case arany_rum: return 3;
        case feher_rum: return 4;
        default: std::cerr<<"Hibás fajta!"<<std::endl;
        break;
    }
    return 0; //ha nem sikerult 0 adunk vissza
}

//A Rum osztály altal tárolt adatokat kiirja egy fajlba <fajta(száma)> formátumban
void Rum::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os); //SzeszesItalok osztály adatok kiirása
    os<<"<"<<getFajta_Szam()<<">";
}

//A Tequila fajtáját számra alakítja
int Tequila::getFajta_Szam() const {
    switch (fajta) {
        case silver: return 1;
        case gold: return 2;
        case aged: return 3;
        default: std::cerr<< "Hibás fajta!"<<std::endl;
        break;
    }
    return 0; //ha nem sikerult 0 adunk vissza
}
//A Tequila osztály altal tárolt adatokat kiirja egy fajlba <fajta(száma)> formátumban
void Tequila::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os); //SzeszesItalok osztály adatok kiirása
    os<<"<"<<getFajta_Szam()<<">";
}

//A Sor osztály altal tárolt adatokat kiirja egy fajlba <tipus_sor> formátumban
void Sor::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os); //SzeszesItalok osztály adatok kiirása
    os<<"<"<<tipus_sor<<">";
}

//A Gyumolcsle osztály altal tárolt adatokat kiirja egy fajlba <gyumolcsszazalek> formátumban
void Gyumolcsle::kiirF(std::ofstream& os) const {
    Ital::kiirF(os); //Ital osztály adatok kiirása
    os<<"<"<<gyumolcsszazalek<<">";
}


//A bor szinét számra alakítja
int Bor::getSzin_Szam() const {
    switch (szin) {
        case voros: return 1;
        case rose: return 2;
        case feher: return 3;
        default: std::cerr<<"Hibás szín!"<<std::endl;
        break;
    }
    return 0; //ha nem sikerult 0 adunk vissza
}

//A Bor osztály altal tárolt adatokat kiirja egy fajlba <evjarat><szin(száma)><fajta_db><fajta> formátumban
void Bor::kiirF(std::ofstream& os) const {
    SzeszesItalok::kiirF(os); //SzeszesItalok osztály adatok kiirása
    os<<"<"<<evjarat<<"><"<<getSzin_Szam()<<"><"<<fajta_db<<"><";
    if(fajta_db>=1)
        os<<fajta[0];
    for(size_t i=1;i<fajta_db;i++){
        os<<"><"<<fajta[i]; //ha tobb fajta van akkor a kovetkezo fajta kiirasa
    }
    os<<">";
}

//Az Italok osztály altal tárolt adatokat kiirja egy fajlba
 void Italok::kiirF() const{
    std::ofstream file;
    file.open("italok.txt"); //megnyitjuk a fajlt
    if (!file.is_open())
        throw"nem nyilt meg az italok.txt";
    for(size_t i=0;i<db;i++){
        file<<getItal(i)<<"\n"; //kiirjuk az italokat a fajlba
    }
    file.close(); //fajl bezarasa
}

//szam_olvas függvény ami egy fajlban található számot olvasbe
int szam_olvas(std::ifstream &file) {
    char kacsacsor;
    int szam;
    file>>kacsacsor>>szam>>kacsacsor; //kacsacsorok közötti szám olvasása
    return szam; //szam viszadása
}
//unsigned int_olvas függvény ami egy fajlban található unsigned int számot olvasbe
unsigned int uszam_olvas(std::ifstream &file) {
    char kacsacsor;
    unsigned int szam;
    file>>kacsacsor>>szam>>kacsacsor; //kacsacsorok közötti szám olvasása
    return szam; //szam viszadása
}

//size_t_olvas függvény ami egy fajlban található size_t számot olvasbe
size_t size_olvas(std::ifstream &file) {
    char kacsacsor;
    size_t szam;
    file>>kacsacsor>>szam>>kacsacsor; //kacsacsorok közötti szám olvasása
    return szam; //szam viszadása
}

//float_olvas függvény ami egy fajlban található float számot olvasbe
float float_olvas(std::ifstream &file) {
    char kacsacsor;
    float szam;
    file>>kacsacsor>>szam>>kacsacsor; //kacsacsorok közötti szám olvasása
    return szam; //szam viszadása
}

//Ital osztály konstruktora ami egy fajlban található adatokat olvas be
Ital::Ital(std::ifstream &file) {
    setTipus(alkohol_mentes); //alapértelmezett tipus beállítása minden ittal alkoholmentes
    file>>nev; //nev beolvasása
    file>>gyarto; //gyarto beolvasása
}

//SzeszesItalok osztály konstruktora ami egy fajlban található adatokat olvas be
SzeszesItalok::SzeszesItalok(std::ifstream &file):Ital(file) {//inicializálo listán ital konstruktor hívása
    setTipus(alkohols); //tipus beállítása alkoholosra
    setAlkoholTartalom(float_olvas(file)); //alkohol tartalom beolvasása
}

//a kapott számot viszaalakítja a megfelelő szinre és beállítja
void Bor::setSzin(int kap) {
    switch (kap) {
        case 1: szin= voros;
        break;
        case 2: szin= rose;
        break;
        case 3: szin= feher;
        break;
        default: std::cerr<< "Hibás szín!"<<std::endl; //hibbas szam esetén
        std::cout<<"Nev: "<<getNev()<<" Gyarto: "<<getGyarto()<<std::endl; //kiírjuk a nevét és gyartojat
        setSzin(); //megkérjuk hogy a felhasználo kezel vigye be adatot
        break;
    }
}

//Bor osztály konstruktora ami egy fajlban található adatokat olvasbe
Bor::Bor(std::ifstream &file):SzeszesItalok(file),fajta(nullptr) { //inicializálo listán szeszes italok konstruktor hívása és fajta nullptr-ra állítása
    setTipus(bor); //tipus beállítása borra
    setEvjarat(szam_olvas(file)); //evjarat beolvasása és beállítása
    if(!evjarat_teszt(evjarat)){ //ha a beolvasott evjarat nem tobb mint az aktualis evjarat
        std::cout<<"Hibás évjárat: "<<std::endl;
        std::cout<<"Nev: "<<getNev()<<" Gyarto: "<<getGyarto()<<getSzinNev()<<std::endl;
        setEvjarat(); //megkérjuk hogy a felhasználo kezel vigye be adatot
    }
    setSzin(szam_olvas(file));//szin beolvasása és beállítása
    setFajta_db(size_olvas(file)); //fajta db beolvasása
    if(fajta_db!=0) {
        String *fajatk=new String[fajta_db]; //fajta db méretű string tömb létrehozása
        for(size_t i=0;i<this->getFajta_db();i++){
            file>>fajatk[i]; //fajtak beolvasása a tömbbe
        }
        setFajta_string(fajatk); //fajta string tömb beállítása
    }
    else {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ha nincs fajta akkor a sor végéig olvasunk és a következő sorba lépünk
    }
}

//Whiskey osztály konstruktora ami egy fajlban található adatokat olvasbe
Wiskey::Wiskey(std::ifstream &file):SzeszesItalok(file) { //inicializálo listán SzeszesItalok konstruktor hívása
    setTipus(whiskey); //tipus beállítása whiskey-re
    file>>jeleg; //jeleg beolvasása
    setErleses(uszam_olvas(file)); //erleses beolvasása és beállítása
}

//a kapt számot viszaalakítja a Gin megfelelő szinre és beállítja
void Gin::setSzin(int kap) {
    switch (kap) {
        case 1: szin= szintelen;
        break;
        case 2: szin= pink;
        break;
        case 3: szin= egyeb;
        break;
        default: std::cerr<< "Hibás szín!"<<std::endl;
        std::cout<<"Nev: "<<getNev()<<" Gyarto: "<<getGyarto()<<std::endl;
        setSzin(); //megkérjuk hogy a felhasználo kezel vigye be a szinet
        break;
    }
}
//Gin osztály konstruktora ami egy fajlban található adatokat olvasbe
Gin::Gin(std::ifstream &file):SzeszesItalok(file) { //inicializálo listán SzeszesItalok konstruktor hívása
    setTipus(gin); //tipus beállítása gin-re
    setSzin(szam_olvas(file)); //szin beolvasása és beállítása
    file>>iz; //iz beolvasása
}

//a kapott számot viszaalakítja a Rum megfelelő fajtájára és beállítja
void Rum::setFajta(int kap) {
    switch (kap) {
        case 1: fajta= fuszeres_rum;
        break;
        case 2: fajta= fekete_rum;
        break;
        case 3: fajta= arany_rum;
        break;
        case 4: fajta= feher_rum;
        break;
        default: std::cerr<< "Hibás fajta!"<<std::endl;
        std::cout<<"Nev: "<<getNev()<<" Gyarto: "<<getGyarto()<<std::endl;
        setFajta(); //megkérjuk hogy a felhasználo kezel vigye be a fajtát
        break;
    }
}
//Rum osztály konstruktora ami egy fajlban található adatokat olvasbe
Rum::Rum(std::ifstream &file):SzeszesItalok(file) { //inicializálo listán SzeszesItalok konstruktor hívása
    setTipus(rum);  //tipus beállítása rum-ra
    setFajta(szam_olvas(file)); //fajta beolvasása és beállítása
}


//a kapott számot viszaalakítja a Tequila megfelelő fajtájára és beállítja
void Tequila::setFajta(int kap){
    switch (kap) {
        case 1: fajta= silver;
        break;
        case 2: fajta= gold;
        break;
        case 3: fajta= aged;
        break;
        default: std::cerr<<"Hibás fajta!"<<std::endl;
        std::cout<<"Nev: "<<getNev()<<" Gyarto: "<<getGyarto()<<std::endl;
        setFajta(); //megkérjuk hogy a felhasználo kezel vigye be a fajtát
        break;
    }
}

//Tequila osztály konstruktora ami egy fajlban található adatokat olvasbe
Tequila::Tequila(std::ifstream &file):SzeszesItalok(file) { //inicializálo listán SzeszesItalok konstruktor hívása
    setTipus(tequila); //tipus beállítása tequila-ra
    setFajta(szam_olvas(file)); //fajta beolvasása és beállítása
}

//Sor osztály konstruktora ami egy fajlban található adatokat olvasbe
Sor::Sor(std::ifstream &file):SzeszesItalok(file) { //inicializálo listán SzeszesItalok konstruktor hívása
    setTipus(sor); //tipus beállítása sor-ra
    file>>tipus_sor; //sornek a tipus beolvasása
}

//Gyumolcsle osztály konstruktora ami egy fajlban található adatokat olvasbe
Gyumolcsle::Gyumolcsle(std::ifstream &file):Ital(file),gyumolcsszazalek(0) { //inicializálo listán Ital konstruktor hívása és gyumolcsszazalek 0-ra állítása
    setTipus(gyumolcsle); //tipus beállítása gyumolcsle-re
    setGyumolcsszazalek(uszam_olvas(file)); //gyumolcsszazalek beolvasása és beállítása
}

//Italok osztály fáljbol olvaso függvénye
void Italok::olvasF() {
    std::ifstream file;
    file.open("italok.txt"); //fajl megnyitása italok.txt
    if (!file.is_open())
        throw"nem nyilt meg az italok.txt";
    int tipus; //tipus szám beolvasására
    while ((file>>tipus)){
        switch (tipus) { //tipus szám alapján a megfelelő ital létrehozása
            case 1:
                addItal(new Bor(file));
                break;
            case 2:
                addItal(new Wiskey(file));
                break;
            case 3:
                addItal(new Gin(file));
                break;
            case 4:
               addItal(new Rum(file));
                break;
            case 5:
               addItal(new Tequila(file));
                break;
            case 6:
                addItal(new Sor(file));
                break;
            case 7:
               addItal(new Gyumolcsle(file));
                break;
            case 8:
                addItal(new SzeszesItalok(file));
            break;
            case 9:
               addItal(new Ital(file));
                break;
            default:
                std::cerr<<"Hibas tipus kreme vigye fell majd kezzel vagy vegye fell a kapcsolatot a feljlesztovel"<<std::endl;
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ha hibas tipus akkor a sor végéig olvasunk és a következő sorba lépünk
                break;
        }
    }
}

//Koktel osztály fáljba vallo kiíro fugvénye
void Koktle::kiirF(std::ofstream &os) const {
    os<<alapanyag_db; //alapanyagok számának kiirása
    os<<"<"<<nev<<">"; //nev kiirása kacsacsorok között
    for (size_t i=0; i<alapanyag_db; i++){ //alapanyagok kiirása
        os<<"<"<<alapanyagok[i]->getTipus_Szam()<<"><"<<alapanyagok[i]->getNev()<<"><"; //tipus szám, nev kiirása
        os<<menyiseg[i]<<">"; //menyiseg kiirása
    }
}

//Koktolok osztály fáljba vallo kiíro fugvénye
void Koktlok::kiirF() const {
    std::ofstream file;
    file.open("koktelok.txt"); //fajl megnyitása koktelok.txt
    if (!file.is_open())
        throw"nem nyilt meg a koktelok.txt";
    for (size_t i=0; i<koktel_db; i++){ //vegik megyünk a koktelok tobjén és kiirjuk oket a fajlba
        file<<getKoktel(i);
        file<<"\n"; //sor végének kiirása
    }
}

//Koktelok osztály fáljbol olvaso függvénye
void Koktlok::olvasF(Italok &italok ) {
    std::ifstream file;
    file.open("koktelok.txt"); //fajl megnyitása koktelok.txt
    if (!file.is_open())
        throw"nem nyilt meg a koktelok.txt";
    size_t alapanyag_db;
    while (file>>alapanyag_db){ //alapanyagok számának beolvasása
        String nev;
        file>>nev; //nev beolvasása0
        Ital **alapanyagok=new Ital*[alapanyag_db]; //alapanyagok tömb létrehozása
        unsigned int *menyiseg=new unsigned int[alapanyag_db]; //menyiseg tömb létrehozása
        for (size_t i=0; i<alapanyag_db; i++){
            int tipus=szam_olvas(file); //tipus szám beolvasása
            String nev_ital;
            file>>nev_ital; //ital nevének beolvasása
            switch (tipus) {
                case 1:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,bor); //viszaadja az ital cimet
                    break;
                case 2:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,whiskey); //viszaadja az ital cimet
                    break;
                case 3:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,gin); //viszaadja az ital cimet
                    break;
                case 4:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,rum); //viszaadja az ital cimet
                    break;
                case 5:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,tequila); //viszaadja az ital cimet
                    break;
                case 6:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,sor); //viszaadja az ital cimet
                    break;
                case 7:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,gyumolcsle); //viszaadja az ital cimet
                    break;
                case 8:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,alkohols); //viszaadja az ital cimet
                    break;
                case 9:
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,alkohol_mentes);  //
                    break;
                default: //ha nemtaljuk a tipust akkor kiirjuk az itall nevét és kérjük be a tipust
                    std::cout<<"Hibas tipus ital nev: "<<nev_ital<<  " mi legyen az uj tipus: "<<std::endl;
                    ital_tipus bevit=tipus_valszto(); //tipus beolvasása a felhasználótól
                    alapanyagok[i]=ital_letezik_e(italok,nev_ital,bevit); //viszaadja az ital cimet
                    break;
            }
            menyiseg[i]=uszam_olvas(file); //menyiseg beolvasása
        }
        addKoktel(new Koktle(nev,alapanyag_db,alapanyagok,menyiseg)); //hozzáadjuk a koktelt a tömbhöz és létrehozzuk a kotelt a konstruktorral
    }
}

//Az italok tömbben nézuk hogy egy alapanyag benne van e ha nincsen hozzáadjuk
Ital* Koktlok::ital_letezik_e(Italok &italok, String nev, ital_tipus tipus){
    size_t db=italok.getdb();
    for(size_t i=0; i<db; i++){
        Ital *akt=italok.getItalCsilag(i);
        if(akt->getTipus()==tipus and nev==akt->getNev()){ //ha a tipus és a nev megegyezik akkor visszaadjuk az italt
            return akt;
        }
    }
    std::cout<<"\nNem talalhato az ital!: most hozaadjuk a tipus: "<<get_tipus_nev_str(tipus)<<" Nev: "<<nev<<std::endl;
    italok.addItal(nev,tipus); //ha nem találjuk az italt akkor hozzáadjuk
    italok.kiirF(); //kiirjuk az italokat a fajlba
    return italok.getItalCsilag(db); //visszaadjuk az ujonal hozzáadott italt ami az utolsó helyen van
}

//felüldefiniált << operátor az Ital osztályhoz hogy kiirhassuk az adatokat egy fajlba
std::ofstream& operator<<(std::ofstream& os,const Ital &ital) {
    ital.kiirF(os); //kiirF függvény meghívása az adoott italra
    return os;
}


//felüldefiniált << operátor az Koktle osztályhoz hogy kiirhassuk az adatokat egy fajlba
std::ofstream& operator<<(std::ofstream& os,const Koktle &koktle) {
    koktle.kiirF(os);
    return os;
}


