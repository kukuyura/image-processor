//
// Created by yukuk on 23.03.2022.
//
#pragma once

#include "filter.h"
#include "image.h"

class Crop : public Filter {
public:
    Crop(int64_t new_height, int64_t new_width) : new_height_(new_height), new_width_(new_width){};
    Image Apply(const Image &) override;

private:
    int64_t new_height_;
    int64_t new_width_;
};
