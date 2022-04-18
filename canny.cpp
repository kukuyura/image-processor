//
// Created by yukuk on 23.03.2022.
//
#include "canny.h"

#include <cmath>

Image Canny::Apply(const Image& img) {
    Image img_good = blur_.Apply(gs_.Apply(img));
    Image g_x = lf1_.Apply(img_good);
    Image g_y = lf2_.Apply(img_good);
    Image g = Image(img_good.GetHeight(), img_good.GetWidth());
    Image t = Image(img_good.GetHeight(), img_good.GetWidth());
    for (int64_t i = 0; i < img_good.GetHeight(); ++i) {
        for (int64_t j = 0; j < img_good.GetWidth(); ++j) {  // All colors are equal
            double hypot = std::hypot(g_x.At(i, j).r, g_y.At(i, j).r);
            g.At(i, j) = Image::Color(hypot, hypot, hypot);
            double atan = std::atan2(g_y.At(i, j).r, g_x.At(i, j).r);
            if (atan < 0) {
                atan += M_PI;
            }
            if (atan <= M_PI / 8 || 7 * M_PI / 8 <= atan) {
                atan = 0;
            } else if (M_PI / 8 < atan && atan <= 3 * M_PI / 8) {
                atan = M_PI / 4;
            } else if (3 * M_PI / 8 < atan && atan <= 5 * M_PI / 8) {
                atan = M_PI / 2;
            } else {
                atan = 3.0 * M_PI / 4.0;
            }
            t.At(i, j) = Image::Color(atan, atan, atan);
        }
    }
    for (int64_t i = 1; i < img_good.GetHeight() - 1; ++i) {
        for (int64_t j = 1; j < img_good.GetWidth() - 1; ++j) {
            if ((t.At(i, j).r == 0 && g.At(i, j).r > std::max(g.At(i - 1, j).r, g.At(i + 1, j).r)) ||
                (t.At(i, j).r == M_PI / 4 && g.At(i, j).r > std::max(g.At(i - 1, j - 1).r, g.At(i + 1, j + 1).r)) ||
                (t.At(i, j).r == M_PI / 2 && g.At(i, j).r > std::max(g.At(i, j - 1).r, g.At(i, j + 1).r)) ||
                (t.At(i, j).r == 3 * M_PI / 4 && g.At(i, j).r > std::max(g.At(i + 1, j - 1).r, g.At(i - 1, j + 1).r))) {
                // The first threshold
                if (g.At(i, j).r > upper_threshold_) {
                    img_good.At(i, j) = Image::Color(1, 1, 1);
                } else if (g.At(i, j).r < lower_threshold_) {
                    img_good.At(i, j) = Image::Color(0, 0, 0);
                } else {
                    img_good.At(i, j) = Image::Color(0.5, 0.5, 0.5);
                }
            } else {
                img_good.At(i, j) = Image::Color(0, 0, 0);
            }
        }
    }
    // The second threshold
    Image ret = Image(img_good.GetHeight(), img_good.GetWidth());
    for (int64_t i = 0; i < ret.GetHeight(); ++i) {
        for (int64_t j = 0; j < ret.GetWidth(); ++j) {
            if (img_good.At(i, j).r == 1 ||
                (img_good.At(i, j).r == 0.5 && (img_good.At(i - 1, j - 1).r == 1 || img_good.At(i - 1, j).r == 1 ||
                                                img_good.At(i - 1, j + 1).r == 1 || img_good.At(i, j - 1).r == 1 ||
                                                img_good.At(i, j + 1).r == 1 || img_good.At(i + 1, j - 1).r == 1 ||
                                                img_good.At(i + 1, j).r == 1 || img_good.At(i + 1, j + 1).r == 1))) {
                ret.At(i, j) = Image::Color(1, 1, 1);
            } else {
                ret.At(i, j) = Image::Color(0, 0, 0);
            }
        }
    }
    return ret;
}
