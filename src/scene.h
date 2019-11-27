#pragma once

#include <vector>

#include "primitives.h"
#include "shader.h"
#include "camera.h"
#include "light.h"

namespace trace {


    class Scene {

        public:

        Scene() {
            shader = new Glossy(&lights);
            shaders.push_back(new Phong(&lights));
            shaders.push_back(new Glossy(&lights));
        }

        ~Scene() {
            delete shader;
            shader = nullptr;
        }

        inline void add_primitive(Primitive& prim) {primitives.push_back(&prim);}
        inline void add_light(Light& light) {lights.push_back(&light);}
        inline const Camera& get_camera() const {return cam;}


        Shader* shader;

        bool closest_hit(const Ray& r, HitInfo& hit) const;
        bool any_hit(const Ray& r, HitInfo& hit) const;

        vec3 background = vec3(0.5f, 0.7f, 1.0f); // color of background
        std::vector<Shader*> shaders;

        private:
        std::vector<Primitive*> primitives;
        std::vector<Light*> lights;
        Camera cam;



    };












}