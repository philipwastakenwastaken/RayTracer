#pragma once
#include "vec3.h"
#include "rt_random.h"
#include "glm/gtc/constants.hpp"

namespace trace {


    inline void rotate_to_normal(const vec3& normal, vec3& v) {
        const float sign = copysignf(1.0f, normal.z);
        const float a = -1.0f / (1.0f + fabsf(normal.z));
        const float b = normal.x*normal.y*a;
        v = vec3(1.0f + normal.x*normal.x*a, b, -sign * normal.x)*v.x
          + vec3(sign*b, sign*(1.0f + normal.y*normal.y*a), -normal.y)*v.y
          + normal * v.z;
    }




    inline vec3 sample_cosine_weighted(const vec3& normal) {
        double psi1 = mt_random();
        double psi2 = mt_random();

        float theta = acos(sqrt(psi1));
        float phi = 2 * glm::pi<float>() * psi2;

        vec3 v(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));

        rotate_to_normal(normal, v);
        return v;
    }




}
