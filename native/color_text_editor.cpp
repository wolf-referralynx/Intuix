#include "include/color_text_editor.h"

ColorTextEditor::ColorTextEditor() {
    editor = new TextEditor();
    if (!editor) {
        throw std::runtime_error("Failed to create TextEditor instance");
    }
}

ColorTextEditor::~ColorTextEditor() {
    if (editor) {
        delete editor;
        editor = nullptr;
    }
}

void ColorTextEditor::SetText(const std::string& text) {
    editor->SetText(text);
}

std::string ColorTextEditor::GetText() const {
    if (!editor) {
        throw std::runtime_error("Editor instance is null in GetText");
    }
    return editor->GetText();
}

std::string ColorTextEditor::GetSelectedText() const {
    if (!editor) {
        throw std::runtime_error("Editor instance is null in GetText");
    }
    return editor->GetSelectedText();
}



void ColorTextEditor::Render(const std::string& title) {
    if (!editor) {
        throw std::runtime_error("Editor instance is null in Render");
    }

    // Check for valid ImGui context
    if (!ImGui::GetCurrentContext()) {
        throw std::runtime_error("No active ImGui context in Render");
    }

    //printf("Rendering editor with title: %s\n", title.c_str());
    editor->Render(title.c_str());
}

napi_value ColorTextEditor::Constructor(napi_env env, napi_callback_info info) {
    napi_value thisArg;
    napi_status status;

    // Retrieve 'this' object
    status = napi_get_cb_info(env, info, nullptr, nullptr, &thisArg, nullptr);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to retrieve 'this' in Constructor");
        return nullptr;
    }

    // Create a new instance
    auto* instance = new ColorTextEditor();
    if (!instance) {
        napi_throw_error(env, nullptr, "Failed to allocate ColorTextEditorWrapper");
        return nullptr;
    }

    // Wrap the native instance
    status = napi_wrap(env, thisArg, instance, ColorTextEditor::Destructor, nullptr, nullptr);
    if (status != napi_ok) {
        delete instance; // Cleanup on failure
        napi_throw_error(env, nullptr, "Failed to wrap native instance");
        return nullptr;
    }

    //printf("Wrapped native instance: %p\n", instance);

    return thisArg;
}

void ColorTextEditor::Destructor(napi_env env, void* nativeObject, void* finalizeHint) {
    delete static_cast<ColorTextEditor*>(nativeObject);
}

napi_value ColorTextEditor::SetTextMethod(napi_env env, napi_callback_info info) {
    napi_value thisArg;
    napi_value args[1];
    size_t argc = 1;
    napi_status status;

    // Retrieve the 'this' object and associated data
    status = napi_get_cb_info(env, info, &argc, args, &thisArg, nullptr);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to retrieve arguments in SetText");
        return nullptr;
    }

    // Unwrap the native instance
    void* nativeObject;
    status = napi_unwrap(env, thisArg, &nativeObject);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Invalid editor instance in SetText");
        return nullptr;
    }

    auto* instance = static_cast<ColorTextEditor*>(nativeObject);
    if (!instance || !instance->editor) {
        napi_throw_error(env, nullptr, "Invalid native editor instance");
        return nullptr;
    }

    // Validate and process the argument
    if (argc < 1 || !args[0]) {
        napi_throw_error(env, nullptr, "Expected a string argument for setText");
        return nullptr;
    }

    size_t strLength;
    status = napi_get_value_string_utf8(env, args[0], nullptr, 0, &strLength);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Invalid string argument for setText");
        return nullptr;
    }

    std::string text(strLength, '\0');
    napi_get_value_string_utf8(env, args[0], text.data(), strLength + 1, nullptr);

    // Set text
    instance->SetText(text);

    return nullptr;
}

