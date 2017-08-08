#include <iostream>
#include "Viewer.h"

using namespace std;

void buttonCallback(Fl_Widget* widget, void* viewerPtr) {
	NavButton* button = static_cast<NavButton*>(widget);
	Viewer* viewer = static_cast<Viewer*>(viewerPtr);
	int count = button->getClickCount();
	int total = button->getTotalClicks();
	cout << button->getLabel() <<" has been pressed "<< count << " times." << endl;
	cout << "All buttons have been pressed " << total << " times." << endl << endl;

	viewer->navPressed(widget); 
	/* you can name this whatever you want, the idea is to call a 
	     member function in the viewer class that does what is needed
	     to update the image. You'll pass in the widget (you can also
	     dynamic cast it to a NavButton before passing it). From the
	     widget the function can determine whether to move forward
	     or backward in the list.
	*/
}

Viewer::Viewer(string imageFolder, vector<string> imageFilenames, int width = 800, int height = 600) :
	Fl_Window(width, height, "Image Viewer"), imageFolder(imageFolder), imageFilenames(imageFilenames), currentIndex(0),
	prev(nullptr), next(nullptr), imageBox(nullptr), pic(nullptr) {
  	prev = new NavButton(getPathFilename(imageFilenames.at(imageFilenames.size()-1), true),
		"Previous Button",
		borderSize,
		this->h() - borderSize - thumbnailSize - borderSize,
		thumbnailSize, imageFilenames.size() - 1);
	next = new NavButton(getPathFilename(imageFilenames.at((imageFilenames.size()+1)%imageFilenames.size()), true),
		"Next Button", 
		this->w() - borderSize - thumbnailSize - borderSize,
		this->h() - borderSize - thumbnailSize - borderSize, 
		thumbnailSize, imageFilenames.size()-1);
	imageBox = new Fl_Box(borderSize, 
		borderSize, 
		this->w() - (2*borderSize), 
		this->h() - (2*borderSize) - thumbnailSize - 2*borderSize);
	//imageBox->box(FL_BORDER_BOX); // useful to see where the full size of the widget holding the images

	pic = new Fl_JPEG_Image(getPathFilename(imageFilenames.at(currentIndex)).c_str());
	imageBox->image(pic);

	prev->callback(buttonCallback, static_cast<void*>(this));
	next->callback(buttonCallback, static_cast<void*>(this));


	this->end();
}

void Viewer::navPressed(Fl_Widget* widget){
	NavButton* button = static_cast<NavButton*>(widget);
	if(button->getLabel() == "Previous Button"){
		currentIndex--;
		if(currentIndex < 0){
			currentIndex = imageFilenames.size()-1;
		}
		int currentIndexPrev = currentIndex-1;
		if(currentIndexPrev < 0){
			currentIndexPrev = imageFilenames.size()-1;
		}
		pic = new Fl_JPEG_Image(getPathFilename(imageFilenames.at(currentIndex)).c_str());
		imageBox->image(pic);
	}
	else{
		currentIndex++;
		if(currentIndex == imageFilenames.size()){
			currentIndex = 0;
		}
		pic = new Fl_JPEG_Image(getPathFilename(imageFilenames.at(currentIndex)).c_str());
		imageBox->image(pic);

	}
	int prevIndex = currentIndex-1;
	if(prevIndex == -1){
		prevIndex = imageFilenames.size()-1;
	}
	int nextIndex = currentIndex+1;
	if(nextIndex == imageFilenames.size()){
		nextIndex = 0;
	}
	string prevImage1 = getPathFilename(imageFilenames.at(prevIndex));
	string nextImage1 = getPathFilename(imageFilenames.at(nextIndex));

	string prevImage = imageFolder + "/t_" + prevImage1.substr(imageFolder.size()+1);
	string nextImage = imageFolder + "/t_" + nextImage1.substr(imageFolder.size()+1);
	
	//cout << prevImage << endl;
	//cout << nextImage << endl;
	//cout << prevImage << " " << nextImage << endl;
	prev->setImage(prevImage);
	next->setImage(nextImage);

	this->redraw();
}

string Viewer::getPathFilename(string filename, bool thumb) {
	string thumbPart = "";
	if (thumb) thumbPart = "t_";
	return imageFolder + "/" + thumbPart+ filename;
}