#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pts; size_t size; int /*<<< orphan*/  flags; int /*<<< orphan*/  dts; scalar_t__ data; } ;
struct stream {int has_pending; TYPE_1__ pending; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  LOGE (char*) ; 
 scalar_t__ av_grow_packet (TYPE_1__*,size_t) ; 
 scalar_t__ av_new_packet (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,size_t) ; 
 int process_config_packet (struct stream*,TYPE_1__*) ; 
 int stream_parse (struct stream*,TYPE_1__*) ; 

__attribute__((used)) static bool
stream_push_packet(struct stream *stream, AVPacket *packet) {
    bool is_config = packet->pts == AV_NOPTS_VALUE;

    // A config packet must not be decoded immetiately (it contains no
    // frame); instead, it must be concatenated with the future data packet.
    if (stream->has_pending || is_config) {
        size_t offset;
        if (stream->has_pending) {
            offset = stream->pending.size;
            if (av_grow_packet(&stream->pending, packet->size)) {
                LOGE("Could not grow packet");
                return false;
            }
        } else {
            offset = 0;
            if (av_new_packet(&stream->pending, packet->size)) {
                LOGE("Could not create packet");
                return false;
            }
            stream->has_pending = true;
        }

        memcpy(stream->pending.data + offset, packet->data, packet->size);

        if (!is_config) {
            // prepare the concat packet to send to the decoder
            stream->pending.pts = packet->pts;
            stream->pending.dts = packet->dts;
            stream->pending.flags = packet->flags;
            packet = &stream->pending;
        }
    }

    if (is_config) {
        // config packet
        bool ok = process_config_packet(stream, packet);
        if (!ok) {
            return false;
        }
    } else {
        // data packet
        bool ok = stream_parse(stream, packet);

        if (stream->has_pending) {
            // the pending packet must be discarded (consumed or error)
            stream->has_pending = false;
            av_packet_unref(&stream->pending);
        }

        if (!ok) {
            return false;
        }
    }
    return true;
}