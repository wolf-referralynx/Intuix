#include "include/imgui_bindings.hpp"
#include "include/imgui_functions.hpp"

napi_value InitImGuiBindings(napi_env env, napi_value exports){
    napi_property_descriptor imgui_desc[] = {
        /* Backend */
        {"imgui_implOpenGL3NewFrame", 0, im_gui::ImplOpenGL3_NewFrame, 0, 0, 0, napi_default, 0}
        ,{"imgui_implGlfw_NewFrame", 0, im_gui::ImplGlfw_NewFrame, 0, 0, 0, napi_default, 0}
        ,{"imgui_newFrame", 0, im_gui::NewFrame, 0, 0, 0, napi_default, 0}
        ,{"imgui_showDemoWindow", 0, im_gui::ShowDemoWindow, 0, 0, 0, napi_default, 0}
        ,{"imgui_render", 0, im_gui::Render, 0, 0, 0, napi_default, 0}
        ,{"imgui_getDrawData", 0, im_gui::GetDrawData, 0, 0, 0, napi_default, 0}
        ,{"imgui_implOpenGL3_RenderDrawData", 0, im_gui::ImplOpenGL3_RenderDrawData, 0, 0, 0, napi_default, 0}

        /* GUI */
        ,{"imgui_begin", 0, im_gui::Begin, 0, 0, 0, napi_default, 0}
        ,{"imgui_end", 0, im_gui::End, 0, 0, 0, napi_default, 0}
        ,{"imgui_button", 0, im_gui::Button, 0, 0, 0, napi_default, 0}
        ,{"imgui_pushStyleColor", 0, im_gui::PushStyleColor, 0, 0, 0, napi_default, 0}
        ,{"imgui_popStyleColor", 0, im_gui::PopStyleColor, 0, 0, 0, napi_default, 0}
        ,{"imgui_inputTextMultiline", 0, im_gui::InputTextMultiline, 0, 0, 0, napi_default, 0}
        ,{"imgui_inputText", 0, im_gui::InputText, 0, 0, 0, napi_default, 0}
        ,{"imgui_text", 0, im_gui::Text, 0, 0, 0, napi_default, 0}
        ,{"imgui_textDisabled", 0, im_gui::TextDisabled, 0, 0, 0, napi_default, 0}
        ,{"imgui_isItemHovered", 0, im_gui::IsItemHovered, 0, 0, 0, napi_default, 0}
        ,{"imgui_beginTooltip", 0, im_gui::BeginTooltip, 0, 0, 0, napi_default, 0}
        ,{"imgui_endTooltip", 0, im_gui::EndTooltip, 0, 0, 0, napi_default, 0}
        ,{"imgui_pushTextWrapPos", 0, im_gui::PushTextWrapPos, 0, 0, 0, napi_default, 0}
        ,{"imgui_getFontSize", 0, im_gui::GetFontSize, 0, 0, 0, napi_default, 0}
        ,{"imgui_textUnformatted", 0, im_gui::TextUnformatted, 0, 0, 0, napi_default, 0}
        ,{"imgui_popTextWrapPos", 0, im_gui::PopTextWrapPos, 0, 0, 0, napi_default, 0}
        ,{"imgui_sameLine", 0, im_gui::SameLine, 0, 0, 0, napi_default, 0}
        ,{"imgui_smallButton", 0, im_gui::SmallButton, 0, 0, 0, napi_default, 0}
    };
    napi_define_properties(env, exports, sizeof(imgui_desc) / sizeof(*imgui_desc), imgui_desc);
    return exports;
}