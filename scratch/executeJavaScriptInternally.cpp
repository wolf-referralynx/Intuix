#include <node_api.h>
#include <iostream>

// Helper function to execute JavaScript code internally
void ExecuteJavaScriptInternally(napi_env env) {
    napi_status status;

    // Define the JavaScript code to execute
    const char* js_code = "(() => { const result = 21 * 2; result; })()";

    // Create a napi_value representing the script
    napi_value js_script;
    status = napi_create_string_utf8(env, js_code, NAPI_AUTO_LENGTH, &js_script);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to create JS string");
        return;
    }

    // Execute the JavaScript code
    napi_value result;
    status = napi_run_script(env, js_script, &result);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to execute script");
        return;
    }

    // Retrieve and log the result (if needed)
    double result_value;
    status = napi_get_value_double(env, result, &result_value);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to get result value");
        return;
    }

    std::cout << "Internal JavaScript execution result: " << result_value << std::endl;
}

// Module initialization function
napi_value Init(napi_env env, napi_value exports) {
    // Execute JavaScript code during module initialization
    ExecuteJavaScriptInternally(env);

    // The exports object can remain unmodified
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
