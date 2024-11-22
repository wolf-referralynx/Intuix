#include <node_api.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* window = nullptr;

// Initialize GLFW
napi_value InitGLFW(napi_env env, napi_callback_info info) {
    if (!glfwInit()) {
        napi_throw_error(env, nullptr, "Failed to initialize GLFW");
        return nullptr;
    }
    return nullptr; // Return undefined
}

// Create a window
napi_value CreateWindow(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (argc < 2) {
        napi_throw_type_error(env, nullptr, "Expected width and height as arguments");
        return nullptr;
    }

    int width, height;
    napi_get_value_int32(env, args[0], &width);
    napi_get_value_int32(env, args[1], &height);

    // Create a GLFW window
    window = glfwCreateWindow(width, height, "ImGui + GLFW + Node.js", nullptr, nullptr);
    if (!window) {
        napi_throw_error(env, nullptr, "Failed to create GLFW window");
        glfwTerminate();
        return nullptr;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);
    return nullptr; // Return undefined
}

// Check if the window should close
napi_value WindowShouldClose(napi_env env, napi_callback_info info) {
    napi_value result;
    napi_get_boolean(env, window && glfwWindowShouldClose(window), &result);
    return result;
}

// Poll events
napi_value PollEvents(napi_env env, napi_callback_info info) {
    glfwPollEvents();
    return nullptr;
}

// Swap buffers
napi_value SwapBuffers(napi_env env, napi_callback_info info) {
    if (window) {
        glfwSwapBuffers(window);
    }
    return nullptr;
}

// Terminate GLFW
napi_value TerminateGLFW(napi_env env, napi_callback_info info) {
    glfwTerminate();
    return nullptr;
}

// Export the functions to JavaScript
napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"initGLFW", nullptr, InitGLFW, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createWindow", nullptr, CreateWindow, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"windowShouldClose", nullptr, WindowShouldClose, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"pollEvents", nullptr, PollEvents, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"swapBuffers", nullptr, SwapBuffers, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"terminateGLFW", nullptr, TerminateGLFW, nullptr, nullptr, nullptr, napi_default, nullptr}
    };

    napi_define_properties(env, exports, sizeof(desc) / sizeof(*desc), desc);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
