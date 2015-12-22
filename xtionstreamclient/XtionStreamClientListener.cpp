#include <fstream>
#include <iostream>
#include <sstream>

#include "XtionStreamClientListener.h"

void XtionStreamClientListener::onFrame(Frame* frame)
{
	std::cout << "New frame !" << std::endl;

	//TODO

	/*
	static int frameCount = 0;

	std::ostringstream fileName;
	fileName << "/tmp/frame" << (++frameCount < 10 ? "0" : "") << frameCount << ".rgb24";

	std::ofstream file(fileName.str().c_str());
	file.write(frame->data, frame->size);
	file.close();

	std::cout << fileName.str() << " dumped" << std::endl;
	*/
}
