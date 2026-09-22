// Assertions for Vec3.
//
// Run:  cmake --build build/dev && ./build/dev/vec3_test
//
// A test that cannot fail is not a test -- this one returns a non-zero exit
// code when anything is wrong, so a script (and later CI) can tell.

#include "rt/vec3.h"

#include <cmath>
#include <cstdio>

static int failures = 0;

// Compare two doubles. Never use == on floating point: 0.1 + 0.2 is not
// exactly 0.3 in binary, so exact comparison fails on arithmetic that is
// perfectly correct. Instead ask whether they are close enough.
static void check_near(const char *what, double got, double want) {
    const double tolerance = 1e-9;
    if (std::fabs(got - want) > tolerance) {
        std::printf("FAIL  %-40s got %.12g, want %.12g\n", what, got, want);
        ++failures;
    }
}

// Compare two vectors, component by component.
static void check_vec(const char *what, const Vec3 &got, const Vec3 &want) {
    const double tolerance = 1e-9;
    if (std::fabs(got.x - want.x) > tolerance ||
        std::fabs(got.y - want.y) > tolerance ||
        std::fabs(got.z - want.z) > tolerance) {
        std::printf("FAIL  %-40s got (%g, %g, %g), want (%g, %g, %g)\n", what,
                    got.x, got.y, got.z, want.x, want.y, want.z);
        ++failures;
    }
}

int main() {
    const Vec3 a{1.0, 2.0, 3.0};
    const Vec3 b{4.0, 5.0, 6.0};

    // --- Two worked examples, so you can see the shape -----------------------

    check_vec("a + b", a + b, Vec3{5.0, 7.0, 9.0});

    check_near("length of (3,4,0)", Vec3(3.0, 4.0, 0.0).length(), 5.0);

    // --- Your turn -----------------------------------------------------------
    //
    // Fill in the third argument of each: what SHOULD the answer be?
    // Work it out on paper. Do not run the code to find out -- that tests
    // nothing, it just agrees with whatever you wrote.

    // 1. Subtraction.
    check_vec("b - a", b - a, Vec3{3.0, 3.0, 3.0});

    // 2. Component-wise multiply. (1,2,3) * (4,5,6)
    check_vec("a * b", a * b, Vec3{4.0, 10.0, 18.0});

    // 3. Scaling. Both orders must agree.
    check_vec("a * 2", a * 2.0, Vec3{2.0, 4.0, 6.0});
    check_vec("2 * a", 2.0 * a, Vec3{2.0, 4.0, 6.0});

    // 4. Division. This is the one that had the precedence bug.
    check_vec("a / 2", a / 2.0, Vec3{0.5, 1.0, 1.5});

    // 5. Negation.
    check_vec("-a", -a, Vec3{-1.0, -2.0, -3.0});

    // 6. Dot product of a and b.
    check_near("dot(a, b)", dot(a, b), 32.0);

    // 7. Perpendicular vectors have a dot product of zero. The x axis and the
    //    y axis are at 90 degrees, so this must hold whatever their lengths.
    check_near("dot of perpendicular", dot(Vec3{1, 0, 0}, Vec3{0, 1, 0}), 0.0);

    // 8. Cross gives a vector perpendicular to both inputs. x and y both lie
    //    flat, so the only axis perpendicular to both is z.
    check_vec("cross(x, y)", cross(Vec3{1, 0, 0}, Vec3{0, 1, 0}), Vec3{0, 0, 1});

    // 9. A unit vector has length 1 by definition, for any input.
    check_near("unit_vector length", unit_vector(b).length(), 1.0);

    // 10. += modifies in place. c changes; a must not.
    Vec3 c = a;
    c += b;
    check_vec("c after c += b", c, Vec3{5.0, 7.0, 9.0});
    check_vec("a unchanged by c += b", a, Vec3{1.0, 2.0, 3.0});

    // -------------------------------------------------------------------------

    if (failures == 0) {
        std::printf("all checks passed\n");
        return 0;
    }
    std::printf("%d check(s) FAILED\n", failures);
    return 1;
}
