#include <iostream>
#include "ColorButton.h"

using namespace std;

int getRandomColor();

ColorButton::ColorButton(int x, int y, int width, int height, const char *L = 0) :
	Fl_Button(x, y, width, height, L), clickCount(0) {
	this->labelsize(36);
	this->labelfont(FL_HELVETICA_BOLD);
}



 
 