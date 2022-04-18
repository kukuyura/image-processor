//
// Created by yukuk on 23.03.2022.
//
#pragma once

#include <cmath>
#include <vector>

#include "image.h"
#include "linearfilter.h"

class GaussianBlur : public LinearFilter {
public:
    GaussianBlur(double sigma) {
        int64_t lambda = static_cast<int64_t>(std::ceil(3.0 * sigma));
        std::vector<std::vector<double>> matrix(2 * lambda + 1, std::vector<double>(2 * lambda + 1));
        for (int64_t i = 0; i < 2 * lambda + 1; ++i) {
            for (int64_t j = 0; j < 2 * lambda + 1; ++j) {
                double x = static_cast<double>(i) - static_cast<double>(lambda);
                double y = static_cast<double>(j) - static_cast<double>(lambda);
                matrix[i][j] = 1.0 / (2.0 * M_PI * sigma * sigma) * std::exp(-(x * x + y * y) / (2 * sigma * sigma));
            }
        }
        vertical_offset_ = -static_cast<int64_t>(lambda);
        horizontal_offset_ = -static_cast<int64_t>(lambda);
        matrix_ = matrix;
    };
};
