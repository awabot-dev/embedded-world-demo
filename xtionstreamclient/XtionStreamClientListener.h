#ifndef XTIONSTREAMCLIENTLISTENER_H
#define XTIONSTREAMCLIENTLISTENER_H

#include "IXtionStreamClient.h"

class XtionStreamClientListener : public IXtionStreamClient
{
	public:
		virtual void onFrame(Frame* frame);
};

#endif
