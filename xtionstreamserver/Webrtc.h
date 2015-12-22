#ifndef WEBRTC_H
#define WEBRTC_H

#include <QDebug>
#include <QList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QThread>

#include <openni2/OpenNI.h>

#include "ImageListener.h"

class Webrtc : public QObject, public IOpenniImageListener
{
	Q_OBJECT

	public:
		Webrtc() : mColorListener(this)
		{
			buffer = NULL;
			mServer = new QTcpServer(this);
			mServer->listen(QHostAddress::Any, 7070);

			connect(mServer, SIGNAL(newConnection()), this, SLOT(newConnection()));

			openni::OpenNI::initialize();
			mDevice.open(openni::ANY_DEVICE);
			mColorStream.create(mDevice, openni::SENSOR_COLOR);
			mColorStream.addNewFrameListener(&mColorListener);

			openni::VideoMode mode;
			mode.setFps(30);
			mode.setPixelFormat(openni::PIXEL_FORMAT_RGB888);
			mode.setResolution(640, 480);
			mColorStream.setVideoMode(mode);
			mColorStream.setMirroringEnabled(false);
			mColorStream.start();
		}

		~Webrtc()
		{
			mColorStream.stop();
			mColorStream.removeNewFrameListener(&mColorListener);
			mColorStream.destroy();
			mDevice.close();

			openni::OpenNI::shutdown();
		}

		virtual void onNewFrame(const char *data, unsigned int s)
		{
			buffer = data;
			size = s;

			QMetaObject::invokeMethod(this, "newFrame");
		}

	private:
		QTcpServer *mServer;
		QList<QTcpSocket *> mClients;

		int size;
		const char *buffer;

		openni::Device mDevice;
		openni::VideoStream mColorStream;
		ImageListener mColorListener;

	private slots:
		void newFrame()
		{
			foreach(QTcpSocket *c, mClients)
			{
				c->write(buffer, size);
			}
		}

		void newConnection()
		{
			qDebug() << "conn";

			QTcpSocket *client = mServer->nextPendingConnection();
			connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));

			mClients.append(client);
		}

		void disconnected()
		{
			qDebug() << "disconn";

			QTcpSocket *client = (QTcpSocket *)sender();
			mClients.removeOne(client);
		}
};

#endif

