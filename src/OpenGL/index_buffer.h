#pragma once

namespace trian {

    class IndexBuffer {

    public:
        IndexBuffer(const unsigned* data, unsigned count);
        ~IndexBuffer();
        IndexBuffer() = default;

        void bind() const;
        void unbind() const;

        inline unsigned get_count() const {return count;}
        inline unsigned get_render_id() const {return render_id;}

    private:
        unsigned render_id;
        unsigned count;
    };
}