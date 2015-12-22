#include <iostream>
#include <unistd.h>

#include "XtionStreamClient.h"
#include "XtionStreamClientListener.h"

int main()
{
	XtionStreamClient client;

	XtionStreamClientListener listener;
	client.setListener(&listener);

	client.run();
	return 0;
}
