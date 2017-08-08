#include <iostream>
#include "ColorWindow.h"

using namespace std;

int getRandomColor();

/*
  FIXME 1 a : Complete callback function called buttonCallback() 
    don't forget the parameters.
	The first parameter will
    be a pointer that can be static_cast to a ColorButton
	The second parameter will
    be a pointer that can be static_cast to a ColorWindow
    - Set the window's background color to a randomly generated 
       color obtained by calling getRandomColor()
*/

void buttonCallback(Fl_Widget* w, void* v){
    
}

ColorWindow::ColorWindow(int width = 400, int height = 200) :
	Fl_Window(width, height) {
	this->color(getRandomColor());
	buttonOne = new ColorButton(50, 50, 100, 50, "One");
	buttonTwo = new ColorButton(50, 175, 100, 50, "Two");
         
	/*
	  FIXME 1 b
	  Register a callback with buttonOne and buttonTwo
	    with buttonCallback (from FIXME 1a) and this
		  instance of ColorWindow as parameters
	*/
         

	this->end();
}