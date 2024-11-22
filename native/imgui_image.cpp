#include "include/imgui_image.h"
#include <iostream>

// Initialize the module
napi_value ImGuiImage::Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc = { 
        "imgui_image", 0, RenderImage, 0, 0, 0, napi_default, 0 
    };

    napi_status status = napi_define_properties(env, exports, 1, &desc);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to define properties for ImGuiImage");
    }

    return exports;
}

// Render ImGui::Image
napi_value ImGuiImage::RenderImage(napi_env env, napi_callback_info info) {
    size_t argc = 3; // textureID, width/height (ImVec2), and optional UV coords
    napi_value args[3];
    napi_value thisArg;

    napi_status status = napi_get_cb_info(env, info, &argc, args, &thisArg, nullptr);
    if (status != napi_ok || argc < 2) {
        napi_throw_error(env, nullptr, "Invalid arguments for ImGui::Image");
        return nullptr;
    }

    // Extract texture ID
    void* textureID = GetTextureID(env, args[0]);
    if (!textureID) {
        napi_throw_error(env, nullptr, "Invalid texture ID");
        return nullptr;
    }

    // Extract size as ImVec2
    ImVec2 size = GetImVec2(env, args[1]);

    // Optional UV coordinates (default to full texture)
    ImVec2 uv0(0.0f, 0.0f), uv1(1.0f, 1.0f);
    if (argc >= 3) {
        uv0 = GetImVec2(env, args[2]);
    }

    // Render the image using ImGui
    try {
        ImGui::Image(textureID, size, uv0, uv1);
    } catch (const std::exception& e) {
        napi_throw_error(env, nullptr, e.what());
        return nullptr;
    }

    return nullptr;
}

// Utility to extract a texture ID from a JavaScript value
void* ImGuiImage::GetTextureID(napi_env env, napi_value value) {
    void* textureID = nullptr;
    napi_status status = napi_get_value_external(env, value, &textureID);
    return status == napi_ok ? textureID : nullptr;
}

// Utility to extract ImVec2 from a JavaScript object
ImVec2 ImGuiImage::GetImVec2(napi_env env, napi_value value) {
    napi_value xVal, yVal;
    double x, y;

    napi_status status = napi_get_named_property(env, value, "x", &xVal);
    if (status == napi_ok) {
        napi_get_value_double(env, xVal, &x);
    }

    status = napi_get_named_property(env, value, "y", &yVal);
    if (status == napi_ok) {
        napi_get_value_double(env, yVal, &y);
    }

    return ImVec2(static_cast<float>(x), static_cast<float>(y));
}
