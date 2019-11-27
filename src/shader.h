#pragma once


#include "vec3.h"
#include "ray.h"
#include "light.h"
#include <vector>
#include <math.h>

namespace trace {

    class RayTracer;
    class Scene;

    class Shader {

        public:
        Shader(std::vector<Light*>* lights): lights(lights) {}
        virtual vec3 shade(const Ray& r, const HitInfo& hit) const {
            return vec3(hit.material.ambient[0], hit.material.ambient[1], hit.material.ambient[2]);
        }

        virtual ~Shader() = default;

        std::vector<Light*>* lights;
        RayTracer* tracer;
        Scene* scene;
        unsigned max_trace_depth = 10;
    };

    class Lambertian: public Shader {

        public:
        Lambertian(std::vector<Light*>* lights): Shader(lights) {}

        virtual vec3 shade(const Ray& r, const HitInfo& hit) const override {
            vec3 rho_d(hit.material.diffuse[0], hit.material.diffuse[1], hit.material.diffuse[2]);
            vec3 result(0.0f);

            for (const Light* light : *lights) {
                vec3 acc_light(0.0f);

                for (int i = 0; i < light->number_of_samples; i++) {

                    vec3 dir, L;
                    if (light->sample(hit.position, dir, L)) {

                        float cos_angle = dot(hit.shading_normal, dir);
                        if (cos_angle > 0) {
                            acc_light += L * cos_angle;
                        }

                    }

                }

                result += acc_light / light->number_of_samples;

            }


            return result * rho_d * M_1_PIf + Shader::shade(r, hit);
        }

    };

    class Phong: public Shader {

        public:
        Phong(std::vector<Light*>* lights): Shader(lights) {}

        virtual vec3 shade(const Ray& r, const HitInfo& hit) const override {
            vec3 rho_d(hit.material.diffuse[0], hit.material.diffuse[1], hit.material.diffuse[2]);
            vec3 rho_s = vec3(0.2f, 0.8f, 0.2f);
            float s = 3;


            vec3 result(0.0f);

            for (const Light* light : *lights) {
                vec3 acc_light(0.0f);

                for (int i = 0; i < light->number_of_samples; i++) {

                    vec3 dir, L;
                    if (light->sample(hit.position, dir, L)) {

                        float cos_angle = dot(hit.shading_normal, dir);
                        if (cos_angle > 0) {
                            vec3 omega_r = 2 * cos_angle * hit.shading_normal - dir;
                            acc_light += (rho_d * M_1_PIf + rho_s * (s + 2) * M_2_PIf *
                            (powf(fmaxf(dot(-r.direction, omega_r), 0), s))) * L * cos_angle;
                        }

                    }

                }

                result += acc_light / light->number_of_samples;

            }


            return result * rho_d * M_1_PIf + Shader::shade(r, hit);
        }

    };

    class Glossy: public Phong {

        public:
        Glossy(std::vector<Light*>* lights): Phong(lights) {}
        virtual vec3 shade(const Ray& r, const HitInfo& hit) const override;
        vec3 shade_new_ray(Ray& r, HitInfo& hit) const;


    };

}