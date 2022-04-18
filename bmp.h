//
// Created by yukuk on 20.03.2022.
//
#pragma once

#include <limits>
#include <string>

#include "fileformat.h"
#include "image.h"

class BMP : public FileFormat {
public:
    void Read(const std::string &, Image &) const override;
    void Write(const std::string &, const Image &) const override;

private:
    static size_t CalculatePaddingSize(size_t);
    const double color_conversion_ratio_ = std::numeric_limits<unsigned char>::max();
};
