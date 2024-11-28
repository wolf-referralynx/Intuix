#ifndef IMGUI_FUNCTIONS_H
#define IMGUI_FUNCTIONS_H

#include <node_api.h>
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

namespace im_gui {
    /* Backend */
    napi_value ImplOpenGL3_NewFrame(napi_env env, napi_callback_info info);
    napi_value ImplGlfw_NewFrame(napi_env env, napi_callback_info info);
    napi_value NewFrame(napi_env env, napi_callback_info info);
    napi_value ShowDemoWindow(napi_env env, napi_callback_info info);
    napi_value Render(napi_env env, napi_callback_info info);
    napi_value GetDrawData(napi_env env, napi_callback_info info);
    napi_value ImplOpenGL3_RenderDrawData(napi_env env, napi_callback_info info);

    /* GUI */
    napi_value Begin(napi_env env, napi_callback_info info);
    napi_value End(napi_env env, napi_callback_info info);
    napi_value Button(napi_env env, napi_callback_info info);
    napi_value PushStyleColor(napi_env env, napi_callback_info info);
    napi_value PopStyleColor(napi_env env, napi_callback_info info);
    napi_value InputTextMultiline(napi_env env, napi_callback_info info);
    napi_value InputText(napi_env env, napi_callback_info info);
    napi_value Text(napi_env env, napi_callback_info info);
    napi_value TextDisabled(napi_env env, napi_callback_info info);
    napi_value IsItemHovered(napi_env env, napi_callback_info info);
    napi_value BeginTooltip(napi_env env, napi_callback_info info);
    napi_value EndTooltip(napi_env env, napi_callback_info info);
    napi_value PushTextWrapPos(napi_env env, napi_callback_info info);
    napi_value GetFontSize(napi_env env, napi_callback_info info);
    napi_value TextUnformatted(napi_env env, napi_callback_info info);
    napi_value PopTextWrapPos(napi_env env, napi_callback_info info);
    napi_value SameLine(napi_env env, napi_callback_info info);
    napi_value SmallButton(napi_env env, napi_callback_info info);
    napi_value PushFont(napi_env env, napi_callback_info info);
    napi_value PopFont(napi_env env, napi_callback_info info);
}


#endif // IMGUI_FUNCTIONS_H