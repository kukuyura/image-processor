//
// Created by yukuk on 10.03.2022.
//
#include "image.h"

#include <algorithm>

Image::Color Image::Color::operator*(double val) const {
    return Image::Color(r * val, g * val, b * val);
}

Image::Color Image::Color::operator+(const Color& other) const {
    return Image::Color(r + other.r, g + other.g, b + other.b);
}

Image::Color Image::Color::operator-(const Color& other) const {
    return *this + (other * (-1));
}

void Image::Color::operator+=(const Color& other) {
    r += other.r;
    g += other.g;
    b += other.b;
}

void Image::Color::Clamp() {
    r = std::clamp(r, 0.0, 1.0);
    g = std::clamp(g, 0.0, 1.0);
    b = std::clamp(b, 0.0, 1.0);
}

std::pair<int64_t, int64_t> Image::TransformIndices(int64_t x, int64_t y,
                                                    OutOfBoundsHandling out_of_bounds_handling) const {
    if (out_of_bounds_handling == CLAMP) {
        return std::make_pair(std::clamp(x, static_cast<int64_t>(0), height_ - 1),
                              std::clamp(y, static_cast<int64_t>(0), width_ - 1));
    }  // here is place to implement other handling types
    throw std::runtime_error("This handling type is not supported");
}

Image::Color& Image::At(int64_t x, int64_t y, OutOfBoundsHandling out_of_bounds_handling) {
    auto [x_good, y_good] = TransformIndices(x, y, out_of_bounds_handling);
    return container_.at(x_good).at(y_good);
}

const Image::Color& Image::At(int64_t x, int64_t y, OutOfBoundsHandling out_of_bounds_handling) const {
    auto [x_good, y_good] = TransformIndices(x, y, out_of_bounds_handling);
    return container_.at(x_good).at(y_good);
}

int64_t Image::GetHeight() const {
    return height_;
}

int64_t Image::GetWidth() const {
    return width_;
}
