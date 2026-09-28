#include <iostream>
#include "rt/vec3.h"
#include "rt/ray.h"

bool hit_sphere(const Point3 &center, double radius, const Ray &r)
{
    Vec3 oc = center - r.origin();              // oc = C-Q
    auto a = dot(r.direction(), r.direction()); // a = d.d
    auto b = -2 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    return discriminant >= 0;
}

Color ray_color(const Ray &r)
{
    if (hit_sphere(Point3(0, 0, -1), 0.5, r))
    {
        return Color(1, 0, 0);
    }
    auto unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y + 1);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}
int main()
{
    // Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = int(image_width / aspect_ratio); // 225
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = Point3(0, 0, 0);

    // Vectors across and down the viewport edges
    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0); // minus: image rows go DOWN, y goes UP

    // One pixel step, across and down
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Top-left corner of the viewport, then the centre of pixel (0,0)
    auto viewport_upper_left = camera_center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // PPM header: format, size, max value
    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";
    for (int j = 0; j < image_height; ++j) // row, top to bottom
    {
        for (int i = 0; i < image_width; ++i) // columsn, left to right
        {

            auto pixel_center = pixel00_loc + i * pixel_delta_u + j * pixel_delta_v;
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);
            Color pixel_color = ray_color(r);
            // tunr r,g,b into ints 0...255 and print them
            int ir = int(255.999 * pixel_color.x);
            int ig = int(255.999 * pixel_color.y);
            int ib = int(255.999 * pixel_color.z);
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}
