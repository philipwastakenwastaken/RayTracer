#include "primitives.h"

namespace trace {

    bool Sphere::intersect(const Ray& r, HitInfo& hit) const {

        float A = dot(r.direction, r.direction);
        float B = dot((2 * r.direction),(r.origin - center));
        float C = dot((r.origin - center), (r.origin - center)) - radius*radius;
        float discriminant = B * B - 4 * A * C;

        // if true there are solutions to the quadratic equation
        if (discriminant >= 0) {

            float half_b = -B / 2;
            float sqrt_half_b = sqrt(half_b * half_b - C);

            float t1 = half_b - sqrt_half_b;
            float t2 = half_b + sqrt_half_b;

            // in case of intersections there will always be two points, t1 and t2.
            // we also need to check bounds such that we dont intersect with a
            // sphere behind us.
            if (t1 >= r.tmin && t1 <= r.tmax) {
                hit.dist = t1;
                hit.position = r.origin + t1 * r.direction;
            }
            else if (t2 >= r.tmin && t2 <= r.tmax) {
                hit.dist = t2;
                hit.position = r.origin + t2 * r.direction;
            }
            else {
                return false;
            }

            // if we reach this point we have hit the sphere
            hit.geometric_normal = normalize(hit.position - center);
            hit.shading_normal = normalize(hit.position - center);
            hit.has_hit = true;
            hit.material = material;

            return true;
        }

        return false;
    }


}