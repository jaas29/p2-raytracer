#include <iostream>
#include "rt/vec3.h"
#include "rt/ray.h"

Color ray_color(const Ray &r)
{
    auto unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y + 1);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}
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
