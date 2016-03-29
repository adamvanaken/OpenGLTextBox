#include "callbacks.h"

double mouseX, mouseY;
double mouseMoveX, mouseMoveY;

int WIDTH = 300, HEIGHT = 400;

std::vector<std::string> _chatText;
std::vector<std::string> _chatLog;
int _chatTextIndex = 0;

std::string name = "Adam";

void recvMsg(std::string s) {

    s = name + ": " + s;

    int stride = (WIDTH - (3*LINE_WIDTH))/LINE_WIDTH - 3;

    std::istringstream ss(s);
    std::string hold;

    while(std::getline(ss, hold, '\n')){
        for (int i = 0; i < hold.length(); i+=stride) {
            _chatLog.push_back(hold.substr(i, stride));
        }       
    }
}

void sendMsg(std::vector<std::string> s) {
    std::string entireMsg = "";
    for (int i = 0; i < s.size(); i++) {
        entireMsg += s[i];
        // entireMsg += '\n';
    }
    recvMsg(entireMsg);
}

void reshapeCallback(int width, int height)
{
    HEIGHT=height;
    WIDTH=width;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0,HEIGHT);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_MODELVIEW);
}

// int glutGetModifiers(void);
// GLUT_ACTIVE_SHIFT
// Set if the Shift modifier or Caps Lock is active.
// GLUT_ACTIVE_CTRL
// Set if the Ctrl modifier is active.
// GLUT_ACTIVE_ALT
// Set if the Alt modifier is active.
void keyboardCallback(unsigned char key, GLint x, GLint y)
{
    switch (key)
    {
        // ESCAPE
        case 27:
            exit (0);
            break;
        // RETURN
        case 13:
            if (glutGetModifiers() & GLUT_ACTIVE_SHIFT) {
                if (_chatText.size() == 0) {
                    _chatText.push_back("");
                }

                _chatTextIndex++;
                _chatText.push_back("\n");
            } else {
                sendMsg(_chatText);
                _chatText.clear();
                _chatTextIndex = 0;
            }
            break;
        // BACKSPACE
        case 127:
            if (isChatTextEmpty()) {
                break;
            }
            if (_chatText.size() > 0) {

                if (_chatText[_chatTextIndex].length() <= 0) {
                    _chatText.pop_back();
                    _chatTextIndex--;
                    if (_chatTextIndex < 0) {
                        _chatTextIndex = 0;
                    }
                }

                if (_chatText.size() > 0 && _chatText[_chatTextIndex].length() > 0) {
                    // printf("Char: %d\n", _chatText[_chatTextIndex].back());
                    // if (_chatText[_chatTextIndex].back() == '\n') {
                    //     _chatText[_chatTextIndex] = _chatText[_chatTextIndex].substr(0, _chatText[_chatTextIndex].size() - 1);    
                    // }
                    _chatText[_chatTextIndex] = _chatText[_chatTextIndex].substr(0, _chatText[_chatTextIndex].size() - 1);
                }
            }
            break;
        default:
            if (_chatText.size() == 0) {
                _chatText.push_back("");
            }

            int stride = (WIDTH - (3*LINE_WIDTH))/LINE_WIDTH - 3;
            if (_chatText[_chatTextIndex].length() >= stride) {
                _chatTextIndex++;
                _chatText.push_back("");
            }
            _chatText[_chatTextIndex] += key;
            break;
    }

    glutPostRedisplay();
}

// button = { GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON }
// state = { GLUT_UP, GLUT_DOWN }
void mouseCallback(int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_UP)
            {
               
            }
            break;
    }
}
