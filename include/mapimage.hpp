#pragma once

#include <string_view>

#include "piece.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

inline size_t __image_scaling = 1;

inline void set_scale(size_t n) noexcept {
    __image_scaling = n;
}

inline void save_map_png(const Map<128, 128>& map, const std::vector<Position>& path,
                         const std::string_view& filename) {
    const size_t width = map.width() * __image_scaling;
    const size_t height = map.height() * __image_scaling;

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
            else if(map[y, x]) {
                r = g = b = 0;
            }
            else {
                r = g = b = 255;
            }

            for(size_t sy = 0; sy < __image_scaling; ++sy) {
                for(size_t sx = 0; sx < __image_scaling; ++sx) {
                    size_t px = x * __image_scaling + sx;
                    size_t py = y * __image_scaling + sy;

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
