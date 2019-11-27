#pragma once

#include "ray.h"
#include "material.h"

namespace trace {

    class Primitive {

        public:

        Material material;
        virtual bool intersect(const Ray& r, HitInfo& hit) const = 0;
    };

    class Sphere: public Primitive {
        public:
        Sphere(const vec3& center, float radius):
               center(center), radius(radius) {}
        Sphere() = default;
        vec3 center;
        float radius;

        bool intersect(const Ray& r, HitInfo& hit) const override;
    };

    class Triangle {
        public:
        Triangle(const vec3& v1, const vec3& v2, const vec3& v3):
                 v1(v1), v2(v2), v3(v3) {}
        Triangle() = default;
        vec3 v1, v2, v3;
    };




}