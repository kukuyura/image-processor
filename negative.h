//
// Created by yukuk on 23.03.2022.
//
#pragma once

#include "image.h"
#include "filter.h"

class Negative : public Filter {
public:
    Image Apply(const Image &) override;
};
