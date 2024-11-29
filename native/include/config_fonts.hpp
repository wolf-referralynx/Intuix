#pragma once

#include "../../deps/imgui/imgui_internal.h"
#include "../fonts/fonts.h"
#include <map>
#include <string>
#include <iostream>

void ConfigFontsApp(std::map<std::string,ImFont*>& Fonts){

    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->Clear();

    ImFontConfig font_cfg;
    font_cfg.FontDataOwnedByAtlas = false;

    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.GlyphMinAdvanceX = 14.0f;
    icons_config.GlyphOffset = ImVec2(0, 0);
    icons_config.OversampleH = 1;
    icons_config.OversampleV = 1;
    icons_config.FontDataOwnedByAtlas = false;

    static const ImWchar fa_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
    
    ImStrncpy(font_cfg.Name, "Roboto Regular", 40);
    Fonts[font_cfg.Name] = io.Fonts->AddFontFromMemoryTTF(Roboto_Regular_ttf, Roboto_Regular_ttf_len, 18.0f, &font_cfg);
    ImFont* font1 = io.Fonts->AddFontFromMemoryTTF(fa_solid_900_ttf, fa_solid_900_ttf_len, 14.0f, &icons_config, fa_ranges);

    ImStrncpy(font_cfg.Name, "Roboto Bold", 40);
    Fonts[font_cfg.Name] = io.Fonts->AddFontFromMemoryTTF(Roboto_Bold_ttf, Roboto_Bold_ttf_len, 15.0f, &font_cfg);
    ImFont* font2 = io.Fonts->AddFontFromMemoryTTF(fa_solid_900_ttf, fa_solid_900_ttf_len, 14.0f, &icons_config, fa_ranges);

    ImStrncpy(font_cfg.Name, "Roboto Italic", 40);
    Fonts[font_cfg.Name] = io.Fonts->AddFontFromMemoryTTF(Roboto_Italic_ttf, Roboto_Italic_ttf_len, 15.0f, &font_cfg);
    ImFont* font3 = io.Fonts->AddFontFromMemoryTTF(fa_solid_900_ttf, fa_solid_900_ttf_len, 14.0f, &icons_config, fa_ranges);

    ImStrncpy(font_cfg.Name, "Roboto Mono Bold", 40);
    Fonts[font_cfg.Name] = io.Fonts->AddFontFromMemoryTTF(RobotoMono_Bold_ttf, RobotoMono_Bold_ttf_len, 15.0f, &font_cfg);
    ImFont* font4 = io.Fonts->AddFontFromMemoryTTF(fa_solid_900_ttf, fa_solid_900_ttf_len, 14.0f, &icons_config, fa_ranges);

    ImStrncpy(font_cfg.Name, "Roboto Mono Italic", 40);
    Fonts[font_cfg.Name] = io.Fonts->AddFontFromMemoryTTF(RobotoMono_Italic_ttf, RobotoMono_Italic_ttf_len, 15.0f, &font_cfg);
    ImFont* font5 = io.Fonts->AddFontFromMemoryTTF(fa_solid_900_ttf, fa_solid_900_ttf_len, 14.0f, &icons_config, fa_ranges);

    ImStrncpy(font_cfg.Name, "Roboto Mono Regular", 40);
    Fonts[font_cfg.Name] = io.Fonts->AddFontFromMemoryTTF(RobotoMono_Regular_ttf, RobotoMono_Regular_ttf_len, 20.0f, &font_cfg);
    ImFont* font6 = io.Fonts->AddFontFromMemoryTTF(fa_solid_900_ttf, fa_solid_900_ttf_len, 20.0f, &icons_config, fa_ranges);

    io.Fonts->Build(); 
}