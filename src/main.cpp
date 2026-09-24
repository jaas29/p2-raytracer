#include "rt/vec3.h"
#include <iostream>

int main()
{
    const int image_width = 256;
    const int image_height = 256;
    // PPM header: format, size, max value
    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";
    for (int j = 0; j < image_height; ++j) // row, top to bottom
    {
        for (int i = 0; i < image_width; ++i) // columsn, left to right
        {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.0;
            // tunr r,g,b into ints 0...255 and print them
            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}
