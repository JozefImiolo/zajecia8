#include <iostream>

template <typename T>
T max(T a, T b) {
    return a < b ? b : a;
}

// Overload
int max(int a, int b) {
    return 3;
}

//wbierana jest zwykla funkcja 1 mozliwosx

// Specialization
// 2 mozliwosc specjalizacja , wciaz uzywana nieszblonowa i tak dalej
// can also be max<>(..), or max<int>(..)
template <>
int max<int>(int a, int b) {
    return 17;
}

template<typename T>
T* max(T* a, T* b)
{
    return *a < *b ? b : a;
        // ten jest bardzie j wyspecjaliwaony i zostanie wybrany dla wskanikow
}


// Explicit instantiation
template double max(double, double);

// "Don't generate here, I promise it is elsewhere"
extern template float max(float, float);


// Non-type params
template <typename T, int N>
struct A {
    T f();
    void stuff() { }
};

template <typename T, int N>
T A<T, N>::f() { return T{}; }

// Specialization of a single method
template <>
void A<int, 5>::stuff() { std::cout << "A<int,5>::stuff()" << std::endl; }


// Full specialization
template <>
struct A<void, 0> {
    void g();
};

void A<void, 0>::g() { }

// Partial specialization
template <int N>
struct A<void, N> {
    void h();
};

template <int N>
void A<void, N>::h() { }


// Template methods
struct C {
    template <typename T> void f();
};

template <typename T>
void C::f() { };

// Specialization of template method
template <>
void C::f<int>() { };


// Template template methods
template <typename T>
struct D {
    template <typename U> void f();
};

template <typename T>
template <typename U>
void D<T>::f() { }

//#define MAX(a,b) ((a)<(b)?(b):(a))
int main() {

       //(std::cout<<3)<8?8:3<<std::endl; ostrem z liczba porowanai
//    std::cout<<MAX(7,9)<<std::endl;


//    std::cout<<MAX((3&4),(10&2))<<std::endl;


//    std::cout<<MAX(3&4,10&2)<<std::endl;

//    int a=3, b=5;


//    std::cout<<MAX(++a,++b)<<std::endl;


    //bez nawiasow zle dziala


    max(1.3, 1.7);// max<double>
     max(1.4, 1.7); // juz zrobiona funkcja dla doubli
     max(1, 1.7); // probuje podasowac musi dopasowac dokladnie nie domysli sie tego
     // sensowanie dziala dla zwyklych funkcji sum(double, double);
     max<double>(1,0.7);
    max(2, 3);     // non-template max(int, int)
   max<>(2, 3);   // max<int> specialization jkurwa weresja szablonowa


 max(1.2f, 5.0f); // linker error - max<float> not defined

//    A<int, 5> a1;      // generic version
//    int val = a1.f();
//    a1.stuff();        // method specialization

//    A<void, 3> a2;     // partial specialization
//    a2.h();
//    // a2.f();         // error - specialization doesn't have f()

//    A<void, 0> a3;     // full specialization
//    a3.g();
}

