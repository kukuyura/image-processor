//
// Created by yukuk on 23.03.2022.
//
#pragma once

#include <vector>

#include "filter.h"
#include "image.h"

class LinearFilter : public Filter {
public:
    LinearFilter() = default;
    LinearFilter(int64_t vertical_offset, int64_t horizontal_offset, std::vector<std::vector<double>> matrix)
        : vertical_offset_(vertical_offset), horizontal_offset_(horizontal_offset), matrix_(matrix){};
    LinearFilter(int64_t vertical_offset, int64_t horizontal_offset, std::vector<std::vector<double>> matrix, bool do_clamp)
        : vertical_offset_(vertical_offset), horizontal_offset_(horizontal_offset), matrix_(matrix), do_clamp_(do_clamp){};
    Image Apply(const Image &) override;

protected:
    int64_t vertical_offset_;
    int64_t horizontal_offset_;
    std::vector<std::vector<double>> matrix_;
    bool do_clamp_ = true;
};
