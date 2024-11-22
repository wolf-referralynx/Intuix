#ifndef IMGUI_IMAGE_H
#define IMGUI_IMAGE_H

#include <node_api.h>
#include "imgui.h" // Ensure ImGui is included

class ImGuiImage {
public:
    static napi_value Init(napi_env env, napi_value exports);
    static napi_value RenderImage(napi_env env, napi_callback_info info);

private:
    // Utility to validate and convert inputs
    static void* GetTextureID(napi_env env, napi_value value);
    static ImVec2 GetImVec2(napi_env env, napi_value value);
};

#endif // IMGUI_IMAGE_H
