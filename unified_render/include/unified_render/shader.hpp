// Unified Render - General purpouse game engine
// Copyright (C) 2021, Unified Render contributors
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
// ----------------------------------------------------------------------------
// Name:
//      shader.hpp
//
// Abstract:
//      Does some important stuff.
// ----------------------------------------------------------------------------

#pragma once

#include <string>
#include <exception>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#include "unified_render/path.hpp"
#include "unified_render/print.hpp"
#include "unified_render/texture.hpp"
#include "unified_render/glsl_trans.hpp"

namespace UnifiedRender::OpenGL {
    class ShaderException : public std::exception {
        std::string buffer;
    public:
        ShaderException(const std::string& _buffer): buffer(_buffer) {};
        virtual const char* what(void) const noexcept {
            return buffer.c_str();
        }
    };
    struct Option {
        bool used;
        Option(std::string option, bool use):
            used{ use }, _option{ option } {}

        std::string get_option() {
            return _option;
        }
    private:
        std::string _option;
    };

    class Shader {
    private:
        void compile(GLuint type);
        std::string buffer;
        GLuint id;
    public:
        Shader(const std::string& path, GLuint type, bool use_transpiler = true, std::vector<UnifiedRender::OpenGL::GLSL_Define> defintions = {});
        ~Shader();

        GLuint get_id(void) const;
    };

    class VertexShader: public Shader {
    public:
        VertexShader(const std::string& path);
        ~VertexShader();
    };

    class FragmentShader: public Shader {
    public:
        FragmentShader(const std::string& path, bool use_transpiler = true, std::vector<UnifiedRender::OpenGL::GLSL_Define> defintions = {});
        ~FragmentShader();
    };

    class GeometryShader: public Shader {
    public:
        GeometryShader(const std::string& path);
        ~GeometryShader();
    };

    class TessControlShader: public Shader {
    public:
        TessControlShader(const std::string& path);
        ~TessControlShader();
    };

    class TessEvalShader: public Shader {
    public:
        TessEvalShader(const std::string& path);
        ~TessEvalShader();
    };

    class Program {
        GLuint id;
    public:
        Program();
        Program(const VertexShader* vertex, const FragmentShader* fragment, const GeometryShader* geometry = nullptr, const TessControlShader* tctrl = nullptr, const TessEvalShader* tee = nullptr);
        ~Program();
        static std::unique_ptr<Program> create(const std::string& vs_path, const std::string& fs_path, const std::string& gs_path = "");
        static std::unique_ptr<Program> create(std::vector<Option> options, const std::string& vs_path, const std::string& fs_path, const std::string& gs_path = "");
        static std::unique_ptr<Program> create_regular(const std::string& vs_path, const std::string& fs_path, const std::string& gs_path = "");

        void attach_shader(const Shader* shader);
        void link(void);

        void use(void) const;
        void set_uniform(const std::string& name, glm::mat4 uniform) const;
        void set_uniform(const std::string& name, float value1, float value2) const;
        void set_uniform(const std::string& name, float value1, float value2, float value3) const;
        void set_uniform(const std::string& name, float value1, float value2, float value3, float value4) const;
        void set_uniform(const std::string& name, float uniform) const;
        void set_uniform(const std::string& name, int uniform) const;

        void set_texture(int value, const std::string& name, const UnifiedRender::Texture& texture) const;
        void set_texture(int value, const std::string& name, const UnifiedRender::TextureArray& texture) const;

        GLuint get_id(void) const;
    };
};