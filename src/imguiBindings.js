const intuix = require('./intuixBindings');

const ImGui = {
    implOpenGL3NewFrame: intuix.imgui_implOpenGL3NewFrame
    ,implGlfw_NewFrame: intuix.imgui_implGlfw_NewFrame
    ,newFrame: intuix.imgui_newFrame
    ,showDemoWindow: intuix.imgui_showDemoWindow
    ,render: intuix.imgui_render
    ,getDrawData: intuix.imgui_getDrawData
    ,implOpenGL3_RenderDrawData: intuix.imgui_implOpenGL3_RenderDrawData
    ,begin: intuix.imgui_begin
    ,end: intuix.imgui_end
    ,button: intuix.imgui_button
    ,pushStyleColor: intuix.imgui_pushStyleColor
    ,popStyleColor: intuix.imgui_popStyleColor
    ,ImGuiCol_Button: intuix.imgui_ImGuiCol_Button
    ,ImGuiCol_ButtonHovered: intuix.imgui_ImGuiCol_ButtonHovered
    ,ImGuiCol_ButtonActive: intuix.imgui_ImGuiCol_ButtonActive
    ,inputTextMultiline: intuix.imgui_inputTextMultiline
    ,inputText: intuix.imgui_inputText
    ,text: intuix.imgui_text
    ,textDisabled: intuix.imgui_textDisabled
    ,isItemHovered: intuix.imgui_isItemHovered
    ,HoveredFlags_DelayShort: intuix.imgui_HoveredFlags_DelayShort
    ,beginTooltip: intuix.imgui_beginTooltip
    ,endTooltip: intuix.imgui_endTooltip
    ,pushTextWrapPos: intuix.imgui_pushTextWrapPos
    ,getFontSize: intuix.imgui_getFontSize
    ,textUnformatted: intuix.imgui_textUnformatted
    ,popTextWrapPos: intuix.imgui_popTextWrapPos
    ,sameLine: intuix.imgui_sameLine
    ,smallButton: intuix.imgui_smallButton
    ,colorTextEditor: intuix.imgui_colorTextEditor
    ,image: intuix.imgui_image
    ,pushFont: intuix.imgui_pushFont
    ,popFont: intuix.imgui_popFont
    ,robotoRegular18: intuix.imgui_roboto_regular_18

};

module.exports = ImGui;