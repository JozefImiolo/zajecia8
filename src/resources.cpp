#include <iostream>
#include <cstring>

class String {
    char* buf;
public:
    String(const char* str): buf{new char[std::strlen(str) + 1]} {
        std::strcpy(buf, str);
    }
    String (const String& other){
        buf=new char[std::strlen(other.buf)+1];
        std::strcpy(buf, other.buf);

        // kontrukto moze wywowlac
    }

   //   String (const String& other): String{other.buf}{} delegoweani konstruktoea

    // skrot jak sie komentuje
    String& operator = (const String& other){

        if(this == &other)
            return *this;
        delete[] buf;
          buf=new char[strlen(other.buf)+1];

          std::strcpy(buf, other.buf);

         return *this;
    }

    // inny sposob
    /*
     * porzestawaic operacje
     * char * tmp=new char[strlen(other.buf)+1];
          std::strcpy(tmp, other.buf);
          delete[] buf;
          buf=temp
          return *this;
          // nie ma problemow

          // 3 wersja copy swap idiom
          /*
           * opertor=
           *
           * {
           * String tmp{other};
           * std::swap(buf,tmp.buf);
           * tmp zostanie zniczszona i destruktor siw wywola
           * dodatkowe operacje a=a niepotrzebnie
           *
           *
           * inny trik mozna przekazac przez wartosc
           * kompilator sam tworzy koipe nieptrzeba temp
           * i zamieniamy wskaniki

           (c=a)=b;
           konwencja & kaskadowo // przemyslcec na spokoju

          // rule of three rule of five  ctor and =
    /*
     * String (const String& other): buf{other.buf}
     *   * String& operator = (const String& other){ buf=other.buf;
     * return *this}
     * */

    // destruktor b pamiec zwolni a a nie mozej juz wolnic zwolnionej pamieci craesh w runtime
    // wygenerowane domyslnie nie sa zazywczja ok :(
    // jak alokuja pamiec zarzadzaja zosoabmi to
    // destruktor tor cop i operatorprzypisania jak piszemy sami to rule of three to obslugujemy zasob i trzeba sie nim pobawic

    ~String() {
        delete[] buf;
    }
};


int main() {
    String a{"Ala"};
   String b{a}; //konstruktor kopiujacy
    String c{"Kot"};
    c = a;
    a=a;//operator przypisania domsylny
    // na to trzba uwazac a=a;


}
