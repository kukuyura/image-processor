//
// Created by yukuk on 23.03.2022.
//
#include "grayscale.h"

Image Grayscale::Apply(const Image& img) {
    Image ret(img.GetHeight(), img.GetWidth());
    for (int64_t i = 0; i < img.GetHeight(); ++i) {
        for (int64_t j = 0; j < img.GetWidth(); ++j) {
            double val = 0.299 * img.At(i, j).r + 0.587 * img.At(i, j).g + 0.114 * img.At(i, j).b;
            ret.At(i, j) = Image::Color(val, val, val);
        }
    }
    return ret;
}
