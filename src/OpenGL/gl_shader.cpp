#include <glad/glad.h>

#include "gl_shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace trian {


    Shader::~Shader() {
        glDeleteProgram(render_id);
    }

    void Shader::bind() const {
        glUseProgram(render_id);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }

    void Shader::set_uniform1i(const std::string& name, int v1) {
        glUniform1i(get_uniform_location(name), v1);
    }

    void Shader::set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
        glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
    }

    void Shader::set_uniform_mat4f(const std::string & name, const glm::mat4& matrix) {
        glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
    }

    int Shader::get_uniform_location(const std::string& name) {
        
        std::unordered_map<std::string, int>::const_iterator it = uniform_location_cache.find(name);
        if (it != uniform_location_cache.end()) {
            return it->second;
        }

        int location = glGetUniformLocation(render_id, name.c_str());
        if (location == -1) {
            std::cout << "Uniform " << name << " does not exist!" << std::endl;
        }
        uniform_location_cache[name] = location;
        return location;
    }


    unsigned Shader::create_shader() {
        ShaderProgramSource source = parse_shader();

        unsigned vertex_shader = compile_shader(GL_VERTEX_SHADER, source.vertex_source);
        unsigned fragment_shader = compile_shader(GL_FRAGMENT_SHADER, source.fragment_source);

        unsigned shader_program = glCreateProgram();

        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);
        glLinkProgram(shader_program);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return shader_program;
    }

    unsigned Shader::compile_shader(unsigned type, const std::string& source) {
        unsigned id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // error handling
        int success;
        char info_log[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        if (!success) {
            std::cout << "Shader compilation failed\n";
            glGetShaderInfoLog(id, 512, NULL, info_log);
            std::cout << info_log << std::endl;
            __debugbreak();
            exit(1);
        }

        std::cout << "Shader compilation success\n";

        return id;
    }

    ShaderProgramSource Shader::parse_shader() {
        std::ifstream stream(file_path);

        enum class ShaderType {
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;
        while (getline(stream, line)) {
            if (line.find("#shader") != std::string::npos) {

                if (line.find("vertex") != std::string::npos) {
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos) {
                    type = ShaderType::FRAGMENT;
                }
            }
            else {
                ss[(int) type] << line << '\n';
            }
        }

    return {ss[0].str(), ss[1].str()};

}


}