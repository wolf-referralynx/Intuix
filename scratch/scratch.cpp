#include <node_api.h>
#include "imgui.h"

// Helper macro for error checking
#define DECLARE_NAPI_METHOD(name, func)          \
    { name, 0, func, 0, 0, 0, napi_default, 0 }

// Helper function to create a string return value
napi_value CreateString(napi_env env, const char* str) {
    napi_value result;
    napi_create_string_utf8(env, str, NAPI_AUTO_LENGTH, &result);
    return result;
}

// Wrapper for ImGui::Begin
napi_value Begin(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (argc < 1) {
        napi_throw_type_error(env, nullptr, "Expected a string argument");
        return nullptr;
    }

    size_t str_size;
    napi_get_value_string_utf8(env, args[0], nullptr, 0, &str_size);
    char* buffer = new char[str_size + 1];
    napi_get_value_string_utf8(env, args[0], buffer, str_size + 1, nullptr);

    ImGui::Begin(buffer);
    delete[] buffer;

    return nullptr; // Return undefined
}

// Wrapper for ImGui::End
napi_value End(napi_env env, napi_callback_info info) {
    ImGui::End();
    return nullptr; // Return undefined
}

// Initialization function to define the module
napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor descriptors[] = {
        DECLARE_NAPI_METHOD("begin", Begin),
        DECLARE_NAPI_METHOD("end", End)
    };

    napi_define_properties(env, exports, sizeof(descriptors) / sizeof(*descriptors), descriptors);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
