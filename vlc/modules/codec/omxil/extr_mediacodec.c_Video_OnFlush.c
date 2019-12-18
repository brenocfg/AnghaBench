#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_8__ {scalar_t__ b_direct_rendering; } ;
struct TYPE_7__ {int /*<<< orphan*/  timestamp_fifo; } ;
struct TYPE_10__ {TYPE_2__ api; TYPE_1__ video; } ;
typedef  TYPE_4__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidateAllPictures (TYPE_3__*) ; 
 int /*<<< orphan*/  timestamp_FifoEmpty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Video_OnFlush(decoder_t *p_dec)
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    timestamp_FifoEmpty(p_sys->video.timestamp_fifo);
    /* Invalidate all pictures that are currently in flight
     * since flushing make all previous indices returned by
     * MediaCodec invalid. */
    if (p_sys->api.b_direct_rendering)
        InvalidateAllPictures(p_dec);
}