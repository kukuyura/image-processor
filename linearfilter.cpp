//
// Created by yukuk on 23.03.2022.
//
#include "linearfilter.h"

Image LinearFilter::Apply(const Image& img) {
    Image ret(img.GetHeight(), img.GetWidth());
    for (int64_t i = 0; i < img.GetHeight(); ++i) {
        for (int64_t j = 0; j < img.GetWidth(); ++j) {
            for (int64_t k = 0; k < static_cast<int64_t>(matrix_.size()); ++k) {
                for (int64_t l = 0; l < static_cast<int64_t>(matrix_.at(0).size()); ++l) {
                    ret.At(i, j) += (img.At(i + vertical_offset_ + k, j + horizontal_offset_ + l) * matrix_[k][l]);
                }
            }
            if (do_clamp_) {
                ret.At(i, j).Clamp();
            }
        }
    }
    return ret;
}
