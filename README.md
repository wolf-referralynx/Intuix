### Native Node.js ImGui/GLFW Integration
#### Overview

This project bridges the power of C++ with the simplicity of JavaScript, enabling developers to create high-performance graphical user interfaces (GUIs) and interactive applications directly from Node.js. By wrapping the popular Dear ImGui and GLFW libraries in a native Node.js module, this project allows you to:

- Leverage ImGui’s immediate-mode GUI system to build intuitive, real-time interfaces.
- Use GLFW to manage windows, handle input, and interact with OpenGL seamlessly.
- Write your GUI logic entirely in JavaScript—no need to dive into C++!

Whether you're building debugging tools, data visualization dashboards, or interactive prototypes, this project makes creating desktop applications more accessible and efficient for JavaScript developers.

------------
### Key Features
- ImGui Integration: Access the full power of ImGui’s immediate-mode GUI capabilities directly in Node.js, including widgets, menus, windows, and more.

- GLFW Support: Handle window creation, input, and OpenGL context management with ease.

- Native Performance: Benefit from the speed and efficiency of native C++ bindings while writing application logic in JavaScript.

- Flexible Workflow: Dynamically script and modify your GUI at runtime using Node.js.
Cross-Platform Compatibility: Build and run your applications on Windows, macOS, and Linux.

------------
### Why This Project?
ImGui is known for its versatility and simplicity in C++ development, but it traditionally requires a steep learning curve and significant boilerplate code. This project lowers the barrier to entry by exposing ImGui and GLFW functionality to JavaScript, allowing developers to:

- Prototype Faster: Rapidly create and iterate on GUIs without needing to recompile.

- Simplify Development: Focus on application logic in JavaScript while leveraging native performance.

- Enhance Productivity: Automate workflows and streamline tool creation with Node.js's vast ecosystem.

------------
### How It Works
- C++ Bindings: The project wraps ImGui and GLFW functions using Node.js's N-API, exposing them as JavaScript functions.

- Modular Design: The bindings are organized into namespaces (glfw and ImGui) for clarity and maintainability.

- JavaScript API: A consistent, intuitive API mirrors ImGui's and GLFW's native conventions, making it easy to use for developers familiar with the libraries.

#### Example usage:

```js
const intuix = require('./build/Release/Lynx.node');

const displayW = 1280;
const displayH = 1024;
... Finish this...


```

------------
### Getting Started

1) Clone the Repository:
    ```
    git clone <repo-url>
    cd <repo-directory>
    ```

2) Install Dependencies: Ensure you have Node.js and CMake installed. Then, build the module:
    ```
    npm install
    npm run build
    ```

3) Run Examples: Check out the /examples directory for sample applications.

------------
### Planned Features
- Runtime Scripting: Add a colored text editor component for live scripting and debugging.
- Enhanced Bindings: Extend support for additional ImGui and GLFW features.
- Cross-Platform Testing: Ensure consistent performance across all major platforms.

------------
### Acknowledgments
- Dear ImGui: https://github.com/ocornut/imgui
- GLFW: https://github.com/glfw/glfw