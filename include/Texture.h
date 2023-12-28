#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "stb_image.h"

class Texture
{
public:
    unsigned int texture_id;
    int width, height, nrChannels;

    Texture(const std::string &path);

    void config_wrapping_filtering();
};
