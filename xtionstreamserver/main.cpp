#include <iostream>
#include <signal.h>

#include <QCoreApplication>

#include "Webrtc.h"

Webrtc *w;

void sig_handler(int sig)
{
	std::cout << "sigint" << std::endl;
	delete w;
	exit(0);
}

int main(int argc, char **argv)
{
	QCoreApplication app(argc, argv);

	struct sigaction act;
	act.sa_handler = sig_handler;
	sigaction(SIGINT, &act, NULL);

	w = new Webrtc;

	app.exec();

	return 0;
}

