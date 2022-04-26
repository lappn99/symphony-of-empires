// Symphony of Empires
// Copyright (C) 2021, Symphony of Empires contributors
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
//      client/map.hpp
//
// Abstract:
//      Does some important stuff.
// ----------------------------------------------------------------------------

#pragma once

#include <vector>
#include <memory>
#include <utility>
#include <functional>
#include <cstddef>

namespace UnifiedRender {
    class Texture;
    class Model;
    class TextureArray;
    class Model;
    class Quad;
    class FontSDF;
    class Label3D;

    namespace OpenGL {
        class Square;
        class Sphere;
        class Program;
        class Quad2D;
        class Framebuffer;
    }
}

namespace UI {
    class Context;
}

#include "province.hpp"
#include "unified_render/color.hpp"
#include "unified_render/primitive.hpp"

enum class MapView {
    SPHERE_VIEW,
    PLANE_VIEW,
};

class World;
class Camera;
class Nation;
class MapRender;
class GameState;
union SDL_Event;
class Input;
class Rivers;
class Borders;

static const float GLOBE_RADIUS = 100.f;
class ProvinceColor {
public:
    Province::Id id;
    UnifiedRender::Color color;
    ProvinceColor(Province::Id _id, UnifiedRender::Color _color): id{ _id }, color{ _color } {}
};
typedef std::function<std::string(const World& world, const Province::Id id)> mapmode_tooltip;
typedef std::function<std::vector<ProvinceColor>(const World& world)> mapmode_generator;
class Map;
typedef std::function<void(const World& world, Map& map, Province* province)> selector_func;
std::vector<ProvinceColor> political_map_mode(const World& world);
std::string political_province_tooltip(const World& world, const Province::Id id);
std::string empty_province_tooltip(const World& world, const Province::Id id);

class Map {
    // Called to get mapmode
    mapmode_generator mapmode_func;
    // Called to get the provinces info to show in tooltip
    mapmode_tooltip mapmode_tooltip_func;
    Rivers* rivers;
    Borders* borders;

    selector_func selector = nullptr;
    
public:
    Map(const World& world, int screen_width, int screen_height);
    ~Map();

    void update(const SDL_Event& event, Input& input, UI::Context* ui_ctx, GameState& gs);
    void update_mapmode();
    void draw_flag(const UnifiedRender::OpenGL::Program& shader, const Nation& nation);
    void draw(const GameState& gs);
    void handle_click(GameState& gs, SDL_Event event);
    void set_map_mode(mapmode_generator mapmode_func, mapmode_tooltip tooltip_func);
    void set_view(MapView view);
    void reload_shaders();
    void create_labels();

    MapRender* map_render;
    MapView view_mode = MapView::PLANE_VIEW;

    std::vector<const UnifiedRender::Model*> building_type_models, unit_type_models;
    std::vector<std::shared_ptr<UnifiedRender::Texture>> building_type_icons;
    std::vector<std::shared_ptr<UnifiedRender::Texture>> unit_type_icons;
    std::vector<std::shared_ptr<UnifiedRender::Texture>> nation_flags;

    std::vector<UnifiedRender::Label3D*> province_labels;
    std::vector<UnifiedRender::Label3D*> nation_labels;
    UnifiedRender::FontSDF* map_font;

    // Wind oscillator (for flags)
    float wind_osc = 0.f;
    // Input states
    bool is_drag = false;
    glm::vec2 last_camera_drag_pos;

    void set_selection(selector_func selector);

    const World& world;
    Camera* camera;

    std::shared_ptr<UnifiedRender::Texture> id_map;
    std::shared_ptr<UnifiedRender::Texture> province_color_tex;
    std::shared_ptr<UnifiedRender::Texture> line_tex;
    std::shared_ptr<UnifiedRender::Texture> skybox_tex;
    UnifiedRender::Sphere skybox;
    std::unique_ptr<UnifiedRender::OpenGL::Program> obj_shader;
};

