#pragma once
#include "rt/vec3.h"

class Ray
{
public:
    Ray() = default;
    Ray(const Point3 &origin, const Vec3 &direction) : orig(origin), dir(direction) {}

    const Point3 &origin() const { return orig; }
    const Vec3 &direction() const { return dir; }

    // The point 3 steps along hte ray: origin + t * direction.
    Point3 at(double t) const
    {
        return orig + t * dir;
    }

private:
    Point3 orig;
    Vec3 dir;
};