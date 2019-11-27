#pragma once

#include "scene.h"
#include "vec3.h"

namespace trace {


    class RayTracer {


        Scene scene;

        float height = 400;
        float width = 800;

        public:

        inline Scene& get_scene() {return scene;}

        vec3 compute_pixel(int x, int y);

        bool trace_reflected(const Ray& r_in, const HitInfo& in_hit, Ray& r_out, HitInfo& hit_out) const;
        bool trace_refracted(const Ray& r_in, const HitInfo& in_hit, Ray& r_out, HitInfo& hit_out, float& R) const;
        
        float get_ior_out(const Ray& r_in, const HitInfo& in_hit, vec3& normal) const;





    };










}