napi_value ColorTextEditor::GetTextMethod(napi_env env, napi_callback_info info) {
    napi_value thisArg;
    void* data;

    // Retrieve the 'this' object
    napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &thisArg, &data);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to retrieve 'this' in GetText");
        return nullptr;
    }

    // Unwrap the native instance
    status = napi_unwrap(env, thisArg, &data);
    if (status != napi_ok || !data) {
        napi_throw_error(env, nullptr, "Invalid editor instance in GetText");
        return nullptr;
    }

    auto* instance = static_cast<ColorTextEditor*>(data);
    if (!instance || !instance->editor) {
        napi_throw_error(env, nullptr, "Editor instance is null in GetText");
        return nullptr;
    }

    // Get the text from the editor
    std::string text;
    try {
        text = instance->GetText();
    } catch (const std::exception& e) {
        napi_throw_error(env, nullptr, e.what());
        return nullptr;
    }

    napi_value result;
    status = napi_create_string_utf8(env, text.c_str(), NAPI_AUTO_LENGTH, &result);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to create string in GetText");
        return nullptr;
    }

    return result;
}

napi_value ColorTextEditor::GetSelectedTextMethod(napi_env env, napi_callback_info info) {
    napi_value thisArg;
    void* data;

    // Retrieve the 'this' object
    napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &thisArg, &data);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to retrieve 'this' in GetText");
        return nullptr;
    }

    // Unwrap the native instance
    status = napi_unwrap(env, thisArg, &data);
    if (status != napi_ok || !data) {
        napi_throw_error(env, nullptr, "Invalid editor instance in GetText");
        return nullptr;
    }

    auto* instance = static_cast<ColorTextEditor*>(data);
    if (!instance || !instance->editor) {
        napi_throw_error(env, nullptr, "Editor instance is null in GetText");
        return nullptr;
    }

    // Get the text from the editor
    std::string text;
    try {
        text = instance->GetSelectedText();
    } catch (const std::exception& e) {
        napi_throw_error(env, nullptr, e.what());
        return nullptr;
    }

    napi_value result;
    status = napi_create_string_utf8(env, text.c_str(), NAPI_AUTO_LENGTH, &result);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to create string in GetText");
        return nullptr;
    }

    return result;
}

napi_value ColorTextEditor::RenderMethod(napi_env env, napi_callback_info info) {
    napi_value thisArg;
    void* data;

    // Retrieve 'this' object
    napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &thisArg, nullptr);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to retrieve 'this' in Render");
        return nullptr;
    }

    // Unwrap the native instance
    status = napi_unwrap(env, thisArg, &data);
    if (status != napi_ok || !data) {
        napi_throw_error(env, nullptr, "Invalid editor instance in Render");
        return nullptr;
    }

    auto* instance = static_cast<ColorTextEditor*>(data);
    if (!instance || !instance->editor) {
        napi_throw_error(env, nullptr, "Editor instance is null in Render");
        return nullptr;
    }

    //printf("Unwrapped native instance: %p\n", instance);

    // Optional title argument
    size_t argc = 1;
    napi_value args[1];
    std::string title = "Editor";

    status = napi_get_cb_info(env, info, &argc, args, &thisArg, nullptr);
    if (status == napi_ok && argc > 0) {
        size_t strLength;
        status = napi_get_value_string_utf8(env, args[0], nullptr, 0, &strLength);
        if (status == napi_ok) {
            title.resize(strLength);
            napi_get_value_string_utf8(env, args[0], title.data(), strLength + 1, nullptr);
        }
    }

    try {
        instance->Render(title);
    } catch (const std::exception& e) {
        napi_throw_error(env, nullptr, e.what());
        return nullptr;
    }

    return nullptr;
}

napi_value ColorTextEditor::Init(napi_env env, napi_value exports) {
    napi_property_descriptor properties[] = {
        { "setText", 0, SetTextMethod, 0, 0, 0, napi_default, 0 },
        { "getText", 0, GetTextMethod, 0, 0, 0, napi_default, 0 },
        { "getSelectedText", 0, GetSelectedTextMethod, 0, 0, 0, napi_default, 0 },
        { "render", 0, RenderMethod, 0, 0, 0, napi_default, 0 },
    };

    napi_value constructor;
    napi_define_class(env, "imgui_colorTextEditor", NAPI_AUTO_LENGTH, Constructor, nullptr,
                      sizeof(properties) / sizeof(properties[0]), properties, &constructor);

    napi_set_named_property(env, exports, "imgui_colorTextEditor", constructor);

    return exports;
}
