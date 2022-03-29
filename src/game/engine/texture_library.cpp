#include "texture_library.h"

namespace engine
{
    const std::string resources_directory_g = RESOURCES_DIRECTORY;

    GLuint TextureLibrary::GetTexture(const std::string &tex) const
    {
        if(tex_library_.find(tex) == tex_library_.end()) {
            return tex_library_.at("error");
        } else {
            return tex_library_.at(tex);
        }
    }
    
    GLuint TextureLibrary::GetTexture(const int index) const
    {
        if(index > NUM_TEXTURES - 1) {
            return tex_library_.at("error");
        }
        return tex_[index];
    }

    void TextureLibrary::SetAllTextures()
    {
        glGenTextures(NUM_TEXTURES, tex_);
        tex_library_["player"] = SetTexture(tex_[0], (resources_directory_g + std::string("/textures/ship.png")).c_str());
        tex_library_["enemy_basic"] = SetTexture(tex_[1], (resources_directory_g + std::string("/textures/ship_red.png")).c_str());
        tex_library_["background"] = SetBackgroundTexture(tex_[2], (resources_directory_g + std::string("/textures/back.png")).c_str());
        tex_library_["explosion_basic"] = SetTexture(tex_[3], (resources_directory_g + std::string("/textures/explosion.png")).c_str());
        tex_library_["chopper_blade"] = SetTexture(tex_[4], (resources_directory_g + std::string("/textures/blade.png")).c_str());
        tex_library_["bullet"] = SetTexture(tex_[5], (resources_directory_g + std::string("/textures/bullet.png")).c_str());
        tex_library_["orb"] = SetTexture(tex_[6], (resources_directory_g + std::string("/textures/orb.png")).c_str());
        tex_library_["error"] = SetTexture(tex_[7], (resources_directory_g + std::string("/textures/error.png")).c_str());
        tex_library_["buoy2"] = SetTexture(tex_[9], (resources_directory_g + std::string("/textures/buoy2.png")).c_str());
        tex_library_["shield_c"] = SetTexture(tex_[10], (resources_directory_g + std::string("/textures/meteor_small.png")).c_str());
        tex_library_["buoy"] = SetTexture(tex_[11], (resources_directory_g + std::string("/textures/buoy.png")).c_str());
        glBindTexture(GL_TEXTURE_2D, tex_[0]);
    }

    GLuint TextureLibrary::SetTexture(GLuint w, const char *fname)
    {
        // Bind texture buffer
        glBindTexture(GL_TEXTURE_2D, w);

        // Load texture from a file to the buffer
        int width, height;
        unsigned char *image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);

        // Texture Wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Texture Filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        return w;
    }

    GLuint TextureLibrary::SetBackgroundTexture(GLuint w, const char *fname)
    {
        glBindTexture(GL_TEXTURE_2D, w);

        // Texture Wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Texture Filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load texture from a file to the buffer
        int width, height;
        unsigned char *image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
        return w;
    }
}