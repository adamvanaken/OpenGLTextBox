#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// To suppress deprecation warnings
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "callbacks.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <string>

void *font=(int*)GLUT_BITMAP_9_BY_15;

int rasterpos[2];
int LINE_HEIGHT = 15;
int LINE_WIDTH = 9;

int MARGIN = 10;

bool _renderCursor = true;

void cursorLoop(int i) {
    _renderCursor = !_renderCursor;
    glutPostRedisplay();
    glutTimerFunc(500, cursorLoop, 0);
} 

bool isChatTextEmpty() {
    return _chatTextIndex == 0 && (_chatText.size() == 0 || _chatText[0].length() == 0);
}

void DrawRect(int x, int y, int w, int h)
{
    glBegin(GL_POLYGON);
        glVertex2f(x - w/2, y - h/2);
        glVertex2f(x - w/2, y + h/2);
        glVertex2f(x + w/2, y + h/2);
        glVertex2f(x + w/2, y - h/2);
    glEnd();
}

void DrawString(int x, int y, std::string str)
{
    const char *c;
    glRasterPos2f(x, y);
    for (c=&str[0]; *c != '\0'; c++)
    {
        glGetIntegerv(GL_CURRENT_RASTER_POSITION, rasterpos);
        if (*c != '\n') {
            if (rasterpos[0] > WIDTH-(4*LINE_WIDTH)) {
                y -= LINE_HEIGHT;
                glRasterPos2f(x, y);
            }
            glutBitmapCharacter(font, *c);
        }
    }
}

void init() {
    // Set the clear color to black
    glClearColor(0.7, 0.7, 0.7, 1);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1, 1.0, -1, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(void) {
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    glColor4f(1, 1, 1, 1);

    /* DRAW INPUT BOX */
    DrawRect(WIDTH/2, HEIGHT * 0.15 + MARGIN, WIDTH - (2*MARGIN), HEIGHT * 0.3);

    /* DRAW LOG BOX */
    DrawRect(WIDTH/2, HEIGHT - (HEIGHT * 0.3) - MARGIN, WIDTH - (2*MARGIN), HEIGHT * 0.6);

    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

    /* DRAW CHAT LOG */
    int visibleLines = (HEIGHT * 0.6) / LINE_HEIGHT - 1;
    int x = 1;
    int i = 0;
    if (_chatLog.size() > visibleLines) {
        i = _chatLog.size() - visibleLines;
    }
    for(; i != _chatLog.size(); i++) {
        DrawString(MARGIN*2, (HEIGHT - MARGIN) - LINE_HEIGHT * x, _chatLog[i]);
        x++;
    }

    /* DRAW INPUT TEXT */
    visibleLines = (HEIGHT * 0.3) / LINE_HEIGHT - 1;
    x = 1;
    i = 0;
    if (_chatText.size() > visibleLines) {
        i = _chatText.size() - visibleLines;
    }
    for(; i != _chatText.size(); i++) {
        DrawString(MARGIN*2, (MARGIN + HEIGHT * 0.3) - LINE_HEIGHT * x, _chatText[i]);
        x++;
    }

    /* DRAW CURSOR */
    glGetIntegerv(GL_CURRENT_RASTER_POSITION, rasterpos);

    if (isChatTextEmpty()) {
        glRasterPos2f(MARGIN*2, (MARGIN + HEIGHT * 0.3) - LINE_HEIGHT);
        glGetIntegerv(GL_CURRENT_RASTER_POSITION, rasterpos);
    }
    if (_renderCursor) {
        DrawString(rasterpos[0], rasterpos[1], "|");
    }
    
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    // Initializes GLUT and processes commandline arguments, if any
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WIDTH,HEIGHT);
    
    glutCreateWindow("MegaHurtz Chat");

    // Callback Registration
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardCallback);
    glutMouseFunc(mouseCallback);
    glutReshapeFunc(reshapeCallback);

    init();

    // Pass program control to tk's event handling code
    // In other words, loop forever
    glutTimerFunc(500, cursorLoop, 0);
    glutMainLoop();

    return 0;
}
