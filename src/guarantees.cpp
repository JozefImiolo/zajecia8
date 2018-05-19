#include <cstdio>
#include <vector>
#include <stdexcept>
#include <fstream>

// 1. nothrow/nofail - operation can't possibly fail or throw an exception
// 1 poziom bezpiszensttwa
void f(std::vector<int>& a, std::vector<int>& b) {
    // nierzuci w dokumentacji sprawdzone
    int f = 3;                     // can't throw
    if (! a.empty()) {             // .empty() is nothrow
        a[0] = f + 5;              // can't throw
    }
    std::swap(a, b);               // nothrow (in theory only since C++17)
}

// 2. No guarantee - in presence of exceptions code does Bad Stuff
int some_throwing_function() {
    throw std::runtime_error("Dont' feel like working today");
}

void nasty(const char* path, std::vector<int>& vec) {
    std::FILE* file = std::fopen(path, "w");  // can't throw
    int* buffer = new int[10];                // can throw, but unlikely
    // int* buffer = new(std::nothrow) int[10];   // this version of new can't throw

    for (int i = 0; i < 10; ++ i) {
        buffer[i] = some_throwing_function(); // can throw - if it does,
                                              // file is not closed and buffer not
                                              // deallocated - BAD!
    }
    for (int i = 0; i < 10; ++ i) {
        vec.push_back(buffer[i]);                // can throw too
    }
    delete[] buffer;
    std::fclose(file);
}

// 3. Basic guarantee - in presence of exceptions, code does not leave a mess behind
void basic(const char* path, std::vector<int>& vec) {
    std::FILE* file = std::fopen(path, "w");  // can't throw
    int* buffer = new int[10];                // can throw, but unlikely

    try {
        for (int i = 0; i < 10; ++ i) {
            int value = some_throwing_function(); // can throw - if it does,
                                                  // file is not closed and buffer not
                                                  // deallocated - BAD!
            vec.push_back(value);                    // can throw too
        }
        for (int i = 0; i < 10; ++ i) {
            vec.push_back(buffer[i]);                // can throw too
        }
    } catch (...) {
        delete[] buffer;                          // clean up and propagate
        std::fclose(file);
        throw;
    }
    delete[] buffer;                              // repetition :/
    std::fclose(file);
}

void basic_with_RAII(const char* path, std::vector<int>& vec) {
    std::ofstream file{path};
    std::vector<int> buffer(10);

    // No need to clean up ever, file and buffer manage their resources
    for (int i = 0; i < 10; ++ i) {
        buffer[i] = some_throwing_function();
    }
    //
    vec.reserve(vec.size()+10);
    // jesli poleci wyjatek to nie zminie nam vectora
    //jesli ok to pushback pojdzie
    // przechowujemy int konst kop nie rzuci wyjatku
    // nie ma wyjatku wiec stron guarantee, bez dodatkowego narzutu , tzreba sie zastanwoic
    for (int i = 0; i < 10; ++ i) {
        vec.push_back(buffer[i]);
    }



        // skopiowac lub przenisc problem z konstruktor kopijujacym i rzuci wyjatek np, string
        //skutek przerwana operacja vector czesciowo zmodyfikowany
        // lepiej albo rozbimy do okonca albo nic dlateg o to basic

}

// 4. Strong guarantee - if it fails, state of involved objects is unchanged
void strong(const char* path, std::vector<int>& vec) {
    std::ofstream file{path};
    std::vector<int> buffer(10);

    // No need to clean up ever, file and buffer manage their resources
    for (int i = 0; i < 10; ++ i) {
        buffer[i] = some_throwing_function();
    }
    // Until now, vec was not changed - if it fails before this point, it's OK

    // Make a copy and modify that - if some push_back throws an exception,
    // original vec is still not changed
    std::vector<int> copy(vec);
    for (int i = 0; i < 10; ++ i) {
        copy.push_back(buffer[i]);
    }
    std::swap(vec, copy);     // nothrow - the whole function succeeded przepiecie wskanikkow i rzomair

    //gwarantujemy sukces albo stan obiektow jest nietkniety
    // basic guarantee zawsze

    // stong zastanowic sie realne podejscie


}



int main() {
}
