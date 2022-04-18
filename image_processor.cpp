#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "bmp.h"
#include "canny.h"
#include "crop.h"
#include "edgedetection.h"
#include "fileformat.h"
#include "gaussianblur.h"
#include "grayscale.h"
#include "image.h"
#include "negative.h"
#include "sharpening.h"

namespace file_operation {
void Read(const FileFormat& ff, const std::string& path, Image& img) {
    ff.Read(path, img);
}

void Write(const FileFormat& ff, const std::string& path, const Image& img) {
    ff.Write(path, img);
}
}  // namespace file_operation

static void CheckFileAndDo(const std::string& path, Image& img,
                           std::function<void(FileFormat&, const std::string&, Image&)> file_operation) {
    try {
        if (path.substr(path.size() - 4, 4) == ".bmp") {
            BMP bmp;
            file_operation(bmp, path, img);
        } else {
            // Here is the place to implement other formats
            throw std::runtime_error("This file format is not supported");
        }
    } catch (...) {
        throw std::runtime_error("Something wrong with input/output");
    }
}

void PrintUsage() noexcept {
    auto print = [](std::string msg) { std::cout << msg << std::endl; };
    print("Welcome to Yukuk's Image Processor");
    print("You should follow this order of arguments to use program:");
    print("I: Input path");
    print("II: Output path");
    print("III+: Filters and their parameters");
    print("Filters list:");
    print("1: Crop (-crop width height)");
    print("2: Grayscale (-gs)");
    print("3: Negative (-neg)");
    print("4: Sharpening (-sharp)");
    print("5: Edge Detection (-edge threshold)");
    print("6: Gaussian Blur (-blur sigma)");
    print("Recommended sigma is 5");
    print("7: Canny (-canny upper_threshold lower_threshold)");
    print("Recommended upper:lower ratio is between 2:1 and 3:1 (Example: -canny 0.3 0.1)");
    print("Supported formats:");
    print("BMP-24");
}

int main(int argc, const char* argv[]) {
    if (argc == 1) {
        PrintUsage();
        return 0;
    }
    if (argc < 3) {
        throw std::runtime_error("No output path");
    }
    std::vector<std::string> arguments;  // Using vector is unnecessarily, but that makes code more readable
    arguments.reserve(argc);
    size_t n = static_cast<size_t>(argc);
    for (size_t i = 0; i < n; ++i) {
        arguments.push_back(argv[i]);
    }
    Image img;
    CheckFileAndDo(arguments.at(1), img, file_operation::Read);
    try {
        for (size_t i = 3; i < n; ++i) {
            std::unique_ptr<Filter> filter;
            if (arguments.at(i) == "-crop") {
                filter = std::make_unique<Crop>(std::stoll(arguments.at(i + 2)), std::stoll(arguments.at(i + 1)));
                i += 2;
            } else if (arguments.at(i) == "-gs") {
                filter = std::make_unique<Grayscale>();
            } else if (arguments.at(i) == "-neg") {
                filter = std::make_unique<Negative>();
            } else if (arguments.at(i) == "-sharp") {
                filter = std::make_unique<Sharpening>();
            } else if (arguments.at(i) == "-edge") {
                filter = std::make_unique<EdgeDetection>(std::stod(arguments.at(i + 1)));
                i += 1;
            } else if (arguments.at(i) == "-blur") {
                filter = std::make_unique<GaussianBlur>(std::stod(arguments.at(i + 1)));
                i += 1;
            } else if (arguments.at(i) == "-canny") {
                filter = std::make_unique<Canny>(std::stod(arguments.at(i + 1)), std::stod(arguments.at(i + 2)));
                i += 2;
            } else {
                throw std::runtime_error("No such filter");
            }
            img = filter->Apply(img);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }
    CheckFileAndDo(arguments.at(2), img, file_operation::Write);
    return 0;
}
