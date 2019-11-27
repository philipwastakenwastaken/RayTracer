#include "scene.h"
#include <limits>


namespace trace {

    bool Scene::closest_hit(const Ray& r, HitInfo& hit) const {

        // loop through all primitives and check for intersections
        // save the closest intersection (if any)

        HitInfo temp_hit;
        hit.dist = r.tmax;
        bool hit_anything = false;

        for (const Primitive* prim : primitives) {


            if (prim->intersect(r, temp_hit)) {
                hit_anything = true;

                if (temp_hit.dist < hit.dist) {
                    hit = temp_hit;
                }
            }

        }

        return hit_anything;
    }

    bool Scene::any_hit(const Ray& r, HitInfo& hit) const {
        for (const Primitive* prim : primitives) {
            if (prim->intersect(r, hit)) {
                return true;
            }
        }
        return false;
    }







}