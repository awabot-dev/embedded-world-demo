#ifndef XTIONSTREAMCLIENT_H
#define XTIONSTREAMCLIENT_H

#include <gst/gst.h>

#include "IXtionStreamClient.h"

class XtionStreamClient
{
	public:
		XtionStreamClient();
		~XtionStreamClient();

		void setListener(IXtionStreamClient* listener);
		void run();

	protected:
		static GstFlowReturn onOutputBuffer(GstElement* element, void* data);

		int mArgc;
		char** mArgv;

		Frame* mFrame;
		int mFrameBufferOffset;

		IXtionStreamClient* mListener;
};

#endif
