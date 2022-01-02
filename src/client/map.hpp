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
    namespace OpenGL {
        class Square;
        class Sphere;
        class Program;
        class Quad2D;
        class Framebuffer;
    }
}

#include "province.hpp"
#include "unified_render/color.hpp"

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
struct Input;

static const float GLOBE_RADIUS = 100.f;
struct ProvinceColor {
    Province::Id id;
    UnifiedRender::Color color;
    ProvinceColor(Province::Id _id, UnifiedRender::Color _color): id{ _id }, color{ _color } {}
};
typedef std::function<std::vector<ProvinceColor>(const World& world)> mapmode_generator;
std::vector<ProvinceColor> political_map_mode(const World& world);

class Map {
    // Called to get mapmode
    mapmode_generator mapmode_func;
public:
    Map(const World& world, int screen_width, int screen_height);
    ~Map();

    void update(const SDL_Event& event, Input& input);
    void update_mapmode();
    void draw_flag(const UnifiedRender::OpenGL::Program& shader, const Nation& nation);
    void draw(const GameState& gs);
    void handle_click(GameState& gs, SDL_Event event);
    void set_map_mode(mapmode_generator mapmode_func);
    void set_view(MapView view);
    void reload_shaders();

    MapRender* map_render;
    MapView view_mode = MapView::PLANE_VIEW;

    std::vector<const UnifiedRender::Model*> building_type_models, unit_type_models;
    std::vector<const UnifiedRender::Texture*> building_type_icons;
    std::vector<const UnifiedRender::Texture*> unit_type_icons;
    std::vector<const UnifiedRender::Texture*> nation_flags;

    // Wind oscillator (for flags)
    float wind_osc = 0.f;

    const World& world;
    Camera* camera;

#if !defined TILE_GRANULARITY
    UnifiedRender::Texture* id_map;
    UnifiedRender::Texture* province_color_tex;
#endif
    std::unique_ptr<UnifiedRender::OpenGL::Program> obj_shader;
};

