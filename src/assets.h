//
// Created by henry on 1/11/23.
//

#ifndef HAGAMELITEEDITOR_ASSETS_H
#define HAGAMELITEEDITOR_ASSETS_H

#include <string>

#include "hagame/utils/store.h"
#include "hagame/graphics/shaderProgram.h"

#ifdef __EMSCRIPTEN__
const std::string ASSET_DIR = "./assets/";
#else
const std::string ASSET_DIR = "../assets/";
#endif

static hg::utils::Store<hg::graphics::ShaderProgram*> SHADERS;

#endif //HAGAMELITEEDITOR_ASSETS_H
