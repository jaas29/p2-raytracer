#pragma once
#include "rt/ray.h"
#include "rt/vec3.h"

// Everything that hit() reports abbout the clossest hit

struct HitRecord // a class that everythign is public by default.
{
    Point3 p;       // wher ethe ray met the surface
    Vec3 normal;    // the surface normal there, length 1
    double t = 0.0; // how far along the ray that was
};

// Anything a ray can hit. Each shape has its own hit()

class Hittable
{
public:
    virtual ~Hittable() = default; // if destructor is not virtual it would only run ~Hittable never ~Sphere

    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const = 0; // it would run the verzion that belongs to the object.
};
