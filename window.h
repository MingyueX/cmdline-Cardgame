#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
    Display *d;
    Window w;
    int s;
    GC gc;
    unsigned long colours[10];

  public:
    Xwindow(int width=830, int height =780);  // Constructor; displays the window.
    ~Xwindow();                              // Destructor; destroys the window.
    Xwindow(const Xwindow&) = delete; // disallow copy ctor
    Xwindow &operator=(const Xwindow&) = delete; // disallow copy assignment

    enum {White=0, Black, CadetBlue, LightGray, LightBlue, LightCoral, WebGray, LSGray, SteelBlue, IndianRed, Orange}; // Available colours.
//    enum {White=0, Black, Red, Green, Blue, Aquamarine}; // Available colours.

    // Draws a rectangle
    void fillRectangle(int x, int y, int width, int height, int colour=Black);

    // Draws a string
    void drawString(int x, int y, std::string msg, int colour=White);

    void drawTitle(int x, int y, std::string msg, int colour=White);
};
#endif
