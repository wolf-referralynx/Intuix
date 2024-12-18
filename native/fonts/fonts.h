#pragma once

#include "IconsFontAwesome5.h"

// Embedded fonts. The data for each font can be loaded by ImGui.
//
// ImFontConfig font_cfg;
// font_cfg.FontDataOwnedByAtlas = false;
// ... more font_cfg params.
// ImGui::GetIO().Fonts->AddFontFromMemoryTTF(Roboto_Regular_ttf, Roboto_Regular_ttf_len, 14.0f,
// &font_cfg);
//
// The font data was generated with:
// Bash: xxd -i Roboto-Regular.ttf > font_data.txt

//==============================================================================
// ROBOTO
//==============================================================================

extern unsigned char Roboto_Regular_ttf[];
extern unsigned int  Roboto_Regular_ttf_len;

extern unsigned char Roboto_Bold_ttf[];
extern unsigned int  Roboto_Bold_ttf_len;

extern unsigned char Roboto_Italic_ttf[];
extern unsigned int  Roboto_Italic_ttf_len;

//==============================================================================
// ROBOTO MONO
//==============================================================================

extern unsigned char RobotoMono_Regular_ttf[];
extern unsigned int  RobotoMono_Regular_ttf_len;

extern unsigned char RobotoMono_Bold_ttf[];
extern unsigned int  RobotoMono_Bold_ttf_len;

extern unsigned char RobotoMono_Italic_ttf[];
extern unsigned int  RobotoMono_Italic_ttf_len;

//==============================================================================
// FONT AWESOME
//==============================================================================

extern unsigned char fa_solid_900_ttf[];
extern unsigned int  fa_solid_900_ttf_len;

extern unsigned char fa_brands_400_ttf[];
extern unsigned int  fa_brands_400_ttf_len;