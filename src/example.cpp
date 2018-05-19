#include "example.hpp"
#include <iostream>
#include <string>
struct C{
    virtual void f() const{
    }
    virtual ~C()=default;
};
struct D : C{
    virtual void f() const override{}

};
void f(C c)
{
    c.f();
}

int main()
{
    D d;
    C a{d};
    f(d);
    // podanie przez wartosc niszczy polimorfizm
    // przez wskanik i referencja ok

    //slicing :D
    // tylko bierzemy bazowqa

}


struct A{
    std::string a;
    A() : a{"dsfsdf"}
     {std::cout<<"fsdfsdfsdf"<<std::endl;}

    // obiet a tworzymy stringa
};
struct B : A
{
    std::string a;
    std::string c;
    B(): c{"ala"}, A{}, a{"Dfsf"}
    {}
    // najpierw konstruktor A
    //pozniejkolejnosc pol w klasie najpierw a potem c

    // destruktor niszy w odwrotnej kolejnosci
     //sprawdzic a{c}
    // kolejnosc na lisicie inizcializacyjnej nie ma znaczenia
    //gdyby miala "rozen konstruktory
};
