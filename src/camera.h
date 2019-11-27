#pragma once

#include "ray.h"

namespace trace {


    class Camera {


        public:

        inline Ray get_ray(float u, float v) const {return Ray(origin, normalize(lower_left_corner + u * horizontal + v * vertical));}


        private:
        vec3 lower_left_corner = vec3(-2.0, -1.0, -1.0);
        vec3 horizontal = vec3(4.0, 0.0, 0.0);
        vec3 vertical = vec3(0.0, 2.0, 0.0);
        vec3 origin = vec3(0.0, 0.0, 0.0);


    };





}