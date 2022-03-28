#ifndef TEXTURE_LIBRARY_H
#define TEXTURE_LIBRARY_H

#define NUM_TEXTURES 12

#include "../../../bin/path_config.h"
#include <string>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <map>

namespace engine
{
    class TextureLibrary
    {
        public:
            void SetAllTextures();
            GLuint GetTexture(const std::string& tex) const;
            GLuint GetTexture(const int index) const;
        private:
            GLuint SetTexture(GLuint w, const char *fname);
            GLuint SetBackgroundTexture(GLuint w, const char *fname);
            GLuint tex_[NUM_TEXTURES];
            std::map<std::string, GLuint> tex_library_;
    };
}
#endif // TEXTURE_LIBRARY_H