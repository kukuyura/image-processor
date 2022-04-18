//
// Created by yukuk on 23.03.2022.
//
#pragma once

#include "filter.h"
#include "image.h"

class Grayscale : public Filter {
public:
    Image Apply(const Image &) override;
};
