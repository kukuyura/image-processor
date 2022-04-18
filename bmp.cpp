//
// Created by yukuk on 20.03.2022.
//
#include "bmp.h"

#include <iostream>
#include <vector>

void BMP::Read(const std::string& path, Image& img) const {
    std::ifstream fin(path, std::ios::binary);
    std::vector<char> header(54);
    fin.read(header.data(), header.size());
    int64_t width = static_cast<int64_t>(ReadFromBuffer<uint32_t>(&header[18]));
    int64_t height = static_cast<int64_t>(ReadFromBuffer<uint32_t>(&header[22]));
    uint16_t depth = ReadFromBuffer<uint16_t>(&header[28]);
    if (depth != 24) {
        throw std::runtime_error("Only BMP-24 is supported by now");
    }
    img = Image(height, width);
    for (int64_t i = height - 1; - 1 < i; --i) {
        for (int64_t j = 0; j < width; ++j) {
            std::vector<char> buffer(3);  // Using vector is unnecessarily, but that makes code more readable
            fin.read(buffer.data(), buffer.size());
            img.At(i, j) =
                Image::Color(static_cast<double>(ReadFromBuffer<unsigned char>(&buffer[0])) / color_conversion_ratio_,
                             static_cast<double>(ReadFromBuffer<unsigned char>(&buffer[1])) / color_conversion_ratio_,
                             static_cast<double>(ReadFromBuffer<unsigned char>(&buffer[2])) / color_conversion_ratio_);
        }
        std::vector<char> padding(CalculatePaddingSize(img.GetWidth()));
        fin.read(padding.data(), padding.size());
    }
}

void BMP::Write(const std::string& path, const Image& img) const {
    std::ofstream fout(path, std::ios::binary);
    size_t padding_size = CalculatePaddingSize(img.GetWidth());
    size_t height = img.GetHeight();
    size_t width = img.GetWidth();
    WriteToBuffer(fout, 'B', 1);                                       // The header field
    WriteToBuffer(fout, 'M', 1);                                       // The header field
    WriteToBuffer(fout, 54 + (3 * width + padding_size) * height, 4);  // The size of BMP file
    WriteToBuffer(fout, 0, 2);                                         // Reserved
    WriteToBuffer(fout, 0, 2);                                         // Reserved
    WriteToBuffer(fout, 54, 4);                                        // The offset
    WriteToBuffer(fout, 40, 4);                                        // Size of this header
    WriteToBuffer(fout, width, 4);                                     // Width
    WriteToBuffer(fout, height, 4);                                    // Height
    WriteToBuffer(fout, 1, 2);                                         // The number of color planes
    WriteToBuffer(fout, 24, 2);                                        // Depth
    WriteToBuffer(fout, 0, 4);                                         // The compression method
    WriteToBuffer(fout, 0, 4);                                         // The image size
    WriteToBuffer(fout, 11811, 4);                                     // The horizontal resolution of the image
    WriteToBuffer(fout, 11811, 4);                                     // The vertical resolution of the image
    WriteToBuffer(fout, 0, 4);                                         // The number of colors in the color palette
    WriteToBuffer(fout, 0, 4);                                         // The number of important colors use
    for (int64_t i = img.GetHeight() - 1; - 1 < i; --i) {
        for (int64_t j = 0; j < img.GetWidth(); ++j) {
            WriteToBuffer(fout, static_cast<unsigned char>(color_conversion_ratio_ * img.At(i, j).r), 1);
            WriteToBuffer(fout, static_cast<unsigned char>(color_conversion_ratio_ * img.At(i, j).g), 1);
            WriteToBuffer(fout, static_cast<unsigned char>(color_conversion_ratio_ * img.At(i, j).b), 1);
        }
        WriteToBuffer(fout, 0, padding_size);
    }
}

size_t BMP::CalculatePaddingSize(size_t width) {
    return (24 * width + 31) / 32 * 4 - 3 * width;
}
