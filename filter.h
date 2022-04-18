//
// Created by yukuk on 23.03.2022.
//
#pragma once

#include "image.h"

class Filter {
public:
    virtual Image Apply(const Image&) = 0;
    virtual ~Filter() = default;
};
