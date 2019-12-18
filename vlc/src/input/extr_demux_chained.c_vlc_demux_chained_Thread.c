#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_3__ {double position; scalar_t__ time; scalar_t__ length; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__ stats; int /*<<< orphan*/  reader; int /*<<< orphan*/  out; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ vlc_demux_chained_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEMUX_GET_LENGTH ; 
 int /*<<< orphan*/  DEMUX_GET_POSITION ; 
 int /*<<< orphan*/  DEMUX_GET_TIME ; 
 int /*<<< orphan*/  DEMUX_SET_GROUP_ALL ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ ) ; 
 scalar_t__ VLC_TICK_FROM_MS (int) ; 
 scalar_t__ demux_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  demux_Delete (int /*<<< orphan*/ *) ; 
 scalar_t__ demux_Demux (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * demux_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ demux_TestAndClearFlags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static void *vlc_demux_chained_Thread(void *data)
{
    vlc_demux_chained_t *dc = data;
    demux_t *demux = demux_New(VLC_OBJECT(dc->reader), dc->name, dc->reader,
                               dc->out);
    if (demux == NULL)
    {
        vlc_stream_Delete(dc->reader);
        return NULL;
    }

    /* Stream FIFO cannot apply DVB filters.
     * Get all programs and let the E/S output sort them out. */
    demux_Control(demux, DEMUX_SET_GROUP_ALL);

    /* Main loop */
    vlc_tick_t next_update = 0;

    do
        if (demux_TestAndClearFlags(demux, UINT_MAX) || vlc_tick_now() >= next_update)
        {
            double newpos;
            vlc_tick_t newlen;
            vlc_tick_t newtime;

            if (demux_Control(demux, DEMUX_GET_POSITION, &newpos))
                newpos = 0.;
            if (demux_Control(demux, DEMUX_GET_LENGTH, &newlen))
                newlen = 0;
            if (demux_Control(demux, DEMUX_GET_TIME, &newtime))
                newtime = 0;

            vlc_mutex_lock(&dc->lock);
            dc->stats.position = newpos;
            dc->stats.length = newlen;
            dc->stats.time = newtime;
            vlc_mutex_unlock(&dc->lock);

            next_update = vlc_tick_now() + VLC_TICK_FROM_MS(250);
        }
    while (demux_Demux(demux) > 0);

    demux_Delete(demux);
    return NULL;
}