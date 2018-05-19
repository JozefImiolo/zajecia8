#include <iostream> // general I/O header
#include <fstream>  // file I/O
#include <cassert>

// std::ios_base - abstract base class

int main() {

    // Open and remove existing content
    // can also use std::ios::out instead of ios_base
    std::ofstream file{"/invalid/path", std::ios_base::out | std::ios_base::trunc};
    // Detailed meaning of these flags:
    // http://en.cppreference.com/w/cpp/io/basic_filebuf/open

    // Get flags - combination (|) of the following:
    // - goodbit = ok
    // - eofbit  = end of file reached
    // - failbit = mild error (failed operation)
    // - badbit  = HDD is burning
    std::ios::iostate state = file.rdstate();

    if (state & std::ios::failbit) {
        // std::cerr - standard error (diagnostic) output
        std::cerr << "Failed to open file" << std::endl;
    }

    // Less verbose checks:
    if (file.fail()) { /* ... */ }   // true if failbit or badbit set
    if (! file) { /* ... */ }        // same as above - operator!
    if (file) { /* ... */ }          // opposite - bool conversion operator

    file.clear(); // clears error flags, call to open() below does that too

    const char* path = "plik.txt";
    file.open(path, std::ios::out | std::ios::trunc);

    const int SIZE = 10;
    int data[SIZE];
    // Fill it with some data pattern
    for (int i = 0; i < SIZE; ++ i) {
        data[i] = 0x40302010;
    }
    file.write(reinterpret_cast<char*>(data), sizeof(data));
    // sizeof(data) or SIZE * sizeof(int), total number of bytes
    // Does not return number of bytes written, either all is written or operation
    // fails and badbit is set

    std::ios::pos_type pos = file.tellp(); // "tell-put", tellg "tell-get" for input stream
    std::cout << "Position in file: " << pos << std::endl;

    // Move 10 bytes before the end of file
    // end, beg, cur
    file.seekp(-10, std::ios::end);
    std::cout << "Position in file: " << file.tellp() << std::endl;

    // Methods often return ofstream&, can be chained
    file.put('A').put('L').put('A');

    file.seekp(2); // absolute position in file
    std::cout << "Position in file: " << file.tellp() << std::endl;
    file << "Kot";

    file.seekp(-10, std::ios::cur);
    std::cout << "Failed? " << file.fail() << std::endl;
    std::cout << "Position in file: " << file.tellp() << std::endl;

    // Can explicitly close
    file.close();

     // check if stream has an open file
    assert( !file.is_open());
   /* struct Point{
        double x,y;
    };
    std::istream& operator>> (std::istream& is, Point& p)
    {
        return is>>p.x>>p.y;
    }
    Point p;
std::cin>>p;*/
    // Closed file stream can be opened again, possibly a different file
    // file.open(path/*, std::ios::out - default value */);

    // no need to close - destructor takes care of that
}
