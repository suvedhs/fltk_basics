#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <FL/Fl.H>
#include <FL/Fl_Button.H>

class ColorButton : public Fl_Button {
	int clickCount;

public:
	ColorButton(int x, int y, int width, int height, const char *L);
};
#endif