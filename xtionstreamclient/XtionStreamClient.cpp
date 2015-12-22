#include <cstring>
#include <iostream>

#include <glib.h>
#include <gst/base/gstbasesink.h>

#include "XtionStreamClient.h"

XtionStreamClient::XtionStreamClient()
{
	mFrame = new Frame;
	mFrame->width = 640;
	mFrame->height = 480;
	mFrame->size = mFrame->width * mFrame->height * 3;
	mFrame->data = new char[mFrame->size];
	
	mFrameBufferOffset = 0;
	mListener = 0;
}

XtionStreamClient::~XtionStreamClient()
{
	delete mFrame->data;
	delete mFrame;
}

void XtionStreamClient::setListener(IXtionStreamClient* listener)
{
	mListener = listener;
}

void XtionStreamClient::run()
{
	int argc = 1;
	char** argv = new char*[1];
	argv[0] = (char*)"bin";

	gst_init(&argc, &argv);

	GstElement* pipeline = gst_pipeline_new("pipeline");

	GstElement* sourceElement = gst_element_factory_make("tcpclientsrc", "pipelineSource");
	GstElement* destinationElement = gst_element_factory_make("appsink", "pipelineDestination");

	g_object_set(sourceElement, "host", "localhost", NULL);
	g_object_set(sourceElement, "port", 7070, NULL);

	gst_bin_add_many(GST_BIN(pipeline), sourceElement, destinationElement, NULL);
	gst_element_link_many(sourceElement, destinationElement, NULL);

	g_object_set(destinationElement, "emit-signals", TRUE, NULL);
	g_signal_connect(destinationElement, "new-sample", G_CALLBACK(XtionStreamClient::onOutputBuffer), this);
	
	gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);

	std::cout << "GStreamer setup done" << std::endl;
	g_main_loop_run(g_main_loop_new(NULL, true));
}

GstFlowReturn XtionStreamClient::onOutputBuffer(GstElement* element, void* data)
{
	XtionStreamClient* self = (XtionStreamClient*)data;
	
	GstSample* sample = gst_base_sink_get_last_sample(GST_BASE_SINK(element));
	if(sample)
	{
		GstBuffer* buffer = gst_sample_get_buffer(sample);
		int size = gst_buffer_get_size(buffer);

		GstMemory *mem = gst_buffer_get_all_memory(buffer);
		GstMapInfo info;
		gst_memory_map(mem, &info, GST_MAP_READ);

		if(self->mFrameBufferOffset + size < self->mFrame->size)
		{
			memcpy(self->mFrame->data + self->mFrameBufferOffset, info.data, size);
			self->mFrameBufferOffset += size;
		}
		else
		{
			int part1Size = self->mFrame->size - self->mFrameBufferOffset;
			memcpy(self->mFrame->data + self->mFrameBufferOffset, info.data, part1Size);
			self->mFrameBufferOffset = 0;
			
			if(self->mListener)
			{
				self->mListener->onFrame(self->mFrame);
			}

			int part2Size = size - part1Size;
			if(part2Size != 0)
			{
				memcpy(self->mFrame->data + self->mFrameBufferOffset, info.data + part1Size, part2Size);
				self->mFrameBufferOffset += part2Size;
			}
		}

		gst_memory_unmap(mem, &info);
		gst_memory_unref(mem);
		gst_buffer_unref(buffer);
		gst_sample_unref(sample);
	}

	return GST_FLOW_OK;
}
