const intuix        = require('./src/intuixBindings'); // Import centralized module
const ImGui         = require('./src/imguiBindings'); // Import ImGui bindings
const Glfw          = require('./src/glfwBindings'); // Import Glfw bindings
const { ImVec2 }    = require('./src/imvec2');
const { icons }     = require('./src/icons');

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
    logs: [],
}

// Override console.log
logEditor = new ImGui.colorTextEditor("");
LogTextIsSet = false;

const originalConsoleLog = console.log;
console.log = (...args) => {
    LogTextIsSet = false;
    const message = args.map(arg => (typeof arg === 'object' ? JSON.stringify(arg, null ,2) : String(arg))).join(' ');
    state.logs.push(message);
    //originalConsoleLog(...args);
};

Glfw.init();
state.windowPtr = Glfw.createWindow(state.displayW, state.displayH);
Glfw.setWindowTitle(state.windowPtr, "Intuix");

// Render logs in ImGui
const renderLogs = () => {
    ImGui.begin("Console Output", true);

    if (ImGui.button("Clear Logs")) {
        LogTextIsSet = false;
        logEditor.setText("")
        LogTextIsSet = true;
        state.logs = [];
    }

    logEditor.render(); 

    let textLogs = "";
    state.logs.forEach(log => {
        textLogs = textLogs+log+"\n";
    });
    
    if(!LogTextIsSet){
        logEditor.setText(textLogs)
        LogTextIsSet = true;
    }
    
    ImGui.end();
};

/** Function to render dynamic windows */
const renderDynamicWindows = () => {
    for (let i = 0; i < state.dynamicWindows.length; i++) {
        let win = state.dynamicWindows[i];
        if (win.isOpen) {
            win.isOpen = ImGui.begin(win.title, win.isOpen).isOpen;
            ImGui.text(win.content);
            ImGui.end();
        }
    }
};

/** Function to evaluate and run the script */
const runScript = (script)=> {
    try {
        /** Dynamically evaluate the script code */
        eval(script); 
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

let initialText = 
`state.dynamicWindows.push({
    title: "Dynamic Window " + (state.dynamicWindows.length + 1),
    content: "This is dynamically created window #" + (state.dynamicWindows.length + 1),
    isOpen: true
});


state.dynamicWindows = state.dynamicWindows.map((it)=>{
	return {
		...it,
		isOpen: true
	}
})

state.dynamicWindows.pop();

console.log(state.dynamicWindows);
`;

while (!Glfw.windowShouldClose()) {
    beginRenderLoop();

    if (ImGui.begin("Script Console", true)) {
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
        if(!state.textIsSet){
            state.editor.setText(initialText);
            state.textIsSet = true;
        }
        
        // Render editor
        state.editor.render("My Editor"); 
    }
    ImGui.end();

    if(state.displayDemoWindow){
        ImGui.showDemoWindow();
    }

    /** Dynamic Content */
    renderDynamicWindows();
    renderLogs();

    endRenderLoop();
}

/** Test calls */
const fbSize = Glfw.getFramebufferSize(state.windowPtr);
console.log(fbSize);

/** Fin */
Glfw.terminate();


/** Create a new window using ImGui::Begin / ImGui::End */
// if (ImGui.begin("JS Console", true)) {
//     /** Add ImGui content here */
//     if(state.useButtonStyle){
//         ImGui.pushStyleColor(ImGui.ImGuiCol_Button, 1.0, 0.0, 0.0, 1.0);        // Button default: Bright red
//         ImGui.pushStyleColor(ImGui.ImGuiCol_ButtonHovered, 0.8, 0.0, 0.0, 1.0); // Button hovered: Darker red
//         ImGui.pushStyleColor(ImGui.ImGuiCol_ButtonActive, 0.6, 0.0, 0.0, 1.0);  // Button active: Deep red
//     }
        
//     /** Create a button with a click event that executes JS in the TextBlock. */
//     if(ImGui.button(icons.ICON_FA_ARROW_CIRCLE_RIGHT, new ImVec2(24.00, 24.00))){
//         runScript(textBuffer);
//     }
        
//     if(state.useButtonStyle){
//         ImGui.popStyleColor(3);
//     }
        
//     ImGui.pushFont(5);
//     const result = ImGui.inputTextMultiline("###Editor", textBuffer, state.bufferSize, state.textBoxSize);
//     /** Check if text was changed */
//     if (result.changed) {
//         textBuffer = result.buffer; /** Update buffer with new content */
//     }
//     ImGui.popFont();
//     //renderDynamicWindows();
// }
// End the window
//ImGui.end();