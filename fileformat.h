//
// Created by yukuk on 20.03.2022.
//
#pragma once

#include <fstream>
#include <string>

#include "image.h"

class FileFormat {
public:
    virtual void Read(const std::string& path, Image& img) const = 0;
    virtual void Write(const std::string& path, const Image& img) const = 0;

protected:
    template <typename T>
    static T ReadFromBuffer(char* address) {
        return *reinterpret_cast<T*>(address);
    }
    template <typename T>
    static void WriteToBuffer(std::ofstream& fout, T* address, size_t n) {
        fout.write(reinterpret_cast<char*>(address), n);
    }
    template <typename T>
    static void WriteToBuffer(std::ofstream& fout, T object, size_t n) {
        WriteToBuffer(fout, &object, n);
    }
};
