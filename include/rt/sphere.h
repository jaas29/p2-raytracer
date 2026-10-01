#pragma once

#include <cmath>

#include "rt/hittable.h"

class Sphere : public Hittable
{
public:
    Sphere(const Point3 &center, double radius) : center_(center), radius_(radius) {}
    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override
    {
        Vec3 oc = center_ - r.origin();
        auto a = dot(r.direction(), r.direction());
        auto b = -2.0 * dot(r.direction(), oc);
        auto c = dot(oc, oc) - radius_ * radius_;
        auto discriminant = b * b - 4 * a * c;

        if (discriminant < 0)
            return false;

        auto sqrt = std::sqrt(discriminant);

        // The nearest root that lies in the allowable range
        auto root = (-b - sqrt) / (2.0 * a);
        if (root <= t_min || t_max <= root)
        {
            root = (-b + sqrt) / (2.0 * a);
            if (root <= t_min || t_max <= root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = unit_vector(rec.p - center_);
        return true;
    }

private:
    Point3 center_;
    double radius_;
};
