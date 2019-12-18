#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_11__ {TYPE_2__* output; int /*<<< orphan*/  output_in_transit; TYPE_1__* output_pool; } ;
typedef  TYPE_4__ decoder_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  buffer_num; } ;
struct TYPE_8__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  headers_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIN_NUM_BUFFERS_IN_TRANSIT ; 
 unsigned int NUM_DECODER_BUFFER_HEADERS ; 
 unsigned int __MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int atomic_load (int /*<<< orphan*/ *) ; 
 int mmal_queue_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,int,int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ send_output_buffer (TYPE_3__*) ; 

__attribute__((used)) static void fill_output_port(decoder_t *dec)
{
    decoder_sys_t *sys = dec->p_sys;

    unsigned max_buffers_in_transit = 0;
    int buffers_available = 0;
    int buffers_to_send = 0;
    int i;

    if (sys->output_pool) {
        max_buffers_in_transit = __MAX(sys->output_pool->headers_num,
                MIN_NUM_BUFFERS_IN_TRANSIT);
        buffers_available = mmal_queue_length(sys->output_pool->queue);
    } else {
        max_buffers_in_transit = NUM_DECODER_BUFFER_HEADERS;
        buffers_available = NUM_DECODER_BUFFER_HEADERS - atomic_load(&sys->output_in_transit);
    }
    buffers_to_send = max_buffers_in_transit - atomic_load(&sys->output_in_transit);

    if (buffers_to_send > buffers_available)
        buffers_to_send = buffers_available;

#ifndef NDEBUG
    msg_Dbg(dec, "Send %d buffers to output port (available: %d, "
                    "in_transit: %d, buffer_num: %d)",
                    buffers_to_send, buffers_available,
                    atomic_load(&sys->output_in_transit),
                    sys->output->buffer_num);
#endif
    for (i = 0; i < buffers_to_send; ++i)
        if (send_output_buffer(dec) < 0)
            break;
}