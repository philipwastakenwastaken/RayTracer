#include <iostream>
#include <fstream>

#include "ray.h"
#include "primitives.h"
#include "render_engine.h"

trace::vec3 color(const trace::Ray& r) {
    trace::Sphere sphere(trace::vec3(0, 0, -1), 0.5);
    trace::HitInfo hit;

    if (sphere.intersect(r, hit)) {
        return 0.5 * trace::vec3(hit.shading_normal.x + 1, 
                                 hit.shading_normal.y + 1,
                                 hit.shading_normal.z + 1);
    }
    float t = 0.5*(r.direction.y + 1.0);
    return ((1.0 - t) * trace::vec3(1.0, 1.0, 1.0)) + (t * trace::vec3(0.5, 0.7, 1.0));
}

int main() {
    trace::RenderEngine* engine = new trace::RenderEngine();
    
    trace::Scene& scene = engine->tracer.get_scene();

    trace::Sphere s1(trace::vec3(-1.0, 0.0, -1.0f), 0.25);

    trace::Material m;
    m.ambient[0] = 0.2f;
    m.ambient[1] = 0.1f;
    m.ambient[2] = 0.1f;
    m.ambient[3] = 1.0f;

    m.diffuse[0] = 1.0f;
    m.diffuse[1] = 0.0f;
    m.diffuse[2] = 0.0f;
    m.diffuse[3] = 1.0f;
    m.illum = 1;
    s1.material = m;

    trace::Sphere s3(trace::vec3(1.0, 0.0, -1.0f), 0.25);

    trace::Material m3;
    m3.ambient[0] = 0.3f;
    m3.ambient[1] = 0.1f;
    m3.ambient[2] = 0.1f;
    m3.ambient[3] = 1.0f;

    m3.diffuse[0] = 0.3f;
    m3.diffuse[1] = 0.7f;
    m3.diffuse[2] = 0.2f;
    m3.diffuse[3] = 1.0f;
    m3.illum = 1;
    s3.material = m3;

    trace::Sphere s2(trace::vec3(0.0, -100.5, -1.0), 100.0);
    trace::Material m2;
    m2.ambient[0] = 0.1f;
    m2.ambient[1] = 0.2f;
    m2.ambient[2] = 0.1f;
    m2.ambient[3] = 1.0f;
    
    m2.diffuse[0] = 1.0f;
    m2.diffuse[1] = 0.0f;
    m2.diffuse[2] = 0.0f;
    m2.diffuse[3] = 1.0f;
    m2.illum = 0;
    s2.material = m2;

    trace::vec3 i(8.0f);
    trace::vec3 pos(-1.0f, 1.5f, -1.0f);
    trace::PointLight light(&engine->tracer, i, pos);


    scene.add_primitive(s1);
    scene.add_primitive(s2);
    scene.add_primitive(s3);
    scene.add_light(light);

    scene.shaders[0]->tracer = &engine->tracer;
    scene.shaders[1]->tracer = &engine->tracer;

    scene.shaders[0]->scene = &scene;
    scene.shaders[1]->scene = &scene;

    engine->render();


    system("pause");

    return 0;
}