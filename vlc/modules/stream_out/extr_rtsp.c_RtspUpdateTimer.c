#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_5__ {scalar_t__ timeout; int sessionc; int /*<<< orphan*/  timer; TYPE_1__** sessionv; } ;
typedef  TYPE_2__ rtsp_stream_t ;
struct TYPE_4__ {scalar_t__ last_seen; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TIMER_FIRE_ONCE ; 
 int /*<<< orphan*/  vlc_timer_disarm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_timer_schedule (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void RtspUpdateTimer( rtsp_stream_t *rtsp )
{
    if (rtsp->timeout == 0)
        return;

    vlc_tick_t timeout = 0;
    for (int i = 0; i < rtsp->sessionc; i++)
    {
        if (timeout == 0 || rtsp->sessionv[i]->last_seen < timeout)
            timeout = rtsp->sessionv[i]->last_seen;
    }
    if (timeout != 0)
    {
        timeout += rtsp->timeout;
        vlc_timer_schedule(rtsp->timer, true, timeout, VLC_TIMER_FIRE_ONCE);
    }
    else
    {
        vlc_timer_disarm(rtsp->timer);
    }
}