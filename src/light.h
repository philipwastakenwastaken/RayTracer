#pragma once

#include "ray.h"

namespace trace {

    class RayTracer;

    class Light {
        public:
        Light(RayTracer* tracer, vec3 intensity, vec3 pos):  intensity(intensity), pos(pos), tracer(tracer) {}
        Light(vec3 intensity, vec3 pos): intensity(intensity), pos(pos) {}

        virtual bool sample(const vec3& hit_pos, vec3& dir, vec3& L) const = 0;
        vec3 intensity;
        vec3 pos;
        RayTracer* tracer;
        unsigned number_of_samples = 1;

    };

    class PointLight: public Light {

        public:

        PointLight(RayTracer* tracer, vec3 intensity, vec3 pos): Light(tracer, intensity, pos) {}

        virtual bool sample(const vec3& hit_pos, vec3& dir, vec3& L) const override;

    };





}