#pragma once

#include <cmath>

// A point or a direction in 3D. Three doubles, and the arithmetic to combine them.
//
// Every single thing in this ray tracer is built out of this class: positions,
// directions, surface normals, and colours. Get it right once and the rest of the
// project reads like the maths it is.
//
// TODO(jose): fill in every body marked TODO. The compiler is your checklist --
// with -Werror, a function that does not return is an error, so build after each
// one and watch the error count go down.
//
//     cmake --build build/dev

class Vec3
{
public:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    Vec3() = default;
    Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    // Negation: (1, -2, 3) becomes (-1, 2, -3).
    Vec3 operator-() const
    {
        // TODO
        return Vec3(-x, -y, -z);
    }

    // Add v into this vector, changing it in place. Returns itself so that
    // chained assignment (a += b += c) works.
    Vec3 &operator+=(const Vec3 &v)
    {
        // TODO
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    // Scale this vector in place by t.
    Vec3 &operator*=(double t)
    {
        // TODO
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    // Shrink this vector in place by t. Reuse the operator above rather than
    // writing three divisions -- division is slower than multiplication, and
    // doing it once instead of three times is free.
    Vec3 &operator/=(double t)
    {
        // TODO

        return *this *= 1 / t;
    }

    // How long the vector is. sqrt of length_squared.
    double length() const
    {
        // TODO
        return std::sqrt(length_squared());
    }

    // Length without the square root: x^2 + y^2 + z^2.
    //
    // This exists as its own function because sqrt is expensive and often
    // unnecessary. To ask "which of these two points is closer?" you can compare
    // squared lengths and get the same answer for less. You will use this in the
    // sphere intersection tomorrow.
    double length_squared() const
    {
        // TODO
        return x * x + y * y + z * z;
    }
};

// Two names for the same class, so that a declaration says what it means.
// The compiler cannot tell these apart -- they are for the human reader.
using Point3 = Vec3; // a position in space
using Color = Vec3;  // an r,g,b colour, each component 0.0 to 1.0

// --- Free functions ---------------------------------------------------------
// These are not members. Ask me why after you have filled them in; it is one of
// the signature questions.

inline Vec3 operator+(const Vec3 &u, const Vec3 &v)
{
    // TODO
    return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v)
{
    // TODO
    return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

// Component-wise multiply: (1,2,3) * (4,5,6) is (4,10,18).
// Used for colours -- tinting one colour by another.
inline Vec3 operator*(const Vec3 &u, const Vec3 &v)
{
    // TODO
    return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

// Scale by a number. Both orders exist so that 2*v and v*2 both compile.
inline Vec3 operator*(double t, const Vec3 &v)
{
    // TODO
    return Vec3(v.x * t, v.y * t, v.z * t);
}

inline Vec3 operator*(const Vec3 &v, double t)
{
    // TODO -- one line. Do not repeat the maths above.
    return t * v;
}

inline Vec3 operator/(const Vec3 &v, double t)
{
    // TODO -- also one line, for the same reason.
    return (1 / t) * v;
}

// The dot product: u.x*v.x + u.y*v.y + u.z*v.z.
//
// One number that says how much two vectors point the same way. Positive means
// roughly the same direction, zero means perpendicular, negative means opposite.
// This is the single most used operation in the whole project -- it is how the
// sphere intersection works and how a surface knows it is facing a light.
inline double dot(const Vec3 &u, const Vec3 &v)
{
    // TODO
}

// The cross product: a vector perpendicular to both inputs.
//   x = u.y*v.z - u.z*v.y
//   y = u.z*v.x - u.x*v.z
//   z = u.x*v.y - u.y*v.x
// Needed to build the camera's sideways and upwards axes.
inline Vec3 cross(const Vec3 &u, const Vec3 &v)
{
    // TODO
}

// Same direction, length exactly 1. Divide the vector by its own length.
//
// "Unit" vectors matter because once a direction has length 1, a dot product
// with it gives a clean answer instead of one scaled by an arbitrary length.
inline Vec3 unit_vector(const Vec3 &v)
{
    // TODO
}
