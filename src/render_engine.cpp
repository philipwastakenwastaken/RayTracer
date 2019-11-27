#include "render_engine.h"
#include "math.h"

namespace trace {




    void RenderEngine::render() {


        file.open("image.ppm");

        file << "P3\n" << width << " " << height << "\n255\n";
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {

                vec3 col = tracer.compute_pixel(x, y);
                col.x = fminf(col.x, 1.0f);
                col.y = fminf(col.y, 1.0f);
                col.z = fminf(col.z, 1.0f);
                int ir = int(255.99 * col.x);
                int ig = int(255.99 * col.y);
                int ib = int(255.99 * col.z);
                file << ir << " " << ig << " " << ib << "\n";
            }
        }
        
        file.close();
    }




}