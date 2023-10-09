#pragma once
#include <glfw3.h>

bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);
