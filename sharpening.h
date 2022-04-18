//
// Created by yukuk on 23.03.2022.
//
#pragma once

#include <vector>

#include "image.h"
#include "linearfilter.h"

class Sharpening : public LinearFilter {
public:
    Sharpening() : LinearFilter(-1, -1, {{0.0, -1.0, 0.0}, {-1.0, 5.0, -1.0}, {0.0, -1.0, 0.0}}){};
};
