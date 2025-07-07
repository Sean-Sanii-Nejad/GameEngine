// include/graphics/Texture2D.h
#pragma once
#include <string>

class Texture2D {
public:
    unsigned int ID;
    int Width, Height;

    Texture2D(const std::string& path);
    ~Texture2D();

    void Bind(unsigned int slot = 0) const;
};
