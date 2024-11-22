if (ImGui.begin("Tooltip Example", 0)) {
    ImGui.textDisabled("(?)");

    // Check if the button is hovered
    if (ImGui.isItemHovered()) {
        ImGui.beginTooltip();
        ImGui.pushTextWrapPos(ImGui.getFontSize() * 35.0);
        ImGui.textUnformatted("This is the tooltip text!"); // Add text here
        ImGui.popTextWrapPos();
        ImGui.endTooltip();
    }
}
ImGui.end();

if (ImGui.begin("Same Line Example", 0)) {
    ImGui.text("Text 1");
    ImGui.sameLine();
    ImGui.text("Text 2 (same line)");
    ImGui.sameLine(200.0); // Specify position
    ImGui.text("Text 3 (positioned)");

    if (ImGui.smallButton("Small Button")) {
        console.log("Small button clicked!");
    }
}
ImGui.end();

if (ImGui.begin("Hovered Flags Example", 0)) {
    if (ImGui.button("Hover Me")) {
        console.log("Button clicked!");
    }

    if (ImGui.isItemHovered(ImGui.HoveredFlags_DelayShort)) {
        ImGui.text("Hovered with short delay!");
    } else {
        ImGui.text("Not hovered yet.");
    }
}
ImGui.end();