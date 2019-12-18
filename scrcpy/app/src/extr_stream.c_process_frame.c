#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stream {scalar_t__ recorder; scalar_t__ decoder; } ;
struct TYPE_5__ {int /*<<< orphan*/  pts; int /*<<< orphan*/  dts; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  LOGE (char*) ; 
 int /*<<< orphan*/  decoder_push (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  recorder_push (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static bool
process_frame(struct stream *stream, AVPacket *packet) {
    if (stream->decoder && !decoder_push(stream->decoder, packet)) {
        return false;
    }

    if (stream->recorder) {
        packet->dts = packet->pts;

        if (!recorder_push(stream->recorder, packet)) {
            LOGE("Could not send packet to recorder");
            return false;
        }
    }

    return true;
}