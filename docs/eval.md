# Eval-Based Dynamic ImGui Interaction

## Overview
This example allows you to interact with your running Node.js + ImGui application by dynamically injecting or modifying ImGui elements via terminal input. The solution uses `eval` for flexibility, enabling you to add buttons, text, and logic in real-time.

If you ever need it again, just ask me for the “Eval-based dynamic ImGui example,” and I’ll re-share it or adapt it to your current needs.

---

## Implementation

### Code
```javascript
const readline = require('readline');

// Script code to dynamically modify the UI
let scriptCode = `
if (ImGui.button("Click Me")) {
    console.log("Button clicked!");
}
`;

// Function to evaluate and run the script
function runScript() {
    try {
        eval(scriptCode); // Dynamically evaluate the script code
    } catch (err) {
        console.error("Script error:", err);
    }
}

// Set up readline for terminal input
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    prompt: "> " // Prompt symbol
});

// Listen for input and update the script code dynamically
rl.prompt();
rl.on('line', (input) => {
    scriptCode = input; // Replace the current script code with the new input
    console.log("Script updated!");
    rl.prompt(); // Re-prompt for the next input
});

// Main ImGui render loop
while (!Glfw.windowShouldClose()) {
    Glfw.pollEvents();

    ImGui.implOpenGL3NewFrame();
    ImGui.implGlfw_NewFrame();
    ImGui.newFrame();

    if (ImGui.begin("Eval-Based Interaction", 0)) {
        runScript(); // Execute the current script code inside the ImGui window
    }
    ImGui.end();

    ImGui.render();
    Glfw.swapBuffers();
}

Glfw.terminate();
