#ifndef IXTIONSTREAMCLIENT_H
#define IXTIONSTREAMCLIENT_H

struct Frame
{
	char* data;
	int size;
	int width;
	int height;
};

class IXtionStreamClient
{
	public:
		virtual void onFrame(Frame* frame) = 0;
};

#endif
