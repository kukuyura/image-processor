//
// Created by yukuk on 23.03.2022.
//
#pragma once

#include <vector>

#include "gaussianblur.h"
#include "grayscale.h"
#include "image.h"

class Canny : public Filter {
public:
    Canny(double upper_threshold, double lower_threshold)
        : blur_(GaussianBlur(1.4)),
          lf1_(-1, -1, {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}, false),
          lf2_(-1, -1, {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}}, false),
          upper_threshold_(upper_threshold),
          lower_threshold_(lower_threshold){};
    Image Apply(const Image&) override;

private:
    Grayscale gs_;
    GaussianBlur blur_;
    LinearFilter lf1_;
    LinearFilter lf2_;
    double upper_threshold_;
    double lower_threshold_;
};
