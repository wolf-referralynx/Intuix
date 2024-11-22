#ifndef GLFW_FUNCTIONS_H
#define GLFW_FUNCTIONS_H

#include <node_api.h>
#include <GLFW/glfw3.h>

namespace glfw {
    napi_value Init(napi_env env, napi_callback_info info);
    napi_value SetWindowTitle(napi_env env, napi_callback_info info);
    napi_value CreateWindow(napi_env env, napi_callback_info info);
    napi_value WindowShouldClose(napi_env env, napi_callback_info info);
    napi_value SwapBuffers(napi_env env, napi_callback_info info);
    napi_value PollEvents(napi_env env, napi_callback_info info);
    napi_value TerminateGLFW(napi_env env, napi_callback_info info);
    napi_value GetFramebufferSize(napi_env env, napi_callback_info info);
    napi_value SetViewport(napi_env env, napi_callback_info info);
    napi_value SetClearColor(napi_env env, napi_callback_info info);
    napi_value Clear(napi_env env, napi_callback_info info);
    napi_value RenderDrawData(napi_env env, napi_callback_info info);
    napi_value getTextureID(napi_env env, napi_callback_info info);
}


#endif // GLFW_FUNCTIONS_H