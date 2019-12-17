#include "render_engine.h"
#include <math.h>
#include <chrono>
#include <thread>
#include <vector>
#include <functional>
#include <sstream>

#include "OpenGL/vertex_array.h"
#include "OpenGL/index_buffer.h"
#include "OpenGL/gl_shader.h"


namespace trace {


    using namespace trian;

    void RenderEngine::gl_check_error() {
        while (GLenum error = glGetError()) {
            std::cout << "[OpenGL Error] (" << error << ")\n";
        }
    }

    void RenderEngine::render() {

        unsigned num_threads = std::thread::hardware_concurrency() * 2;
        std::vector<std::thread*> threads;

        unsigned width_step = width / num_threads;
        unsigned height_step = height / num_threads;


        std::cout << "Rendering image with resolution " << width << "x" << height << std::endl;

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        int width_acc = 0;
        int height_acc = 0;
        for (unsigned i = 0; i < num_threads - 1; i++) {
            std::thread* t = new std::thread(std::bind(&RenderEngine::tile_render, this, width_acc, height_acc, width_acc + width_step, height_acc + height_step));
            threads.push_back(t);

            width_acc += width_step;
            height_acc += height_acc;
        }
        std::thread* t = new std::thread(std::bind(&RenderEngine::tile_render, this, width_acc, height_acc, width, height));
        threads.push_back(t);

        for (auto& t : threads) {
            t->join();
        }
        //write_to_file();
        draw_to_screen();
        
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::cout << "Rendering time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0 << " s" << std::endl;
    }

    void RenderEngine::tile_render(int start_x, int start_y, int end_x, int end_y) {
        std::stringstream msg;
        msg << "Rendering from " << start_x << ", " << start_y << " to " << end_x << ", " << end_y << "\n";
        std::cout << msg.str();

        for (int y = 0; y < height; y++) {
            for (int x = start_x; x < end_x; x++) {

                vec3 col = tracer.compute_pixel(x, y);
                col.x = fminf(col.x, 1.0f);
                col.y = fminf(col.y, 1.0f);
                col.z = fminf(col.z, 1.0f);
                img[x][y] = col;
            }
        }

    }

    void RenderEngine::draw_to_screen() {

        /*
        float vertices[] = {
            0.0f, 0.0f, 0.0f,
            100.0f, 0.0f, 0.0f,
            100.0f, 100.0f, 0.0f
        };


        VertexBuffer vbo(vertices, 9, sizeof(float));
        VertexBufferLayout layout;
        layout.push<float>(3);

        trian::VertexArray vao;
        vao.add_buffer(vbo, layout);

        unsigned indices[]{
            0, 1, 2
        };
        IndexBuffer ibo(indices, 3);
        */




        float* vert = new float[height * width * 6];

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int index = (x + y * width) * 6;
                vert[index] = x;
                vert[index + 1] = y;
                vert[index + 2] = 0.0f;
                vec3 col = img[x][y];
                vert[index + 3] = col.x;
                vert[index + 4] = col.y;
                vert[index + 5] = col.z;
            }
        }

        VertexBuffer vbo(vert, height * width * 6, sizeof(float));
        VertexBufferLayout layout;
        layout.push<float>(3);
        layout.push<float>(3);
        trian::VertexArray vao;
        vao.add_buffer(vbo, layout);

        vao.bind();
        trian::Shader shader("shaders/color.shader");
        shader.bind();


        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        shader.set_uniform_mat4f("proj", proj);
        //glDrawElements(GL_TRIANGLES, ibo.get_count(), GL_UNSIGNED_INT, nullptr);
        glDrawArrays(GL_POINTS, 0, height * width);
        glfwSwapBuffers(window);

        while (1) {
            glfwWaitEvents();
        }

        gl_check_error();

        delete[] vert;

    }



    void RenderEngine::write_to_file() {

        file.open("image.ppm");
        file << "P3\n" << width << " " << height << "\n255\n";
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                vec3 col = img[x][y];

                int ir = int(255.99 * col.x);
                int ig = int(255.99 * col.y);
                int ib = int(255.99 * col.z);
                file << ir << " " << ig << " " << ib << "\n";


            }
        }
        file.close();


    }


}