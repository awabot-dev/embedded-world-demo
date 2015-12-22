# embedded-world-demo

##Introduction

For this demo, we will need *Herta software* and *Awabot WebRTC backend* to run simultaneously on the robot. These two parts will require the same resource : the Xtion camera stream. The main goal is to have a system able to provide them the stream and permit them to work correctly.

##Architecture

###Existing

To trasmit the Xtion stream, from the device to the web page, *Awabot* is using two software bricks, working on client/server architecture. The server, called *WebRTC Bridge*, is responsible to grab frames from Xtion and send it over the network (on localhost). The client, called *WebRTC Backend*, is intended to receive those frames and give them to WebRTC in order to send them to the web page.

###For the demo
Since *Herta software* and *Awabot WebRTC backend* must have the stream at the same time, keeping client/server architecture is a good solution. We developed a new software brick, which is a C++ library based on GStreamer, responsible to receive RGB24 frame from *WebRTC bridge* and pull them up via a callback. This brick is usable, as input, both in *Herta software* and *Awabot WebRTC backend*

##Building

### xtionstreamserver
```
$ cd xtionstreamserver
$ qmake
$ make
```

### xtionstreamclient
```
$ cd xtionstreamclient
$ make
```

## Dependencies

### xtionstreamserver
* *qt5-default*
* *libopenni2-dev*

### xtionstreamclient
* *libgstreamer1.0-dev*
* *libgstreamer-plugins-base1.0-dev*

##Running

To run this example, simply launch xtionstreamserver first in a terminal, then launch xtionstreamclient in another terminal

##Integration

To integrate this library into an existing software, just extends the class IXtionStreamClient and set it as a XtionStreamClient instance listener, like in main.cpp

*Note: XtionStreamClient.run() is launching GStreamer pipeline loop, so it's a blocking function*

##Architecture

![alt text](https://raw.githubusercontent.com/awabot-dev/embedded-world-demo/master/doc/Embedded-world-architecture.png "Architecture")
