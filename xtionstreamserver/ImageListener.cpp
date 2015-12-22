#include "ImageListener.h"

ImageListener::ImageListener(IOpenniImageListener *listener)
	: openni::VideoStream::NewFrameListener()
{
	mListener = listener;
}

void ImageListener::onNewFrame(openni::VideoStream& stream)
{
	stream.readFrame(&mLastFrame);
	mListener->onNewFrame((const char *)mLastFrame.getData(), mLastFrame.getDataSize());
}

