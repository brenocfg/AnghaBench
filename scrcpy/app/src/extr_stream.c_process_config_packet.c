#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stream {scalar_t__ recorder; } ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  LOGE (char*) ; 
 int /*<<< orphan*/  recorder_push (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
process_config_packet(struct stream *stream, AVPacket *packet) {
    if (stream->recorder && !recorder_push(stream->recorder, packet)) {
        LOGE("Could not send config packet to recorder");
        return false;
    }
    return true;
}