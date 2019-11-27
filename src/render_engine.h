#pragma once

#include "ray_tracer.h"
#include <fstream>

namespace trace {


    class RenderEngine {

        unsigned width  = 1600;
        unsigned height = 800;
        std::ofstream file;

        public:

        void render();
        RayTracer tracer;


    };









}