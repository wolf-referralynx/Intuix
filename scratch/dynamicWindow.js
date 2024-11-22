// Global object to track dynamic windows
let dynamicWindows = [];

// Function to render dynamic windows
const renderDynamicWindows = () => {
    for (let i = 0; i < dynamicWindows.length; i++) {
        const win = dynamicWindows[i];
        if (win.isOpen) {
            if (ImGui.begin(win.title, 0)) {
                ImGui.text(win.content);
                if (ImGui.button("Close")) {
                    win.isOpen = false; // Close the window
                }
            }
            ImGui.end();
        }
    }
};

// Add a script to dynamically create new windows
const dynamicScript = `
dynamicWindows.push({
    title: "Dynamic Window " + (dynamicWindows.length + 1),
    content: "This is dynamically created window #" + (dynamicWindows.length + 1),
    isOpen: true
});
`;

textBuffer = dynamicScript;

// Add this to your render loop
if (ImGui.button("Execute JS")) {
    runScript(); // Execute the script
}
renderDynamicWindows(); // Render all dynamic windows
