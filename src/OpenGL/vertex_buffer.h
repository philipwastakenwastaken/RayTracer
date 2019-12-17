#pragma once

namespace trian {

    class VertexBuffer {

    public:
        VertexBuffer(const void* data, unsigned count, unsigned type_size);
        ~VertexBuffer();
        VertexBuffer();

        void bind() const;
        void unbind() const;

        inline unsigned get_render_id() const {return render_id;}
        inline unsigned get_count() const {return count;}

    private:
        unsigned render_id;
        unsigned count;
    };
}