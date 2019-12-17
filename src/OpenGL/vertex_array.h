#pragma once

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include <glad/glad.h>


namespace trian {

    class VertexArray {

    public:
        VertexArray() {
            glGenVertexArrays(1, &render_id);
        }

        ~VertexArray() {
            glDeleteVertexArrays(1, &render_id);
        }

        void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

        void bind() const;
        void unbind() const;

        inline unsigned get_render_id() const {return render_id;}
    private:
        unsigned render_id = 0;


    };

}