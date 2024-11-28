#define GL_SILENCE_DEPRECATION
#include <node_api.h>
#include <GLFW/glfw3.h>
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <cassert>

/** App Code */
#include "include/glfw_bindings.hpp"
#include "include/imgui_bindings.hpp"
#include "include/color_text_editor.h"
#include "include/imgui_image.h"
#include "include/imgui_functions.hpp"

namespace {
    /** Entry Point */
    napi_value Init(napi_env env, napi_value exports) {
        InitGLFWBindings(env, exports);
        InitImGuiBindings(env, exports);
        
        ColorTextEditor::Init(env, exports);
        ImGuiImage::Init(env, exports);

        /** Other */
        napi_property_descriptor desc[] = {       
            
        };

        /** Add ImGuiCol_Button */
        napi_value button;
        napi_create_int32(env, ImGuiCol_Button, &button);
        napi_set_named_property(env, exports, "imgui_ImGuiCol_Button", button);

        /** Add ImGuiCol_ButtonHovered */
        napi_value buttonHovered;
        napi_create_int32(env, ImGuiCol_ButtonHovered, &buttonHovered);
        napi_set_named_property(env, exports, "imgui_ImGuiCol_ButtonHovered", buttonHovered);

        /** Add ImGuiCol_ButtonActive */
        napi_value buttonActive;
        napi_create_int32(env, ImGuiCol_ButtonActive, &buttonActive);
        napi_set_named_property(env, exports, "imgui_ImGuiCol_ButtonActive", buttonActive);

        napi_define_properties(env, exports, sizeof(desc) / sizeof(*desc), desc);

        /** Expose ImGuiHoveredFlags_DelayShort */
        napi_value delayShortFlag;
        napi_create_int32(env, ImGuiHoveredFlags_DelayShort, &delayShortFlag);
        napi_set_named_property(env, exports, "imgui_HoveredFlags_DelayShort", delayShortFlag);

        /** Add PushFont */
        

        /** Add PopFont */
        napi_value popFontFn;
        napi_create_function(env, "imgui_popFont", NAPI_AUTO_LENGTH, im_gui::PopFont, nullptr, &popFontFn);
        napi_set_named_property(env, exports, "imgui_popFont", popFontFn);


        return exports;
    }

    NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
}