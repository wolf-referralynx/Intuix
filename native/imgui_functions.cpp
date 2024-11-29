#include <node_api.h>
#include "backends/imgui_impl_opengl3.h" 
#include "backends/imgui_impl_glfw.h"
#include <cstdio>
#include <iostream>
namespace im_gui {
    napi_value ImplOpenGL3_NewFrame(napi_env env, napi_callback_info info) {
        // Call ImGui's OpenGL backend NewFrame function
        ImGui_ImplOpenGL3_NewFrame();

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    napi_value ImplGlfw_NewFrame(napi_env env, napi_callback_info info) {
        // Call ImGui's GLFW backend NewFrame function
        ImGui_ImplGlfw_NewFrame();

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    napi_value NewFrame(napi_env env, napi_callback_info info) {
        // Call ImGui's NewFrame function
        ImGui::NewFrame();

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    napi_value ShowDemoWindow(napi_env env, napi_callback_info info) {
        size_t argc = 1; // Expecting 1 optional argument: a boolean pointer
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        bool open = true; // Default to true
        if (argc > 0) {
            bool jsBool;
            napi_get_value_bool(env, args[0], &jsBool);
            open = jsBool;
        }

        // Call ImGui's ShowDemoWindow with the open flag
        ImGui::ShowDemoWindow(&open);

        /** Return the updated "open" flag */
        napi_value result;
        napi_get_boolean(env, open, &result);
        return result;
    }

    napi_value Render(napi_env env, napi_callback_info info) {
        // Call ImGui's Render function
        ImGui::Render();

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    napi_value GetDrawData(napi_env env, napi_callback_info info) {
        // Get the draw data from ImGui
        ImDrawData* drawData = ImGui::GetDrawData();

        if (drawData == nullptr) {
            napi_throw_error(env, nullptr, "ImDrawData is null. Make sure ImGui::Render() was called before this.");
            return nullptr;
        }

        // Create a JavaScript external to wrap the ImDrawData pointer
        napi_value external;
        napi_status status = napi_create_external(env, drawData, nullptr, nullptr, &external);
        if (status != napi_ok) {
            napi_throw_error(env, nullptr, "Failed to create external ImDrawData");
            return nullptr;
        }

        return external;
    }

    napi_value ImplOpenGL3_RenderDrawData(napi_env env, napi_callback_info info) {
        size_t argc = 1; // Expecting 1 argument: ImDrawData* pointer
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        if (argc < 1) {
            napi_throw_error(env, nullptr, "Expected 1 argument: ImDrawData*");
            return nullptr;
        }

        // Retrieve the ImDrawData* pointer from JavaScript
        void* drawDataPtr;
        napi_status status = napi_get_value_external(env, args[0], &drawDataPtr);
        if (status != napi_ok || drawDataPtr == nullptr) {
            napi_throw_error(env, nullptr, "Invalid ImDrawData* pointer");
            return nullptr;
        }

        ImDrawData* drawData = static_cast<ImDrawData*>(drawDataPtr);

        // Call ImGui_ImplOpenGL3_RenderDrawData
        ImGui_ImplOpenGL3_RenderDrawData(drawData);

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    napi_value Begin(napi_env env, napi_callback_info info) {
        size_t argc = 3; // Expecting 3 arguments: window name (string), open state (boolean), and optional flags (integer)
        napi_value args[3];
        napi_status status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        // Check if enough arguments are provided
        if (argc < 2) {
            napi_throw_error(env, nullptr, "ImGui::Begin requires at least two arguments: window name (string) and open state (boolean)");
            return nullptr;
        }

        // **Retrieve the window name (string)**
        char window_name[256];
        size_t str_len;
        status = napi_get_value_string_utf8(env, args[0], window_name, sizeof(window_name), &str_len);
        if (status != napi_ok) {
            napi_throw_error(env, nullptr, "Failed to retrieve the window name (expected a string)");
            return nullptr;
        }

        // **Retrieve the open state (boolean)**
        bool isOpen = true; // Default value
        status = napi_get_value_bool(env, args[1], &isOpen);
        if (status != napi_ok) {
            napi_throw_error(env, nullptr, "Failed to retrieve the open state (expected a boolean)");
            return nullptr;
        }

        // **Retrieve optional flags (integer)**
        int flags = 0;
        if (argc > 2) {
            status = napi_get_value_int32(env, args[2], &flags);
            if (status != napi_ok) {
                napi_throw_error(env, nullptr, "Failed to retrieve the window flags (expected an integer)");
                return nullptr;
            }
        }

        // **Call ImGui::Begin**
        bool result = ImGui::Begin(window_name, &isOpen, flags);

        // **Return the updated `isOpen` state and the result**
        napi_value result_object;
        napi_create_object(env, &result_object);

        napi_value updated_isOpen;
        napi_get_boolean(env, isOpen, &updated_isOpen);
        napi_set_named_property(env, result_object, "isOpen", updated_isOpen);

        //napi_value napi_result;
        //napi_get_boolean(env, result, &napi_result);
        //napi_set_named_property(env, result_object, "result", napi_result);

        return result_object;
    }

    /** Wrap ImGui::End */
    napi_value End(napi_env env, napi_callback_info info) {
        // Call ImGui::End
        ImGui::End();

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    /** Wrap ImGui::Button */
    napi_value Button(napi_env env, napi_callback_info info) {
        size_t argc = 1; // Expecting 1 argument: button label (string)
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        // Validate argument count
        if (argc < 1) {
            napi_throw_error(env, nullptr, "ImGui::Button requires a label (string) as an argument.");
            return nullptr;
        }

        // Retrieve the button label (string)
        size_t str_len;
        size_t str_read;
        char button_label[256];
        napi_get_value_string_utf8(env, args[0], button_label, sizeof(button_label), &str_read);

        // Call ImGui::Button
        bool result = ImGui::Button(button_label);

        // Return the result as a boolean
        napi_value napi_result;
        napi_get_boolean(env, result, &napi_result);
        return napi_result;
    }

    /** Wrap ImGui::PushStyleColor */
    napi_value PushStyleColor(napi_env env, napi_callback_info info) {
        size_t argc = 5; // Expecting 5 arguments: style enum (int), R, G, B, A (doubles)
        napi_value args[5];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        // Validate argument count
        if (argc < 5) {
            napi_throw_error(env, nullptr, "ImGui::PushStyleColor requires 5 arguments: style ID (int), R, G, B, A (doubles).");
            return nullptr;
        }

        // Retrieve style ID (int)
        int style;
        napi_get_value_int32(env, args[0], &style);

        // Retrieve RGBA values (doubles)
        double r, g, b, a;
        napi_get_value_double(env, args[1], &r);
        napi_get_value_double(env, args[2], &g);
        napi_get_value_double(env, args[3], &b);
        napi_get_value_double(env, args[4], &a);

        // Call ImGui::PushStyleColor
        ImVec4 color(static_cast<float>(r), static_cast<float>(g), static_cast<float>(b), static_cast<float>(a));
        ImGui::PushStyleColor(style, color);

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    /** Wrap ImGui::PopStyleColor */
    napi_value PopStyleColor(napi_env env, napi_callback_info info) {
        size_t argc = 1; // Expecting 1 argument: count (optional int)
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        // Default count to 1 if not provided
        int count = 1;
        if (argc >= 1) {
            napi_get_value_int32(env, args[0], &count);
        }

        // Call ImGui::PopStyleColor
        ImGui::PopStyleColor(count);

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    /** Wrap ImGui::InputTextMultiline */
    napi_value InputTextMultiline(napi_env env, napi_callback_info info) {
        size_t argc = 4; // Expecting 4 arguments: label (string), buffer (string), bufferSize (int), and size (ImVec2)
        napi_value args[4];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        // Validate argument count
        if (argc < 4) {
            napi_throw_error(env, nullptr, "ImGui::InputTextMultiline requires 4 arguments: label (string), buffer (string), bufferSize (int), and size (ImVec2).");
            return nullptr;
        }

        // Retrieve label (string)
        size_t labelLength;
        char label[256];
        napi_get_value_string_utf8(env, args[0], label, sizeof(label), &labelLength);

        // Retrieve buffer (string)
        size_t bufferLength;
        char buffer[1024]; // Adjust size as needed
        napi_get_value_string_utf8(env, args[1], buffer, sizeof(buffer), &bufferLength);

        // Retrieve bufferSize (int)
        int bufferSize;
        napi_get_value_int32(env, args[2], &bufferSize);

        // Retrieve size (ImVec2)
        napi_value sizeObj = args[3];
        napi_value xValue, yValue;
        double x, y;

        napi_get_named_property(env, sizeObj, "x", &xValue);
        napi_get_named_property(env, sizeObj, "y", &yValue);
        napi_get_value_double(env, xValue, &x);
        napi_get_value_double(env, yValue, &y);

        ImVec2 size(static_cast<float>(x), static_cast<float>(y));

        // Call ImGui::InputTextMultiline
        bool result = ImGui::InputTextMultiline(label, buffer, static_cast<size_t>(bufferSize), size);

        // Return updated buffer and result as an object
        napi_value returnObj;
        napi_create_object(env, &returnObj);

        napi_value napiBuffer;
        napi_create_string_utf8(env, buffer, NAPI_AUTO_LENGTH, &napiBuffer);
        napi_set_named_property(env, returnObj, "buffer", napiBuffer);

        napi_value napiResult;
        napi_get_boolean(env, result, &napiResult);
        napi_set_named_property(env, returnObj, "changed", napiResult);

        return returnObj;
    }

    /** Wrap ImGui::InputText */
    napi_value InputText(napi_env env, napi_callback_info info) {
        size_t argc = 4; // Expecting 4 arguments: label (string), buffer (string), bufferSize (int), flags (int)
        napi_value args[4];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        // Validate argument count
        if (argc < 4) {
            napi_throw_error(env, nullptr, "ImGui::InputText requires 4 arguments: label (string), buffer (string), bufferSize (int), and flags (int).");
            return nullptr;
        }

        // Retrieve label (string)
        size_t labelLength;
        char label[256];
        napi_get_value_string_utf8(env, args[0], label, sizeof(label), &labelLength);

        // Retrieve buffer (string)
        size_t bufferLength;
        char buffer[1024]; // Adjust size as needed
        napi_get_value_string_utf8(env, args[1], buffer, sizeof(buffer), &bufferLength);

        // Retrieve bufferSize (int)
        int bufferSize;
        napi_get_value_int32(env, args[2], &bufferSize);

        // Retrieve flags (int)
        int flags;
        napi_get_value_int32(env, args[3], &flags);

        // Call ImGui::InputText
        bool result = ImGui::InputText(label, buffer, static_cast<size_t>(bufferSize), flags);

        // Return updated buffer and result as an object
        napi_value returnObj;
        napi_create_object(env, &returnObj);

        napi_value napiBuffer;
        napi_create_string_utf8(env, buffer, NAPI_AUTO_LENGTH, &napiBuffer);
        napi_set_named_property(env, returnObj, "buffer", napiBuffer);

        napi_value napiResult;
        napi_get_boolean(env, result, &napiResult);
        napi_set_named_property(env, returnObj, "changed", napiResult);

        return returnObj;
    }

    /** Wrap ImGui::Text */
    napi_value Text(napi_env env, napi_callback_info info) {
        size_t argc = 1; // Expecting 1 argument: text (string)
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        // Validate argument count
        if (argc < 1) {
            napi_throw_error(env, nullptr, "ImGui::Text requires 1 argument: text (string).");
            return nullptr;
        }

        // Retrieve the text (string)
        size_t textLength;
        char text[1024]; // Adjust size as needed
        napi_get_value_string_utf8(env, args[0], text, sizeof(text), &textLength);

        // Call ImGui::Text
        ImGui::Text("%s", text);

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    /** Wrap ImGui::TextDisabled */
    napi_value TextDisabled(napi_env env, napi_callback_info info) {
        size_t argc = 1; // Expecting 1 argument: text (string)
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        // Validate argument count
        if (argc < 1) {
            napi_throw_error(env, nullptr, "ImGui::TextDisabled requires 1 argument: text (string).");
            return nullptr;
        }

        // Retrieve the text (string)
        size_t textLength;
        char text[1024]; // Adjust size as needed
        napi_get_value_string_utf8(env, args[0], text, sizeof(text), &textLength);

        // Call ImGui::TextDisabled
        ImGui::TextDisabled("%s", text);

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    /** Wrap ImGui::IsItemHovered */
    napi_value IsItemHovered(napi_env env, napi_callback_info info) {
        // Call ImGui::IsItemHovered
        bool result = ImGui::IsItemHovered();

        // Convert the result to a JavaScript boolean
        napi_value napiResult;
        napi_get_boolean(env, result, &napiResult);

        return napiResult;
    }

    /** Wrap ImGui::BeginTooltip */
    napi_value BeginTooltip(napi_env env, napi_callback_info info) {
        // Call ImGui::BeginTooltip
        ImGui::BeginTooltip();

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    /** Wrap ImGui::EndTooltip */
    napi_value EndTooltip(napi_env env, napi_callback_info info) {
        // Call ImGui::EndTooltip
        ImGui::EndTooltip();

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    /** Wrap ImGui::PushTextWrapPos */
    napi_value PushTextWrapPos(napi_env env, napi_callback_info info) {
        size_t argc = 1; // Expecting 1 optional argument: wrapLocalPosX (float)
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        // Default value for wrapLocalPosX
        float wrapLocalPosX = 0.0f;

        // If an argument is provided, retrieve it as a float
        if (argc > 0) {
            double tempWrapLocalPosX;
            napi_get_value_double(env, args[0], &tempWrapLocalPosX);
            wrapLocalPosX = static_cast<float>(tempWrapLocalPosX);
        }

        // Call ImGui::PushTextWrapPos
        ImGui::PushTextWrapPos(wrapLocalPosX);

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    /**  Wrap ImGui::GetFontSize */
    napi_value GetFontSize(napi_env env, napi_callback_info info) {
        // Call ImGui::GetFontSize
        float fontSize = ImGui::GetFontSize();

        // Convert the result to a JavaScript number
        napi_value napiFontSize;
        napi_create_double(env, static_cast<double>(fontSize), &napiFontSize);

        return napiFontSize;
    }

    /** Wrap ImGui::TextUnformatted */
    napi_value TextUnformatted(napi_env env, napi_callback_info info) {
        size_t argc = 1; // Expecting 1 argument: text (string)
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        // Validate argument count
        if (argc < 1) {
            napi_throw_error(env, nullptr, "ImGui::TextUnformatted requires 1 argument: text (string).");
            return nullptr;
        }

        // Retrieve the text (string)
        size_t textLength;
        char text[1024]; // Adjust size as needed
        napi_get_value_string_utf8(env, args[0], text, sizeof(text), &textLength);

        // Call ImGui::TextUnformatted
        ImGui::TextUnformatted(text);

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    /** Wrap ImGui::PopTextWrapPos */
    napi_value PopTextWrapPos(napi_env env, napi_callback_info info) {
        // Call ImGui::PopTextWrapPos
        ImGui::PopTextWrapPos();

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    /** Wrap ImGui::SameLine */
    napi_value SameLine(napi_env env, napi_callback_info info) {
        size_t argc = 2; // Expecting up to 2 optional arguments: posX (float), spacing (float)
        napi_value args[2];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        // Default values for posX and spacing
        float posX = 0.0f;
        float spacing = -1.0f;

        // If arguments are provided, retrieve them
        if (argc > 0) {
            double tempPosX;
            napi_get_value_double(env, args[0], &tempPosX);
            posX = static_cast<float>(tempPosX);
        }
        if (argc > 1) {
            double tempSpacing;
            napi_get_value_double(env, args[1], &tempSpacing);
            spacing = static_cast<float>(tempSpacing);
        }

        // Call ImGui::SameLine
        ImGui::SameLine(posX, spacing);

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    /** Wrap ImGui::SmallButton */
    napi_value SmallButton(napi_env env, napi_callback_info info) {
        size_t argc = 1; // Expecting 1 argument: label (string)
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        // Validate argument count
        if (argc < 1) {
            napi_throw_error(env, nullptr, "ImGui::SmallButton requires 1 argument: label (string).");
            return nullptr;
        }

        // Retrieve the label (string)
        size_t labelLength;
        char label[256]; // Adjust size as needed
        napi_get_value_string_utf8(env, args[0], label, sizeof(label), &labelLength);

        // Call ImGui::SmallButton
        bool result = ImGui::SmallButton(label);

        // Convert the result to a JavaScript boolean
        napi_value napiResult;
        napi_get_boolean(env, result, &napiResult);

        return napiResult;
    }

    /** Wrapper for ImGui::PushFont
        Accepts a font pointer as a JavaScript `BigInt` (since ImFont* is a pointer). */
    // napi_value PushFont(napi_env env, napi_callback_info info) {
    //     size_t argc = 1;
    //     napi_value args[1];
    //     napi_status status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    //     if (status != napi_ok || argc < 1) {
    //         napi_throw_type_error(env, nullptr, "Expected one argument (BigInt for ImFont*)");
    //         return nullptr;
    //     }

    //     // Ensure the argument is a BigInt
    //     bool isBigInt;
    //     int64_t fontAddress;
    //     status = napi_get_value_bigint_int64(env, args[0], &fontAddress, &isBigInt);
    //     if (status != napi_ok || !isBigInt) {
    //         napi_throw_type_error(env, nullptr, "Argument must be a BigInt representing an ImFont*");
    //         return nullptr;
    //     }

    //     // Cast the BigInt to an ImFont* and validate it
    //     ImFont* font = reinterpret_cast<ImFont*>(fontAddress);
    //     printf("Received font pointer: %p\n", font);

    //     if (font == nullptr) {
    //         napi_throw_type_error(env, nullptr, "Font pointer is null");
    //         return nullptr;
    //     }

    //     // Ensure the ImGui context is valid
    //     if (ImGui::GetCurrentContext() == nullptr) {
    //         napi_throw_error(env, nullptr, "ImGui context is not initialized");
    //         return nullptr;
    //     }

    //     // Push the font
    //     try {
    //         ImGui::PushFont(font);
    //         printf("Font pushed successfully: %p\n", font);
    //     } catch (...) {
    //         napi_throw_error(env, nullptr, "Exception occurred while pushing the font");
    //         return nullptr;
    //     }

    //     return nullptr; // Void return
    // }

    napi_value PushFont(napi_env env, napi_callback_info info) {
        size_t argc = 1;
        napi_value args[1];
        napi_status status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        // Ensure the correct number of arguments
        if (status != napi_ok || argc < 1) {
            napi_throw_type_error(env, nullptr, "Expected one argument (integer for font index)");
            return nullptr;
        }

        // Get the integer index from the arguments
        int32_t fontIndex;
        status = napi_get_value_int32(env, args[0], &fontIndex);
        if (status != napi_ok) {
            napi_throw_type_error(env, nullptr, "Argument must be an integer representing the font index");
            return nullptr;
        }

        // Ensure the ImGui context is valid
        if (ImGui::GetCurrentContext() == nullptr) {
            napi_throw_error(env, nullptr, "ImGui context is not initialized");
            return nullptr;
        }

        // Get the ImGuiIO object and ensure fonts are available
        ImGuiIO& io = ImGui::GetIO();
        if (io.Fonts->Fonts.empty()) {
            napi_throw_error(env, nullptr, "No fonts available in io.Fonts. Ensure fonts are added and built.");
            return nullptr;
        }

        // Validate the font index
        if (fontIndex < 0 || fontIndex >= static_cast<int32_t>(io.Fonts->Fonts.size())) {
            napi_throw_range_error(env, nullptr, "Font index out of range");
            return nullptr;
        }

        // Retrieve the font pointer using the index
        ImFont* font = io.Fonts->Fonts[fontIndex];
        if (font == nullptr) {
            napi_throw_error(env, nullptr, "Font pointer is null at the specified index");
            return nullptr;
        }

        // Push the font
        try {
            ImGui::PushFont(font);
            //printf("Font pushed successfully at index %d: %p\n", fontIndex, font);
        } catch (...) {
            napi_throw_error(env, nullptr, "Exception occurred while pushing the font");
            return nullptr;
        }

        return nullptr; // Void return
    }

    /** Wrapper for ImGui::PopFont
        Pops the current font. */
    napi_value PopFont(napi_env env, napi_callback_info info) {
        ImGui::PopFont();
        return nullptr; // Void return
    }

}
