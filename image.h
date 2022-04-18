//
// Created by yukuk on 10.03.2022.
//
#pragma once

#include <vector>

class Image {
public:
    class Color {
    public:
        Color() = default;
        Color(double r, double g, double b) : r(r), g(g), b(b){};
        Image::Color operator*(double) const;
        Image::Color operator+(const Color&) const;
        Image::Color operator-(const Color&) const;
        void operator+=(const Color&);
        void Clamp();
        double r;
        double g;
        double b;
    };
    Image() = default;
    Image(int64_t height, int64_t width)
        : height_(height),
          width_(width),
          container_(std::vector<std::vector<Color>>(height, std::vector<Color>(width))){};
    enum OutOfBoundsHandling { CLAMP };
    Color& At(int64_t x, int64_t y, OutOfBoundsHandling out_of_bounds_handling = CLAMP);
    const Color& At(int64_t x, int64_t y, OutOfBoundsHandling out_of_bounds_handling = CLAMP) const;
    int64_t GetHeight() const;
    int64_t GetWidth() const;

private:
    std::pair<int64_t, int64_t> TransformIndices(int64_t x, int64_t y,
                                                 OutOfBoundsHandling out_of_bounds_handling) const;
    int64_t height_;
    int64_t width_;
    std::vector<std::vector<Color>> container_;
};
