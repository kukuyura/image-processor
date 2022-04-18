//
// Created by yukuk on 23.03.2022.
//
#include "negative.h"

Image Negative::Apply(const Image& img) {
    Image ret(img.GetHeight(), img.GetWidth());
    for (int64_t i = 0; i < img.GetHeight(); ++i) {
        for (int64_t j = 0; j < img.GetWidth(); ++j) {
            ret.At(i, j) = Image::Color(1, 1, 1) - img.At(i, j);
        }
    }
    return ret;
}
