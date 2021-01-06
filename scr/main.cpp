#include <iostream>
#include "tiffio.h"

int main(int, char**) {
    std::cout << "libtiff version:" << TIFFLIB_VERSION << "\n";
    return 0;
}
