#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#include "include/glfw_functions.hpp"
#include <GLFW/glfw3.h>
#include "imgui_internal.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <map>

#include "include/config_fonts.hpp"
#include "include/texture.h"

GLFWwindow* window = nullptr;
GLFWmonitor** monitors;
int monitorX, monitorY, count;
int windowWidth;
int windowHeight;

namespace glfw {

    std::map<std::string,ImFont*> fonts;

    napi_value Init(napi_env env, napi_callback_info info) {
        if (!glfwInit()) {
            napi_throw_error(env, nullptr, "Failed to initialize GLFW");
            return nullptr;
        }

        // Return undefined
        return nullptr; 
    }

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

        /** GL 3.0 + GLSL 150 */
        const char *glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Required on macOS
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 

        /** Center Window on Primary Monitor */
        monitors = glfwGetMonitors(&count);
        auto videoMode = glfwGetVideoMode(monitors[0]);
        windowWidth = videoMode->width / 2;
        windowHeight = windowWidth / 16 * 9;
        glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);
            
        /** Create window with graphics context */
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        /** Create a GLFW window */
        window = glfwCreateWindow(width, height, "ImGui + GLFW + Node.js", nullptr, nullptr);
        if (!window) {
            napi_throw_error(env, nullptr, "Failed to create GLFW window");
            glfwTerminate();
                return nullptr;
        }

        glfwDefaultWindowHints();
        glfwSetWindowPos(
            window,
            monitorX + (videoMode->width - windowWidth) / 2,
            monitorY + (videoMode->height - windowHeight) / 2
        );

        glfwShowWindow(window);

        /** Make the OpenGL context current */
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        /** Setup Dear ImGui & ImPlot context(s) */
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        //ImPlot::CreateContext();

        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        ConfigFontsApp(fonts);

        bool ret = asset::LoadTextureFromAtlas();

        /** Wrap the GLFWwindow pointer in a napi_value */
        napi_value jsWindow;
        napi_status status = napi_create_external(env, window, nullptr, nullptr, &jsWindow);
        if (status != napi_ok) {
            napi_throw_error(env, nullptr, "Failed to create external pointer");
            return nullptr;
        }

        /** Return the external pointer to JavaScript */
        return jsWindow;
    }

    napi_value SetWindowTitle(napi_env env, napi_callback_info info) {
        // Expecting 2 arguments: GLFWwindow* pointer and title string
        size_t argc = 2;
        napi_value args[2];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        if (argc < 2) {
            napi_throw_error(env, nullptr, "Expected 2 arguments: GLFWwindow* and title string");
            return nullptr;
        }

        // Extract the GLFWwindow* pointer
        void* windowPtr;
        napi_status status = napi_get_value_external(env, args[0], &windowPtr);
        if (status != napi_ok || windowPtr == nullptr) {
            napi_throw_error(env, nullptr, "Invalid GLFWwindow pointer");
            return nullptr;
        }
        GLFWwindow* window = static_cast<GLFWwindow*>(windowPtr);

        // Extract the title string
        size_t strLength;
        napi_get_value_string_utf8(env, args[1], nullptr, 0, &strLength);
        char* title = new char[strLength + 1];
        napi_get_value_string_utf8(env, args[1], title, strLength + 1, nullptr);

        // Call glfwSetWindowTitle
        glfwSetWindowTitle(window, title);

        // Clean up the allocated string
        delete[] title;

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    napi_value WindowShouldClose(napi_env env, napi_callback_info info) {
        napi_value result;
        napi_get_boolean(env, window && glfwWindowShouldClose(window), &result);
        return result;
    }

    napi_value SwapBuffers(napi_env env, napi_callback_info info) {
        if (window) {
            glfwSwapBuffers(window);
        }
        return nullptr;
    }

    napi_value PollEvents(napi_env env, napi_callback_info info) {
        glfwPollEvents();
        return nullptr;
    }

    napi_value TerminateGLFW(napi_env env, napi_callback_info info) {
        glfwTerminate();
        return nullptr;
    }

    napi_value GetFramebufferSize(napi_env env, napi_callback_info info) {
        size_t argc = 1; // Expecting 1 argument: the window pointer
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        if (argc < 1) {
            napi_throw_error(env, nullptr, "Expected 1 argument: GLFWwindow* pointer");
            return nullptr;
        }

        /** Extract the window pointer from JavaScript */
        void* windowPtr;
        napi_get_value_external(env, args[0], &windowPtr);
        GLFWwindow* window = static_cast<GLFWwindow*>(windowPtr);

        if (window == nullptr) {
            napi_throw_error(env, nullptr, "Invalid GLFWwindow pointer");
            return nullptr;
        }

        /** Get the framebuffer size */
        int width = 0, height = 0;
        glfwGetFramebufferSize(window, &width, &height);

        /** Create a JavaScript object to return the width and height */
        napi_value result;
        napi_create_object(env, &result);

        napi_value jsWidth, jsHeight;
        napi_create_int32(env, width, &jsWidth);
        napi_create_int32(env, height, &jsHeight);

        napi_set_named_property(env, result, "width", jsWidth);
        napi_set_named_property(env, result, "height", jsHeight);

        return result;
    }

    napi_value SetViewport(napi_env env, napi_callback_info info) {
        /** Expecting 4 arguments: x, y, width, height */
        size_t argc = 4;
        napi_value args[4];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        if (argc < 4) {
            napi_throw_error(env, nullptr, "Expected 4 arguments: x, y, width, height");
            return nullptr;
        }

        /** Extract the arguments */
        int x, y, width, height;
        napi_get_value_int32(env, args[0], &x);
        napi_get_value_int32(env, args[1], &y);
        napi_get_value_int32(env, args[2], &width);
        napi_get_value_int32(env, args[3], &height);

        /** Call the OpenGL function */
        glViewport(x, y, width, height);

        /** Return undefined (no return value from glViewport) */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    napi_value SetClearColor(napi_env env, napi_callback_info info) {
        /** Expecting 4 arguments: red, green, blue, alpha */
        size_t argc = 4;
        napi_value args[4];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        if (argc < 4) {
            napi_throw_error(env, nullptr, "Expected 4 arguments: red, green, blue, alpha");
            return nullptr;
        }

        /** Extract the arguments */
        double red, green, blue, alpha;
        napi_get_value_double(env, args[0], &red);
        napi_get_value_double(env, args[1], &green);
        napi_get_value_double(env, args[2], &blue);
        napi_get_value_double(env, args[3], &alpha);

        /** Call the OpenGL function */
        glClearColor(
            static_cast<GLfloat>(red),
            static_cast<GLfloat>(green),
            static_cast<GLfloat>(blue),
            static_cast<GLfloat>(alpha));

        /** Return undefined (no return value from glClearColor) */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    napi_value Clear(napi_env env, napi_callback_info info) {
        /** Clear the color buffer */
        glClear(GL_COLOR_BUFFER_BIT);

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    napi_value RenderDrawData(napi_env env, napi_callback_info info) {
        size_t argc = 1;
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

        if (argc < 1) {
            napi_throw_error(env, nullptr, "Expected 1 argument: ImDrawData*");
            return nullptr;
        }

        // Retrieve ImDrawData* from JavaScript (passed as an external)
        void* drawDataPtr;
        napi_status status = napi_get_value_external(env, args[0], &drawDataPtr);
        if (status != napi_ok || drawDataPtr == nullptr) {
            napi_throw_error(env, nullptr, "Invalid ImDrawData* pointer");
            return nullptr;
        }

        ImDrawData* drawData = static_cast<ImDrawData*>(drawDataPtr);

        // Call the ImGui function
        ImGui_ImplOpenGL3_RenderDrawData(drawData);

        /** Return undefined */
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    // Function to load a texture
    // GLuint loadTexture(const char* imagePath) {
    //     GLuint textureID;
    //     glGenTextures(1, &textureID);
    //     glBindTexture(GL_TEXTURE_2D, textureID);

    //     // Set texture parameters
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //     // Load the image
    //     int width, height, nrChannels;
    //     unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    //     if (data) {
    //         // Determine the image format
    //         GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

    //         // Upload the image data to OpenGL
    //         glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    //         glGenerateMipmap(GL_TEXTURE_2D);

    //         std::cout << "Texture loaded: " << imagePath << std::endl;
    //     } else {
    //         std::cerr << "Failed to load texture: " << imagePath << std::endl;
    //     }

    //     // Free image data
    //     stbi_image_free(data);

    //     return textureID;
    // }


    // napi_value getTextureID(napi_env env, napi_callback_info info) {
    //     GLuint textureID = loadTexture("path/to/your/image.png");

    //     if (textureID == 0) {
    //         napi_throw_error(env, nullptr, "Failed to load texture");
    //         return nullptr;
    //     }

    //     napi_value result;
    //     napi_status status = napi_create_external(env, (void*)(intptr_t)textureID, nullptr, nullptr, &result);
    //     if (status != napi_ok) {
    //         napi_throw_error(env, nullptr, "Failed to create external textureID");
    //     }

    //     return result;
    // }

}
