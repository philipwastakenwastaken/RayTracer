#pragma once

#include "vec3.h"
#include "material.h"

namespace trace {


#define M_1_PIf 0.31830988618379067154
#define M_2_PIf 0.636619772367581343076f

    const static float DEFAULT_TMAX = 10000;
    const static float EPSILON = 0.0001f;

    struct Ray {
        Ray(const vec3& origin, const vec3& direction, float tmin = 0, float tmax = DEFAULT_TMAX): 
            direction(direction), origin(origin), tmin(tmin), tmax(tmax) {}
        Ray() = default;

        vec3 direction;
        vec3 origin;
        float tmin, tmax;

        inline vec3 point_at(float t) {return origin + t * direction;}
    };

    struct HitInfo {
        HitInfo(): ray_ior(1.0f), has_hit(false), trace_depth(0)  {}

        vec3 position;
        float dist;
        float ray_ior;
        bool has_hit;
        vec3 shading_normal;
        vec3 geometric_normal;
        Material material;
        unsigned trace_depth;
    };








}