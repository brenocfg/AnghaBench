#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* i_last_pts; void* i_last_dts; void* i_first_dts; } ;
typedef  TYPE_1__ mp4_stream_t ;

/* Variables and functions */
 void* VLC_TICK_INVALID ; 
 TYPE_1__* calloc (int,int) ; 

__attribute__((used)) static mp4_stream_t *mp4_stream_New(void)
{
    mp4_stream_t *p_stream = calloc(1, sizeof(*p_stream));
    if(p_stream)
    {
        p_stream->i_first_dts = VLC_TICK_INVALID;
        p_stream->i_last_dts = VLC_TICK_INVALID;
        p_stream->i_last_pts = VLC_TICK_INVALID;
    }
    return p_stream;
}