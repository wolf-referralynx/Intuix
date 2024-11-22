cmake_minimum_required(VERSION 3.31.0)

cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0042 NEW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

project (intuix)

add_definitions(-DNAPI_VERSION=7)

# GLFW
include(FetchContent)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw) 
FetchContent_MakeAvailable(glfw)

# FMT
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt)
FetchContent_MakeAvailable(fmt)

# IMGUI
set(IMGUI_HEADERS
    deps/imgui/imconfig.h
    deps/imgui/imgui_internal.h
    deps/imgui/imgui.h
    deps/imgui/imstb_rectpack.h
    deps/imgui/imstb_textedit.h
    deps/imgui/imstb_truetype.h    
    deps/imgui/backends/imgui_impl_glfw.h
    deps/imgui/backends/imgui_impl_opengl3.h
    deps/imgui/backends/imgui_impl_opengl3_loader.h
    deps/imgui/misc/cpp/imgui_stdlib.h
)

set(IMGUI_SRC
    deps/imgui/imgui_demo.cpp
    deps/imgui/imgui_draw.cpp
    deps/imgui/imgui_tables.cpp
    deps/imgui/imgui_widgets.cpp
    deps/imgui/imgui.cpp
    deps/imgui/backends/imgui_impl_glfw.cpp
    deps/imgui/backends/imgui_impl_opengl3.cpp
    deps/imgui/misc/cpp/imgui_stdlib.cpp
)

add_library(imgui ${IMGUI_HEADERS} ${IMGUI_SRC})
target_link_libraries(imgui PUBLIC glfw)
target_compile_definitions(imgui PRIVATE IMGUI_DLL_EXPORT)
include_directories(deps/imgui/ deps/imgui/examples deps/imgui/examples/libs/gl3w deps/imgui/backends deps/imgui/misc/cpp)

# IMPLOT
set(IMPLOT_HEADERS deps/implot/implot.h deps/implot/implot_internal.h)
set(IMPLOT_SRC     deps/implot/implot.cpp deps/implot/implot_items.cpp deps/implot/implot_demo.cpp) 

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/deps/implot/backends")
list(APPEND IMPLOT_HEADERS deps/implot/backends/implot_backend.h deps/implot/backends/implot_impl_opengl3.h)
list(APPEND IMPLOT_SRC deps/implot/backends/implot_backend.h deps/implot/backends/implot_impl_opengl3.cpp)
endif()

add_library(implot ${IMPLOT_HEADERS} ${IMPLOT_SRC})
target_link_libraries(implot PUBLIC imgui)
target_compile_definitions(implot PUBLIC IMPLOT_DEBUG IMPLOT_DLL_EXPORT IMPLOT_BACKEND_ENABLE_OPENGL3)
include_directories(deps/implot/)

# INTUIX
include_directories(${CMAKE_JS_INC})

file(GLOB SOURCE_FILES 
        "./native/*.cpp" 
        "./native/fonts/*.cpp" 
        "./native/*.h" 
        "./native/fonts/*.h"
    )

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} glfw imgui implot)

# https://github.com/haruneko/cmake-js-example/blob/main/package.json
# https://github.com/cmake-js/cmake-js