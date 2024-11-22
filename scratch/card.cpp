#include "imgui.h"

void RenderDashboard() {
    // Define card size
    ImVec2 cardSize = ImVec2(200, 120);
    ImVec4 cardBgColor = ImVec4(0.95f, 0.95f, 0.95f, 1.0f); // Light background color
    ImVec4 textColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);       // Dark text color

    // Spacing between cards
    ImVec2 spacing = ImVec2(20, 20);

    ImGui::Begin("Dashboard", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    // Card 1: Admissions
    {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(cardBgColor).Value);
        ImGui::BeginChild("AdmissionsCard", cardSize, true, ImGuiWindowFlags_NoScrollbar);

        // Icon (placeholder, replace with actual texture or font rendering)
        ImGui::Text("🔲"); // Replace with an icon if needed
        ImGui::Text("Admissions");

        ImGui::PushFont(/* Larger Font */); // Use a larger font for the number
        ImGui::TextColored(ImColor(textColor), "247");
        ImGui::PopFont();

        ImGui::EndChild();
        ImGui::PopStyleColor();
    }

    ImGui::SameLine(); // Align the next card horizontally

    // Card 2: Admission Percentage
    {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(cardBgColor).Value);
        ImGui::BeginChild("AdmissionPercentageCard", cardSize, true, ImGuiWindowFlags_NoScrollbar);

        // Icon (placeholder, replace with actual texture or font rendering)
        ImGui::Text("➗"); // Replace with an icon if needed
        ImGui::Text("Admission Percentage %");

        ImGui::PushFont(/* Larger Font */); // Use a larger font for the percentage
        ImGui::TextColored(ImColor(textColor), "72.86");
        ImGui::PopFont();

        ImGui::EndChild();
        ImGui::PopStyleColor();
    }

    ImGui::End();
}
