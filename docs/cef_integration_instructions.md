# Wrapping and Exposing CEF for a Native Node.js Module

## 1. Prerequisites
1. **Set Up CEF Development Environment**:
- Download CEF binaries for your platform ([cefbuilds](https://opensource.spotify.com/cefbuilds/)).
- Ensure your build tools are installed:
  - macOS: `clang`, `cmake`
  - Windows: Visual Studio
  - Linux: GCC/Clang and dependencies for Chromium.

2. **Node.js Native Module Setup**:
- Use `cmake.js` to compile and link CEF with your Node.js module.

---

## 2. Integrate CEF into the Native Module

### a. Create a Basic CEF Application
1. Define a simple CEF application:

```cpp
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/wrapper/cef_helpers.h"

class SimpleClient : public CefClient, public CefLifeSpanHandler {
public:
    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
        return this;
    }

    IMPLEMENT_REFCOUNTING(SimpleClient);
};

class SimpleApp : public CefApp, public CefBrowserProcessHandler {
public:
    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
        return this;
    }

    void OnContextInitialized() override {
        CEF_REQUIRE_UI_THREAD();
        CefWindowInfo window_info;
        CefBrowserSettings browser_settings;

        window_info.SetAsPopup(nullptr, "CEF Example");
        CefBrowserHost::CreateBrowser(window_info, new SimpleClient(), "https://example.com", browser_settings, nullptr, nullptr);
    }

    IMPLEMENT_REFCOUNTING(SimpleApp);
};

int main(int argc, char* argv[]) {
    CefMainArgs main_args(argc, argv);
    CefRefPtr<SimpleApp> app = new SimpleApp();
    return CefExecuteProcess(main_args, app, nullptr);
}
```

---

### b. Expose the CEF Initialization in Node.js
1. Use `<node_api.h>` to define your module entry points:

```cpp
#include <node_api.h>
#include <iostream>
#include "include/cef_app.h"

napi_value InitCEF(napi_env env, napi_callback_info info) {
    // Start CEF
    char* argv[] = { "node-cef-app" };
    CefMainArgs main_args(1, argv);
    CefRefPtr<SimpleApp> app = new SimpleApp();
    CefExecuteProcess(main_args, app, nullptr);
    CefInitialize(main_args, CefSettings(), app, nullptr);

    return nullptr;
}

napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc = { "initCEF", nullptr, InitCEF, nullptr, nullptr, nullptr, napi_default, nullptr };
    napi_define_properties(env, exports, 1, &desc);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
```

2. Build with `cmake.js`:
- Link against the CEF libraries during the build process:
```cmake
target_link_libraries(your_module_name PRIVATE cef_sandbox libcef)
```

---

## 3. Enable Node.js and CEF Communication

### a. Add Bidirectional Communication
- Use CEF’s **V8 Handler** to expose JavaScript objects that Node.js can interact with:
```cpp
class NodeBridge : public CefV8Handler {
public:
    bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) override {
        if (name == "fromNode") {
            std::cout << "Message from Node.js: " << arguments[0]->GetStringValue() << std::endl;
            retval = CefV8Value::CreateString("Response from CEF");
            return true;
        }
        return false;
    }

    IMPLEMENT_REFCOUNTING(NodeBridge);
};
```

