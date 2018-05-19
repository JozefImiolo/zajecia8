#include <iostream>
#include <string>
#include <exception> // for std::exception

struct Loud {
    std::string name;
    Loud(const std::string& name): name{name} {
        std::cout << name << ": created" << std::endl;
    }
    ~Loud() {
        std::cout << name << ": destroyed" << std::endl;
    }
};


// Case 1 - exception caught inside the function

void simple() noexcept {
    Loud a{"Foo"};
    try {
        Loud a{"Ala"};
        throw 15;         // type = int
        Loud b{"Kot"};
    } catch (char c) {    // int can be converted to char, but it's not attempted
        std::cout << "Char handler" << std::endl;
    } catch (long a) {    // doesn't quite match either
        std::cout << "Long handler" << std::endl;
    } catch (int a) {     // That's a match
        std::cout << "Int handler" << std::endl;
    } catch (...) {       // everything matches here
        std::cout << "Universal handler" << std::endl;
    }
}

// Case 2 - custom exception class

struct MyException : std::exception {
    MyException() = default;
    MyException(const MyException& other) {
        std::cout << "MyException: copy ctor" << std::endl;
    }
    const char* what() const noexcept override { return "My exception!"; }
};

// Case 2a - catch by value, wrong order
void wrong_order_value() {
    Loud a{"Ala"};
    try {
        throw MyException{};
    } catch (std::exception e) { // matches and makes a copy
        std::cout << "std::exception: " << e.what() << std::endl;
    } catch (MyException e) {    // matches better, but too late
        std::cout << "MyException: " << e.what() << std::endl;
    }
}

// Case 2b - catch by reference, wrong order polowiczny  sukces
void wrong_order_reference() {
    Loud a{"Ala"};
    try {
        throw MyException{};
    } catch (const std::exception& e) { // matches, but no copy - no slicing
        std::cout << "std::exception: " << e.what() << std::endl;
    } catch (const MyException& e) {    // matches better, but too late
        std::cout << "MyException: " << e.what() << std::endl;
    }
}

// Case 2c - catch by value, right order
void right_order_value() {
    Loud a{"Ala"};
    try {
        throw MyException{};
    } catch (MyException e) {    // matches, copy
        std::cout << "MyException: " << e.what() << std::endl;
    } catch (std::exception e) { // matches as well, too late
        std::cout << "std::exception: " << e.what() << std::endl;
    }
}

// Case 2d - pointers, works the same but someone should delete it
// Usually pointers are not used as exceptions
void wrong_order_pointers() {
    Loud a{"Ala"};
    try {
        throw new MyException{};
    } catch (const std::exception* e) { // matches, but no copy - no slicing
        std::cout << "std::exception: " << e->what() << std::endl;

        //przez wartosc to e->what wywolane z klasy exception

        delete e;
    } catch (const MyException* e) {    // matches better, but too late
        std::cout << "MyException: " << e->what() << std::endl;
        delete e;
    }
}


// Case 3 - multiple functions
int f() {
    Loud a{"Ala"};
    throw MyException{};
    Loud b{"Zebra"}; // never reached
    return 3;        // never reached
}

int g() {
    Loud a{"Kot"};
    int val1 = f();
    Loud b{"Kalmar"};
    int val2 = f();
    return val1 + val2;
}

int h() {
    Loud a{"Pantera"};
    try {
        Loud b{"Salamandra"};
        return g();
    } catch (const std::exception& e) {
        std::cout << "h(): cought std::exception saying: " << e.what() << std::endl;
        std::cout << "Rethrowing..." << std::endl;
        throw; // try changing to throw e; - what happens?
        // my exceptions rzuca throw
        // throw e ; rzuca kopie exceptions
    }
}

int k() {
    try {
        return h();
    } catch (const MyException& e) {
        std::cout << "k(): cought MyException saying: " << e.what() << std::endl;
        return 10;
    } catch (const std::exception& e) {
        std::cout << "k(): cought std::exception saying: " << e.what() << std::endl;
        return 15;
    }
}


int main() {
     simple();
    //wrong_order_value();
    // wrong_order_reference();
    // right_order_value();
    // wrong_order_pointers();
    //k();
}
