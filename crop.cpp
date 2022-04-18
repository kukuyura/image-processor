//
// Created by yukuk on 23.03.2022.
//
#include "crop.h"

#include <algorithm>

Image Crop::Apply(const Image& img) {
    Image ret(std::min(img.GetHeight(), new_height_), std::min(img.GetWidth(), new_width_));
    for (int64_t i = 0; i < new_height_; ++i) {
        for (int64_t j = 0; j < new_width_; ++j) {
            ret.At(i, j) = img.At(i, j);
        }
    }
    return ret;
}
