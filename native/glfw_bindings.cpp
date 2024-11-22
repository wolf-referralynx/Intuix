#include "include/glfw_bindings.hpp"
#include "include/glfw_functions.hpp"

napi_value InitGLFWBindings(napi_env env, napi_value exports) {
    napi_property_descriptor glfw_desc[] = {
        {"glfw_init", nullptr, glfw::Init, nullptr, nullptr, nullptr, napi_default, nullptr}
        ,{"glfw_createWindow", nullptr, glfw::CreateWindow, nullptr, nullptr, nullptr, napi_default, nullptr}
        ,{"glfw_windowShouldClose", nullptr, glfw::WindowShouldClose, nullptr, nullptr, nullptr, napi_default, nullptr}
        ,{"glfw_setWindowTitle", 0, glfw::SetWindowTitle, 0, 0, 0, napi_default, 0}
        ,{"glfw_pollEvents", nullptr, glfw::PollEvents, nullptr, nullptr, nullptr, napi_default, nullptr}
        ,{"glfw_swapBuffers", nullptr, glfw::SwapBuffers, nullptr, nullptr, nullptr, napi_default, nullptr}
        ,{"glfw_terminate", nullptr, glfw::TerminateGLFW, nullptr, nullptr, nullptr, napi_default, nullptr}
        ,{"glfw_getFramebufferSize", 0, glfw::GetFramebufferSize, 0, 0, 0, napi_default, 0}
        ,{"glfw_setViewport", 0, glfw::SetViewport, 0, 0, 0, napi_default, 0}
        ,{"glfw_setClearColor", 0, glfw::SetClearColor, 0, 0, 0, napi_default, 0}
        ,{"glfw_glClear", 0, glfw::Clear, 0, 0, 0, napi_default, 0}
        ,{"glfw_renderDrawData", 0, glfw::RenderDrawData, 0, 0, 0, napi_default, 0}
    };
    napi_define_properties(env, exports, sizeof(glfw_desc) / sizeof(*glfw_desc), glfw_desc);
    return exports;
}