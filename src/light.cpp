#include "light.h"
#include "ray_tracer.h"


namespace trace {

        bool PointLight::sample(const vec3& hit_pos, vec3& dir, vec3& L) const {
            vec3 ray_dir = pos - hit_pos;
            float ray_length = ray_dir.length();
            HitInfo shadow_hit;
            Ray shadow_ray(hit_pos, normalize(ray_dir), EPSILON, ray_length);
            dir = shadow_ray.direction;

            if (tracer->get_scene().any_hit(shadow_ray, shadow_hit)) {
                return false;

            }

            // if we didnt hit anything, we are not in shadow
            L = intensity / (ray_length * ray_length);
            return true;
        }


}
