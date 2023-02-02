//
// Created by henry on 1/11/23.
//

#ifndef HAGAMELITEEDITOR_RENDERABLE_H
#define HAGAMELITEEDITOR_RENDERABLE_H

#include <concepts>
#include "hagame/graphics/shaderProgram.h"
#include "hagame/graphics/mesh.h"

struct Renderable {
    hg::graphics::ShaderProgram* shader;
    hg::graphics::MeshInstance* mesh;
};

template<typename T>
concept IsRenderable = std::is_base_of<Renderable, T>::value;


#endif //HAGAMELITEEDITOR_RENDERABLE_H
