//
// Created by yukuk on 23.03.2022.
//
#include "edgedetection.h"

Image EdgeDetection::Apply(const Image& img) {
    Image ret = lf_.LinearFilter::Apply(gs_.Apply(img));
    for (int64_t i = 0; i < ret.GetHeight(); ++i) {
        for (int64_t j = 0; j < ret.GetWidth(); ++j) {
            if (ret.At(i, j).r > threshold_) {  // All colors are equal
                ret.At(i, j) = Image::Color(1, 1, 1);
            } else {
                ret.At(i, j) = Image::Color(0, 0, 0);
            }
        }
    }
    return ret;
}
