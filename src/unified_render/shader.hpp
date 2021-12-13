#pragma once

#include <GL/glew.h>
#include "path.hpp"
#include "unified_render/print.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#include "unified_render/texture.hpp"
#include "unified_render/texture_array.hpp"

namespace UnifiedRender {
    namespace OpenGl {
        class Shader {
        private:        
            void compile(GLuint type);
            std::string buffer;
            GLuint id;
        public:
            Shader(const std::string& path, GLuint type);
            ~Shader();

            GLuint get_id(void) const;
        };

        class VertexShader : public Shader {
        public:
            VertexShader(const std::string& path) : Shader(path, GL_VERTEX_SHADER) {};
        };

        class FragmentShader : public Shader {
        public:
            FragmentShader(const std::string& path) : Shader(path, GL_FRAGMENT_SHADER) {};
        };

        class Program {
            GLuint id;
        public:
            Program(const VertexShader* vertex, const FragmentShader* fragment);
            static Program* create(const std::string& vs_path, const std::string& fs_path);
            void use(void) const;
            void set_uniform(const std::string& name, glm::mat4 uniform) const;
            void set_uniform(const std::string& name, float value1, float value2) const;
            void set_uniform(const std::string& name, float value1, float value2, float value3) const;
            void set_uniform(const std::string& name, float value1, float value2, float value3, float value4) const;
            void set_uniform(const std::string& name, float uniform) const;
            void set_uniform(const std::string& name, int uniform) const;
            void set_texture(int value, const std::string& name, const UnifiedRender::Texture* texture) const;
            void set_texture(int value, const std::string& name, const UnifiedRender::TextureArray* texture) const;
            GLuint get_id(void) const;
        };
    }
}