#pragma once

#ifndef TEXTURES_H
#define TEXTURES_H

#include "asset_atlas.h"
#include "stb_image.h"
//#include <glad/glad.h>

namespace asset {
    GLuint asset_atlas_texture;
    bool LoadTextureFromAtlas() {
        /** Load from embedded resource file */
        int image_width = 0, image_height = 0;
        auto image_data = (char*)stbi_load_from_memory((unsigned char*)asset::data::DATA, (int)asset::data::SIZE, &image_width, &image_height, nullptr, 4);
        if (image_data == nullptr){ return false; }

        // /** Create an OpenGL texture identifier */
        GLuint image_texture;
        glGenTextures(1, &image_texture);
        glBindTexture(GL_TEXTURE_2D, image_texture);

        /** Setup filtering parameters for display */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); /** This is required on WebGL for non power-of-two textures */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); /** Same */

        /** Upload pixels into texture */
        #if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        #endif
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
        stbi_image_free(image_data);
        *&asset_atlas_texture = image_texture;

        return true;
    }
}


#endif /* TEXTURES_H */