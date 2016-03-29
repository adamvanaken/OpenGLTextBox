#pragma once

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

extern int HEIGHT, WIDTH;
extern std::vector<std::string> _chatText;
extern std::vector<std::string> _chatLog;
extern int _chatTextIndex;

extern int LINE_HEIGHT;
extern int LINE_WIDTH;

extern bool isChatTextEmpty();

void reshapeCallback(int width, int height);

void keyboardCallback(unsigned char key, GLint x, GLint y);

void mouseCallback(int button, int state, int x, int y);