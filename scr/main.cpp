#include <iostream>
#include "tiffio.h"
#include "zlib.h"

int main(int argc, char* argv[]) {
    std::cout << "libtiff version:" << TIFFLIB_VERSION << "\n";
    std::cout << "zlib version:" << ZLIB_VERSION << "\n";
    TIFF* tif = TIFFOpen(argv[1], "r");
    if (tif) {
	int dircount = 0;
	do {
	    dircount++;
	} while (TIFFReadDirectory(tif));
	printf("%d directories in %s\n", dircount, argv[1]);
	TIFFClose(tif);
    }
    return 0;
}
