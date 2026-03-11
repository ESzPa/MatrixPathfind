#pragma once

#include <string_view>

#include "piece.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

namespace {
inline size_t image_scaling = 1;
}

inline void set_scale(size_t n) noexcept {
    image_scaling = n;
}

inline void save_map_png(const FMap& map, const std::vector<Position>& path, const FMap& visited,
                         const std::string_view& filename) {
    const size_t width = map.width() * image_scaling;
    const size_t height = map.height() * image_scaling;

    const size_t channels = 3;

    std::vector<uint8_t> pixels(width * height * channels);

    std::set<Position> path_set(path.begin(), path.end());

    for(size_t y = 0; y < map.height(); ++y) {
        for(size_t x = 0; x < map.width(); ++x) {
            bool wall = map[y, x];
            uint8_t r, g, b;

            Position p = {static_cast<int32_t>(x), static_cast<int32_t>(y)};
            if(!path.empty() && p == path.front()) {
                r = b = 0;
                g = 255;
            }
            else if(!path.empty() && p == path.back()) {
                r = 255;
                g = b = 0;
            }
            else if(path_set.contains(p)) {
                r = g = 255;
                b = 0;
            }
            else if(visited[y, x]) {
                r = 150;
                g = b = 255;
            }
            else if(map[y, x]) {
                r = g = b = 0;
            }
            else {
                r = g = b = 255;
            }

            for(size_t sy = 0; sy < image_scaling; ++sy) {
                for(size_t sx = 0; sx < image_scaling; ++sx) {
                    size_t px = x * image_scaling + sx;
                    size_t py = y * image_scaling + sy;

                    size_t index = (py * width + px) * channels;

                    pixels[index++] = r;
                    pixels[index++] = g;
                    pixels[index++] = b;
                }
            }
        }
    }

    stbi_write_png(filename.data(), width, height, channels, pixels.data(), width * channels);
}
