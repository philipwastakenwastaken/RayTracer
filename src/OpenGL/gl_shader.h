#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"


namespace trian {

    struct ShaderProgramSource {
        std::string vertex_source;
        std::string fragment_source;
    };

    class Shader {

    public:
        Shader(const std::string& file_path): file_path(file_path) {
            render_id = create_shader();
        }
        Shader() {}

        ~Shader();



        void bind() const;
        void unbind() const;

        void set_uniform1i(const std::string& name, int v1);
        void set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void set_uniform_mat4f(const std::string& name, const glm::mat4& matrix);

        inline const std::string& get_file_path() const {return file_path;}
        inline const unsigned get_render_id() const {return render_id;}

    private:
        unsigned render_id = 0;
        std::string file_path;
        std::unordered_map<std::string, int> uniform_location_cache;


        unsigned compile_shader(unsigned type, const std::string& src);
        unsigned create_shader();
        ShaderProgramSource parse_shader();
        int get_uniform_location(const std::string& name);


    };

}