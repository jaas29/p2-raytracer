#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "rt/hittable.h"

// The scene: owns every object, and is itself Hittable.
class HittableList : public Hittable
{
public:
    void add(std::unique_ptr<Hittable> object)
    {
        objects_.push_back(std::move(object));
    }

    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override
    {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = t_max;
        // TODO: ask object->hit(...) with the range t_min to closest_so_far,
        for (const auto &object : objects_)
        {
            if (object->hit(r, t_min, closest_so_far, temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

private:
    std::vector<std::unique_ptr<Hittable>> objects_;
};