CC      = g++
CFLAGS  = `pkg-config --cflags gstreamer-base-1.0`
LDFLAGS = `pkg-config --libs gstreamer-base-1.0`

SRCFILES = $(wildcard *.cpp)

all:
	$(CC) -o xtionstreamclient $(SRCFILES) $(CFLAGS) $(LDFLAGS)

