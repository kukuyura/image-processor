//
// Created by yukuk on 23.03.2022.
//
#pragma once

#include <vector>

#include "grayscale.h"
#include "image.h"
#include "linearfilter.h"

class EdgeDetection : public Filter {
public:
    EdgeDetection(double threshold)
        : lf_(LinearFilter(-1, -1, {{0.0, -1.0, 0.0}, {-1.0, 4.0, -1.0}, {0.0, -1.0, 0.0}})), threshold_(threshold){};
    Image Apply(const Image &) override;

private:
    Grayscale gs_;
    LinearFilter lf_;
    double threshold_;
};
