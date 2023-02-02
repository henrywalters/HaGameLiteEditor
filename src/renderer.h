//
// Created by henry on 1/11/23.
//

#ifndef HAGAMELITEEDITOR_RENDERER_H
#define HAGAMELITEEDITOR_RENDERER_H

#include "hagame/graphics/renderPipeline.h"
#include "hagame/math/collisions.h"

using namespace hg;
using namespace hg::graphics;
using namespace hg::math;

class Renderer : public RenderPipeline {
public:
    void clear() override {

    }

    void render(Vec2i size) override {

        std::vector<Color> pixels;

        theta += 0.1;

        Vec3 lightPos = Vec3(sin(theta) * 3, 1, cos(theta) * 3);

        utils::Random rand;

        float aspect = (float) size[0] / (float) size[1];

        for (int i = 0; i < size[1]; i++) {
            for (int j = 0; j < size[0]; j++) {

                float x = (float) (j - size[0] * 0.5) / (float) (size[0] * 2) * aspect;
                float y = (float) (i - size[1] * 0.5) / (float) (size[1] * 2);

                Vec3 dir(x, y, 1.0f);

                Color color = Color::white();

                float t;

                auto hit = collisions::checkRayAgainstSphere(
                    Ray(Vec3(0, 0, -5), dir.normalized() * 1000),
                    Sphere(Vec3::Zero(), 0.5),
                    t
                );

                if (hit.has_value()) {
                    color = Color::red();
                    color[0] *= dot((hit->position - lightPos).normalized(), hit->normal);
                }

                pixels.push_back(color);
            }
        }

        m_texture = std::make_unique<RawTexture<GL_RGBA>>(size, (float*) pixels.data());
    }

    void cleanup() override {

    }

    virtual RawTexture<GL_RGBA>* outputTexture() override {
        return m_texture.get();
    }

private:

    std::unique_ptr<RawTexture<GL_RGBA>> m_texture;

    float theta = 0;
};

#endif //HAGAMELITEEDITOR_RENDERER_H
