const intuix    = require('./src/intuixBindings'); // Import centralized module
const ImGui     = require('./src/imguiBindings'); // Import ImGui bindings
const Glfw      = require('./src/glfwBindings'); // Import Glfw bindings
const { ImVec2 }    = require('./src/imvec2');
const { icons } = require('./src/icons')

const state = {
    displayW: 2180,
    displayH: 1200,
    windowPtr: null,
    displayDemoWindow: true,
    textIsSet: false,
    bufferSize: 1024,
    textBoxSize: { x: 600, y: 200 },
    useButtonStyle: false,
    editor: null,
    dynamicWindows: [],

}

// const font1 = 0x7f84fef24600n;
// const font2 = 0x7f84fef24700n;
// const font3 = 0x7f84fef247c0n;
// const font4 = 0x7f84fef24880n;
// const font5 = 0x7f84fef24940n;
// const font6 = 0x7f84fef24a00n;

Glfw.init();
state.windowPtr = Glfw.createWindow(state.displayW, state.displayH);
Glfw.setWindowTitle(state.windowPtr, "Intuix");

// Multi-line Text Edit
let textBuffer = `
// state.dynamicWindows.push({
//     title: "Dynamic Window " + (state.dynamicWindows.length + 1),
//     content: "This is dynamically created window #" + (state.dynamicWindows.length + 1),
//     isOpen: true
// });
`;

//Function to render dynamic windows
const renderDynamicWindows = () => {
    for (let i = 0; i < state.dynamicWindows.length; i++) {
        let win = state.dynamicWindows[i];
        if (win.isOpen) {
            if (ImGui.begin(win.title, 0)) {
                ImGui.text(win.content);
                ImGui.textDisabled("This text is disabled");
                if (ImGui.button("Close")) {
                    win.isOpen = false; // Close the window
                }
            }
            ImGui.end();
        }
    }
};


// Function to evaluate and run the script
const runScript = (script)=> {
    try {
        eval(script); // Dynamically evaluate the script code
    } catch (err) {
        console.error("Script error:", err);
    }
}

const beginRenderLoop = ()=>{
    Glfw.pollEvents();
    ImGui.implOpenGL3NewFrame();
    ImGui.implGlfw_NewFrame();
    ImGui.newFrame();
}

const endRenderLoop = ()=>{
    ImGui.render();
    Glfw.setViewport(0, 0, state.displayW, state.displayH);
    Glfw.setClearColor(0.15, 0.16, 0.21, 1.00);
    Glfw.glClear();          
    ImGui.implOpenGL3_RenderDrawData(ImGui.getDrawData());
    Glfw.swapBuffers();
}

while (!Glfw.windowShouldClose()) {
    beginRenderLoop();

    // Create a new window using ImGui::Begin / ImGui::End
    if (ImGui.begin("JS Console", 0)) {
        //Add ImGui content here
        if(state.useButtonStyle){
            ImGui.pushStyleColor(ImGui.ImGuiCol_Button, 1.0, 0.0, 0.0, 1.0);        // Button default: Bright red
            ImGui.pushStyleColor(ImGui.ImGuiCol_ButtonHovered, 0.8, 0.0, 0.0, 1.0); // Button hovered: Darker red
            ImGui.pushStyleColor(ImGui.ImGuiCol_ButtonActive, 0.6, 0.0, 0.0, 1.0);  // Button active: Deep red
        }
        
        // Create a button with a click event that executes JS in the TextBlock.
        //const vec = new ImVec2(24.00, 24.00);
        if(ImGui.button(icons.ICON_FA_ARROW_CIRCLE_RIGHT, new ImVec2(24.00, 24.00))){
            runScript(textBuffer);
        }
        
        if(state.useButtonStyle){
            ImGui.popStyleColor(3);
        }
        
        ImGui.pushFont(5);
        const result = ImGui.inputTextMultiline("###Editor", textBuffer, state.bufferSize, state.textBoxSize);
        // Check if text was changed
        if (result.changed) {
            textBuffer = result.buffer; // Update buffer with new content
        }
        ImGui.popFont();
        renderDynamicWindows();
    }
    // End the window
    ImGui.end();

    let initialText = 
`state.dynamicWindows.push({
    title: "Dynamic Window " + (state.dynamicWindows.length + 1),
    content: "This is dynamically created window #" + (state.dynamicWindows.length + 1),
    isOpen: true
});
        `;

    if (ImGui.begin("Text Box Window", 0)) {
        if (ImGui.button(icons.ICON_FA_ARROW_CIRCLE_RIGHT, new ImVec2(24.00, 24.00))) {
            runScript(state.editor.getText());
        }
        
        if (ImGui.isItemHovered()) {
            ImGui.beginTooltip();
            ImGui.text("Execute All");
            ImGui.endTooltip();
        }
        
        ImGui.sameLine();
        if (ImGui.button(icons.ICON_FA_ARROW_ALT_CIRCLE_RIGHT, new ImVec2(24.00, 24.00))) {
            runScript(state.editor.getSelectedText());
        }

        if (ImGui.isItemHovered()) {
            ImGui.beginTooltip();
            ImGui.text("Execute Selected");
            ImGui.endTooltip();
        }

        /** Color Text Editor */
        if(!state.editor){
            state.editor = new ImGui.colorTextEditor("Initial Text ");
        }
        
        // Set text
        if(!state.textIsSet){
            state.editor.setText(initialText);
            state.textIsSet = true;
        }

        //state.editor.identifyFoldableRegions();
        
        // Get text
        //console.log(editor.getText()); // Outputs: "Hello, world!"

        // Render editor
        state.editor.render("My Editor"); 
    
    }
    ImGui.end();



    if(state.displayDemoWindow){
        ImGui.showDemoWindow();
    }

    endRenderLoop();
}

/** Test calls */
const fbSize = Glfw.getFramebufferSize(state.windowPtr);
console.log(fbSize);

/** Fin */
Glfw.terminate();
