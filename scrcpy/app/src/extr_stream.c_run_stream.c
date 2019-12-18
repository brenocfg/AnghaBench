#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stream {int /*<<< orphan*/  codec_ctx; scalar_t__ decoder; scalar_t__ recorder; TYPE_1__* parser; int /*<<< orphan*/  pending; scalar_t__ has_pending; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  LOGC (char*) ; 
 int /*<<< orphan*/  LOGD (char*) ; 
 int /*<<< orphan*/  LOGE (char*) ; 
 int /*<<< orphan*/  LOGI (char*) ; 
 int /*<<< orphan*/  PARSER_FLAG_COMPLETE_FRAMES ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_parser_close (TYPE_1__*) ; 
 TYPE_1__* av_parser_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decoder_close (scalar_t__) ; 
 int /*<<< orphan*/  decoder_open (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_stopped () ; 
 int /*<<< orphan*/  recorder_close (scalar_t__) ; 
 int /*<<< orphan*/  recorder_join (scalar_t__) ; 
 int /*<<< orphan*/  recorder_open (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recorder_start (scalar_t__) ; 
 int /*<<< orphan*/  recorder_stop (scalar_t__) ; 
 int stream_push_packet (struct stream*,int /*<<< orphan*/ *) ; 
 int stream_recv_packet (struct stream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
run_stream(void *data) {
    struct stream *stream = data;

    AVCodec *codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!codec) {
        LOGE("H.264 decoder not found");
        goto end;
    }

    stream->codec_ctx = avcodec_alloc_context3(codec);
    if (!stream->codec_ctx) {
        LOGC("Could not allocate codec context");
        goto end;
    }

    if (stream->decoder && !decoder_open(stream->decoder, codec)) {
        LOGE("Could not open decoder");
        goto finally_free_codec_ctx;
    }

    if (stream->recorder) {
        if (!recorder_open(stream->recorder, codec)) {
            LOGE("Could not open recorder");
            goto finally_close_decoder;
        }

        if (!recorder_start(stream->recorder)) {
            LOGE("Could not start recorder");
            goto finally_close_recorder;
        }
    }

    stream->parser = av_parser_init(AV_CODEC_ID_H264);
    if (!stream->parser) {
        LOGE("Could not initialize parser");
        goto finally_stop_and_join_recorder;
    }

    // We must only pass complete frames to av_parser_parse2()!
    // It's more complicated, but this allows to reduce the latency by 1 frame!
    stream->parser->flags |= PARSER_FLAG_COMPLETE_FRAMES;

    for (;;) {
        AVPacket packet;
        bool ok = stream_recv_packet(stream, &packet);
        if (!ok) {
            // end of stream
            break;
        }

        ok = stream_push_packet(stream, &packet);
        av_packet_unref(&packet);
        if (!ok) {
            // cannot process packet (error already logged)
            break;
        }
    }

    LOGD("End of frames");

    if (stream->has_pending) {
        av_packet_unref(&stream->pending);
    }

    av_parser_close(stream->parser);
finally_stop_and_join_recorder:
    if (stream->recorder) {
        recorder_stop(stream->recorder);
        LOGI("Finishing recording...");
        recorder_join(stream->recorder);
    }
finally_close_recorder:
    if (stream->recorder) {
        recorder_close(stream->recorder);
    }
finally_close_decoder:
    if (stream->decoder) {
        decoder_close(stream->decoder);
    }
finally_free_codec_ctx:
    avcodec_free_context(&stream->codec_ctx);
end:
    notify_stopped();
    return 0;
}