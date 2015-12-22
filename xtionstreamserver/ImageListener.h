#ifndef OPENNI_IMAGELISTENER_H
#define OPENNI_IMAGELISTENER_H

#include <openni2/OpenNI.h>

class IOpenniImageListener
{
	public:
		virtual void onNewFrame(const char *data, unsigned int size) = 0;
};

class ImageListener : public openni::VideoStream::NewFrameListener
{
	public:
		ImageListener(IOpenniImageListener *listener);

		void onNewFrame(openni::VideoStream& stream);

	protected:
		IOpenniImageListener *mListener;
		openni::VideoFrameRef mLastFrame;
};

#endif

