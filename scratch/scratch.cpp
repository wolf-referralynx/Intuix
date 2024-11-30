while (lineNo <= lineMax) {
    ImVec2 lineStartScreenPos = ImVec2(cursorScreenPos.x, cursorScreenPos.y + lineNo * mCharAdvance.y);

    // Check if the current line is the start of a foldable region
    auto regionIt = std::find_if(mFoldRegions.begin(), mFoldRegions.end(),
                                 [lineNo](const FoldRegion& region) { return region.startLine == lineNo; });

    if (regionIt != mFoldRegions.end()) {
        // Render the fold/unfold button
        RenderFoldIcon(*regionIt, lineStartScreenPos);

        // If the region is folded, render a placeholder and skip the region's lines
        if (regionIt->isFolded) {
            ImGui::SetCursorScreenPos(ImVec2(lineStartScreenPos.x + mTextStart, lineStartScreenPos.y));
            ImGui::TextDisabled("{...}");  // Render folded placeholder
            lineNo = regionIt->endLine + 1;  // Skip to the line after the folded region
            continue;
        }
    }

    // Render the current line normally if it's not folded
    ImVec2 textScreenPos = ImVec2(lineStartScreenPos.x + mTextStart, lineStartScreenPos.y);
    auto& line = mLines[lineNo];

    // Existing per-line rendering logic (selection, error markers, text, etc.)
    // Keep everything as is, so folding integrates seamlessly with existing features
    longTextRenderingLogicHere(line, drawList, textScreenPos, lineStartScreenPos);

    ++lineNo;  // Proceed to the next line
}
