#include "shader.h"
#include "ray_tracer.h"
#include "scene.h"
#include "sampler.h"


namespace trace {



        vec3 Glossy::shade(const Ray& r, const HitInfo& hit) const {

            if (hit.trace_depth >= max_trace_depth) {
                //std::cout << "hit max depth\n";
                return vec3(0.0f);
            }
            //std::cout << hit.trace_depth << std::endl;

            float R;
            Ray reflected, refracted;
            HitInfo hit_reflected, hit_refracted;

            tracer->trace_reflected(r, hit, reflected, hit_reflected);
            tracer->trace_refracted(r, hit, refracted, hit_refracted, R);

            //std::cout << hit.trace_depth << std::endl;
            //std::cout << hit_reflected.trace_depth << std::endl;
            //std::cout << hit_refracted.trace_depth << "\n" << std::endl;

            return R * shade_new_ray(reflected, hit_reflected) + (1 - R) * shade_new_ray(refracted, hit_refracted) +
                   R * Phong::shade(r, hit);
        }

        vec3 Glossy::shade_new_ray(Ray& r, HitInfo& hit) const {
            if (hit.has_hit) {
                Shader* shader = scene->shaders[hit.material.illum];
                return shader->shade(r, hit);
            }

            return tracer->get_scene().background;



        }




}