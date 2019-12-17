#include "vertex_array.h"


namespace trian {


    void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
        bind();
        vb.bind();
        const auto& elements = layout.get_elements();
        unsigned offset = 0;

        for (int i = 0; i < elements.size(); i++) {
            const auto& element = elements[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.count, element.type,
                                  element.normalized, layout.get_stride(), (const void*) offset);
            offset += element.count * VertexBufferElement::get_sizeof_type(element.type);
        }
    }

    void VertexArray::bind() const {
        glBindVertexArray(render_id);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }

}