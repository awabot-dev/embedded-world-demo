#include <fstream>
#include <iostream>
#include <sstream>

#include "XtionStreamClientListener.h"

void XtionStreamClientListener::onFrame(Frame* frame)
{
	std::cout << "New frame !" << std::endl;

	//TODO frame processing
}
