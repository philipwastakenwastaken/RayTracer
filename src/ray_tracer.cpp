#include "ray_tracer.h"
#include "rt_random.h"

namespace trace {


    vec3 RayTracer::compute_pixel(int x, int y) {
        int NUM_SAMPLES = 100;

        vec3 col(0.0f);


        // trace a ray toward the pixel from the camera
        HitInfo hit;

        for (int i = 0; i < NUM_SAMPLES; i++) {
            float u = float(x + mt_random()) / float(width);
            float v = float(y + mt_random()) / float(height);
            const Ray r = scene.get_camera().get_ray(u, v);

            if (scene.closest_hit(r, hit)) {
                Shader* shader = scene.shaders[hit.material.illum];
                col += shader->shade(r, hit);
            }
            else {
                col += scene.background;
            }

        }


        return col / NUM_SAMPLES;
    }



        bool RayTracer::trace_reflected(const Ray& r_in, const HitInfo& in_hit, Ray& r_out, HitInfo& out_hit) const {

            vec3 omega_i = -normalize(r_in.direction);

            float cos_theta = dot(omega_i, in_hit.shading_normal);
            auto omega_r = 2 * cos_theta * in_hit.shading_normal - omega_i;

            r_out.direction = omega_r;
            r_out.origin = in_hit.position;
            r_out.tmin = 0.0001f;
            r_out.tmax = DEFAULT_TMAX;


            scene.closest_hit(r_out, out_hit);

            out_hit.ray_ior = in_hit.ray_ior;
            out_hit.trace_depth = in_hit.trace_depth + 1;

            if (out_hit.has_hit) {
                return true;
            }

            return false;

        }

        bool RayTracer::trace_refracted(const Ray& r_in, const HitInfo& in_hit, Ray& r_out, HitInfo& out_hit, float& R) const {
            R = 0.9f;


            vec3 non_const_g_normal = in_hit.shading_normal;
            float ior_out = get_ior_out(r_in, in_hit, non_const_g_normal);

            vec3 omega_i = -normalize(r_in.direction);
            float cos_theta_i = dot(omega_i, non_const_g_normal);
            float sin_sq_theta_i = 1 - (cos_theta_i * cos_theta_i);
            float sin_theta_i = sqrt(sin_sq_theta_i);

            float ior_ratio = in_hit.ray_ior / ior_out;
            float sin_theta_t = ior_ratio * sin_theta_i;

            float cos_sq_theta_t = 1 - (ior_ratio * ior_ratio) * (1 - (cos_theta_i * cos_theta_i));

            if (cos_sq_theta_t < 0) {
                return false;
            }

            vec3 t = (cos_theta_i * non_const_g_normal - omega_i) / sin_theta_i;

            vec3 omega_t = t * sin_theta_t - non_const_g_normal * sqrt(cos_sq_theta_t);

            r_out.direction = omega_t;
            r_out.origin = in_hit.position;

            r_out.tmin = 0.0001f;
            r_out.tmax = DEFAULT_TMAX;

            scene.closest_hit(r_out, out_hit);

            out_hit.ray_ior = ior_out;
            out_hit.trace_depth = in_hit.trace_depth + 1;
            if (out_hit.has_hit) {
                return true;
            }

            return false;


        }

        float RayTracer::get_ior_out(const Ray& r_in, const HitInfo& in_hit, vec3& normal) const {
            normal = in_hit.shading_normal;
            if (dot(normal, r_in.direction) > 0.0f) {
                normal = -normal;
                return 1.0f;
            }

            return in_hit.material.ior;

        }

}