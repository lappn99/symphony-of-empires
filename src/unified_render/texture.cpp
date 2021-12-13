#include "unified_render/texture.hpp"
#include "path.hpp"
#include "unified_render/print.hpp"
#include <string>
#include <algorithm>
#ifdef _MSC_VER
#include <SDL_surface.h>
#else
#include <SDL2/SDL_surface.h>
#endif

UnifiedRender::Texture::~Texture() {
    if (gl_tex_num)
      delete_opengl();
}
/**
 * This dummy texture helps to avoid crashes due to missing buffers or so, and also gives
 * visual aid of errors
 */
void UnifiedRender::Texture::create_dummy() {
    width = 16;
    height = 16;
    buffer = new uint32_t[width * height];
    if(buffer == nullptr)
        throw TextureException("Dummy", "Out of memory for dummy texture");

    // Fill in with a pattern of pink and black
    // This should be autovectorized by gcc
    for(size_t i = 0; i < width * height; i++)
        buffer[i] = (i % 2) ? 0xff000000 : 0xff808000;
}

void UnifiedRender::Texture::to_opengl(TextureOptions options) {
    glGenTextures(1, &gl_tex_num);
    glBindTexture(GL_TEXTURE_2D, gl_tex_num);
    glTexImage2D(GL_TEXTURE_2D, 0, options.internal_format, width, height, 0, options.format, options.type, buffer);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, options.wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, options.wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, options.min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, options.mag_filter);
}

void UnifiedRender::Texture::gen_mipmaps() const {
    glBindTexture(GL_TEXTURE_2D, gl_tex_num);
    glGenerateMipmap(GL_TEXTURE_2D);
}

/**
 * Converts the texture into a OpenGL texture, and assigns it a number
  */
void UnifiedRender::Texture::to_opengl(SDL_Surface* surface) {
    auto colors = surface->format->BytesPerPixel;
    GLuint texture_format;
    if(colors == 4) {   // alpha
        if(surface->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    }
    else {             // no alpha
        if(surface->format->Rmask == 0x000000ff)
            texture_format = GL_RGB;
        else
            texture_format = GL_BGR;
    }

    glGenTextures(1, &gl_tex_num);
    glBindTexture(GL_TEXTURE_2D, gl_tex_num);
    glTexImage2D(GL_TEXTURE_2D, 0, colors, surface->w, surface->h, 0,
        texture_format, GL_UNSIGNED_BYTE, surface->pixels);

    if(glewIsSupported("GL_VERSION_2_1"))
        glGenerateMipmap(GL_TEXTURE_2D);
    else
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}


/**
 * Binds the texture to the current OpenGL context
 */
void UnifiedRender::Texture::bind(void) const {
    glBindTexture(GL_TEXTURE_2D, gl_tex_num);
}

/**
 * Deletes the OpenGL representation of this texture
  */
void UnifiedRender::Texture::delete_opengl() {
    glDeleteTextures(1, &gl_tex_num);
}

/**
 * Finds a texture in the list of a texture manager
 * if the texture is already in the list we load the saved texture from the list
 * instead of loading it from the disk.
 *
 * Otherwise we load it from the disk and add it to the saved texture list
 *
 * The object returned is a pointer and we will not give ownership of textures in the list
 * and program should not modify the contents of it since it will differ from the texture
 * on the disk, and our main point is to mirror loaded textures from the disk - not modify
 * them.
 */
const UnifiedRender::Texture& UnifiedRender::TextureManager::load_texture(const std::string& path, TextureOptions options) {
    // Find texture when wanting to be loaded
    auto it = std::find_if(this->textures.begin(), this->textures.end(), [&path](const std::pair<UnifiedRender::Texture*, std::string>& element) {
        return (element.second == path);
    });

    // Load texture from cached texture list
    if(it != this->textures.end())
        return *((*it).first);

    print_info("Loaded and cached texture %s", path.c_str());

    // Otherwise texture is not in our control, so we create a new texture
    UnifiedRender::Texture* tex;
    try {
        tex = new UnifiedRender::Texture(path);
    }
    catch(BinaryImageException&) {
        tex = new UnifiedRender::Texture();
        tex->create_dummy();
    }

    tex->to_opengl(options);
    this->textures.insert(std::make_pair(tex, path));
    return *((const Texture*)tex);
}

UnifiedRender::TextureManager* g_texture_manager;