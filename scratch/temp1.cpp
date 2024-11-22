#include <napi.h>
#include <GLFW/glfw3.h>

// Create a GLFW window and return it as an external pointer
napi_value CreateWindow(napi_env env, napi_callback_info info) {
    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "My Window", nullptr, nullptr);
    if (!window) {
        napi_throw_error(env, nullptr, "Failed to create GLFW window");
        return nullptr;
    }

    // Wrap the GLFWwindow pointer in a napi_value
    napi_value jsWindow;
    napi_status status = napi_create_external(env, window, nullptr, nullptr, &jsWindow);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to create external pointer");
        return nullptr;
    }

    // Return the external pointer to JavaScript
    return jsWindow;
}
