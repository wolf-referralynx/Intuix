#ifndef COLOR_TEXT_EDITOR_WRAPPER_H
#define COLOR_TEXT_EDITOR_WRAPPER_H

#include <node_api.h>
#include "TextEditor.h" // Include the ImGuiColorTextEdit header

class ColorTextEditor {
public:
    ColorTextEditor();
    ~ColorTextEditor();

    void SetText(const std::string& text);
    std::string GetText() const;
    std::string GetSelectedText() const;
    
    void Render(const std::string& title);

    static napi_value Init(napi_env env, napi_value exports);
    static napi_value Constructor(napi_env env, napi_callback_info info);

private:
    static napi_value SetTextMethod(napi_env env, napi_callback_info info);
    static napi_value GetTextMethod(napi_env env, napi_callback_info info);
    static napi_value GetSelectedTextMethod(napi_env env, napi_callback_info info);
    
    static napi_value RenderMethod(napi_env env, napi_callback_info info);

    static void Destructor(napi_env env, void* nativeObject, void* finalizeHint);

    TextEditor* editor; // Pointer to the ImGui ColorTextEditor instance
};

#endif // COLOR_TEXT_EDITOR_WRAPPER_H
