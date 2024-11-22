const intuix = require('./intuixBindings');

const Glfw = {
    init: intuix.glfw_init
    ,createWindow: intuix.glfw_createWindow
    ,windowShouldClose: intuix.glfw_windowShouldClose
    ,setWindowTitle: intuix.glfw_setWindowTitle
    ,pollEvents: intuix.glfw_pollEvents
    ,swapBuffers: intuix.glfw_swapBuffers
    ,terminate: intuix.glfw_terminate
    ,getFramebufferSize: intuix.glfw_getFramebufferSize
    ,setViewport: intuix.glfw_setViewport
    ,setClearColor: intuix.glfw_setClearColor
    ,glClear: intuix.glfw_glClear
    ,renderDrawData: intuix.glfw_renderDrawData
}

module.exports = Glfw;