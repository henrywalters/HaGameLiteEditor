cmake_minimum_required(VERSION 3.24)
project(HaGameLite)

# set(CMAKE_TOOLCHAIN_FILE /home/henry/emsdk/)
if(EMSCRIPTEN)
    MESSAGE("BUILDING FOR THE WEB")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
# pkg_search_module(GL REQUIRED gl)

set(IMGUI_PATH ${CMAKE_CURRENT_LIST_DIR}/thirdparty/imgui)
file(GLOB IMGUI_GLOB
        ${IMGUI_PATH}/imgui.h
        ${IMGUI_PATH}/imgui.cpp
        ${IMGUI_PATH}/imconfig.h
        ${IMGUI_PATH}/imgui_demo.cpp
        ${IMGUI_PATH}/imgui_draw.cpp
        ${IMGUI_PATH}/imgui_internal.h
        ${IMGUI_PATH}/imstb_rectpack.h
        ${IMGUI_PATH}/imstb_textedit.h
        ${IMGUI_PATH}/imstb_truetype.h
        ${IMGUI_PATH}/imgui_tables.cpp
        ${IMGUI_PATH}/imgui_widgets.cpp

        # specific bindings...
        ${IMGUI_PATH}/backends/imgui_impl_glfw.h
        ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
        ${IMGUI_PATH}/backends/imgui_impl_opengl3.h
        ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_PATH}/backends/imgui_impl_opengl3_loader.cpp)

add_library("imgui" STATIC ${IMGUI_GLOB})
target_include_directories("imgui" PUBLIC ${IMGUI_PATH})
target_link_libraries("imgui" PRIVATE glfw)


set(CMAKE_CXX_STANDARD 20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
MESSAGE("${CMAKE_CURRENT_LIST_DIR}")
find_package(HaGame2 REQUIRED)

add_executable(HaGameLite main.cpp src/mainMenu.h src/uiObject.h)
target_include_directories(HaGameLite PUBLIC ${HAGAME2_INCLUDE_DIR})
target_link_libraries(HaGameLite ${HAGAME2_LIBRARY})
target_link_libraries(HaGameLite ${GLFW_LIBRARIES})
target_link_libraries(HaGameLite ${OPENGL_LIBRARIES})
target_include_directories(HaGameLite PUBLIC ${IMGUI_PATH})
target_link_libraries(HaGameLite imgui)

# set(CMAKE_TOOLCHAIN_FILE /home/henry/emsdk/)
if(EMSCRIPTEN)
    set_target_properties(HaGameLite PROPERTIES LINK_FLAGS "-DCMAKE_EXE_LINKER_FLAGS=-s -sMAX_WEBGL_VERSION=2 --preload-file ../assets")
endif()