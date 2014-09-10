#ifndef MAIN_H
#define MAIN_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>

bool init();
bool initShaders();
void handleKeys(unsigned char key, int x, int y);
void render();
void update();
void close();
void Screenshot(int x, int y, int w, int h, const char * filename);

#endif // MAIN_H
