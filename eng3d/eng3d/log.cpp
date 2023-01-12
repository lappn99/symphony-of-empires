// Eng3D - General purpouse game engine
// Copyright (C) 2021, Eng3D contributors
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// ----------------------------------------------------------------------------
// Name:
//      log.cpp
//
// Abstract:
//      Does some important stuff.
// ----------------------------------------------------------------------------

#include <cstdio>
#include <optional>
#include <memory>
#include "SDL.h"
#include "log.hpp"

static bool debug_show = false;

/// @brief Logs data to a file or console
void Eng3D::Log::log(const std::string_view severity, const std::string_view category, const std::string_view msg) {
    SDL_Log("<%s:%s> %s", severity.data(), category.data(), msg.data());
}

void Eng3D::Log::debug(const std::string_view category, const std::string_view msg) {
    if(debug_show)
        Eng3D::Log::log("DEBUG", category, msg);
}

void Eng3D::Log::warning(const std::string_view category, const std::string_view msg) {
    Eng3D::Log::log("WARN", category, msg);
}

void Eng3D::Log::error(const std::string_view category, const std::string_view msg) {
    Eng3D::Log::log("ERROR", category, msg);
}