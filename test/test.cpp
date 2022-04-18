#include <gtest/gtest.h>

#include <string>

#include "bmp.h"
#include "crop.h"
#include "grayscale.h"
#include "image.h"
#include "negative.h"

TEST(BMPTest, DoesBasicStuff) {
    Image white = Image(1080, 1920);
    for (int64_t i = 0; i < white.GetHeight(); ++i) {
        for (int64_t j = 0; j < white.GetWidth(); ++j) {
            white.At(i, j) = Image::Color(1, 1, 1);
        }
    }
    BMP bmp;
    std::string path = "test.bmp";
    bmp.Write(path, white);
    Image white_check;
    bmp.Read(path, white_check);
    EXPECT_EQ(white_check.GetHeight(), 1080);
    EXPECT_EQ(white_check.GetWidth(), 1920);
    EXPECT_DOUBLE_EQ(white_check.At(0, 0).r, 1);
}

TEST(ImageTest, DoesBasicStuff) {
    Image img1 = Image(1080, 1920);
    Image img2 = Image(1080, 1920);
    int64_t i = img1.GetHeight() - 1;
    int64_t j = img2.GetWidth() - 1;
    img1.At(i, j) = Image::Color(-1, -1, -1);
    img1.At(i, j).Clamp();
    img1.At(i, j) += Image::Color(0.3, 0.4, 0.5) + Image::Color(0.5, 0.4, 0.3);
    img2.At(i, j) = (img1.At(i, j) - Image::Color(0.6, 0.6, 0.6)) * 4;
    EXPECT_DOUBLE_EQ(img1.At(i, j).r, img2.At(i, j).r);
}

TEST(CropTest, DoesBasicStuff) {
    Image img1(1080, 1920);
    Crop crop = Crop(720, 1280);
    Image img2 = crop.Apply(img1);
    EXPECT_EQ(img2.GetHeight(), 720);
    EXPECT_EQ(img2.GetWidth(), 1280);
}

TEST(CropTest, HandlesBigInput) {
    Image img1(1080, 1920);
    Crop crop = Crop(2160, 3840);
    Image img2 = crop.Apply(img1);
    EXPECT_EQ(img2.GetHeight(), 1080);
    EXPECT_EQ(img2.GetWidth(), 1920);
}

TEST(GrayscaleTest, DoesBasicStuff) {
    Image red = Image(1080, 1920);
    for (int64_t i = 0; i < red.GetHeight(); ++i) {
        for (int64_t j = 0; j < red.GetWidth(); ++j) {
            red.At(i, j) = Image::Color(1, 0, 0);
        }
    }
    Grayscale gs;
    Image gray_check = gs.Apply(red);
    EXPECT_DOUBLE_EQ(gray_check.At(0, 0).r, gray_check.At(0, 0).g);
    EXPECT_DOUBLE_EQ(gray_check.At(0, 0).g, gray_check.At(0, 0).b);
    EXPECT_DOUBLE_EQ(gray_check.At(0, 0).b, gray_check.At(0, 0).r);
}

TEST(NegativeTest, DoesBasicStuff) {
    Image green = Image(1080, 1920);
    for (int64_t i = 0; i < green.GetHeight(); ++i) {
        for (int64_t j = 0; j < green.GetWidth(); ++j) {
            green.At(i, j) = Image::Color(0, 1, 0);
        }
    }
    Negative neg;
    Image neg_check = neg.Apply(green);
    EXPECT_DOUBLE_EQ(neg_check.At(0, 0).r, 1);
    EXPECT_DOUBLE_EQ(neg_check.At(0, 0).g, 0);
    EXPECT_DOUBLE_EQ(neg_check.At(0, 0).b, 1);
}
