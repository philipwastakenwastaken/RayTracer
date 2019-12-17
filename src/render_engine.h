#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ray_tracer.h"
#include <fstream>
#include <cassert>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace trace {


    class RenderEngine {

        public:
        RenderEngine() {

            if (!glfwInit()) {
                assert(0);
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


            window = glfwCreateWindow(width, height, "Ray Tracer", NULL, NULL);

            if (!window) {
                std::cout << "Could not intialize glfw window\n";
                glfwTerminate();
                assert(0);
            }

            glfwMakeContextCurrent(window);
            glfwSwapInterval(1);

            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                std::cout << "Could not intialize glad\n";
                assert(0);
            }

            glViewport(0, 0, width, height);


            proj = glm::ortho(0.0f, (float) width, 0.0f, (float) height, -1.0f, 1.0f);

        }

        ~RenderEngine() {
            glfwTerminate();
        }

        static const unsigned width  = 800;
        static const unsigned height = 400;
        std::ofstream file;
        vec3 img[width][height];


        void render();
        void write_to_file();
        void draw_to_screen();
        void gl_check_error();
        void tile_render(int start_x, int start_y, int end_x, int end_y);
        RayTracer tracer;
        GLFWwindow* window;
        glm::mat4 proj;


    };









}