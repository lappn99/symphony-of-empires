// Eng3D - General purpouse game engine
// Copyright (C) 2021, Eng3D contributors
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
//      log.cpp
//
// Abstract:
//      Basic logging functions.
// ----------------------------------------------------------------------------

#include <cstdio>

#include "eng3d/log.hpp"

void Eng3D::Log::debug(const std::string& category, const std::string& msg) {
    std::unique_ptr<FILE, int(*)(FILE*)> fp(fopen("log.txt", "a+t"), fclose);
    if(fp != nullptr) {
        fprintf(fp.get(), "<debug:%s> %s\n", category.c_str(), msg.c_str());
    }
}

void Eng3D::Log::warning(const std::string& category, const std::string& msg) {
    std::unique_ptr<FILE, int(*)(FILE*)> fp(fopen("log.txt", "a+t"), fclose);
    if(fp != nullptr) {
        fprintf(fp.get(), "<warning:%s> %s\n", category.c_str(), msg.c_str());
    }
}

void Eng3D::Log::error(const std::string& category, const std::string& msg) {
    std::unique_ptr<FILE, int(*)(FILE*)> fp(fopen("log.txt", "a+t"), fclose);
    if(fp != nullptr) {
        fprintf(fp.get(), "<error:%s> %s\n", category.c_str(), msg.c_str());
    }
}