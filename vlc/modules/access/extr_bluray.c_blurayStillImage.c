#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_8__ {scalar_t__ i_still_end_time; int /*<<< orphan*/  bluray; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ES_OUT_GET_EMPTY ; 
 scalar_t__ STILL_IMAGE_INFINITE ; 
 scalar_t__ STILL_IMAGE_NOT_SET ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  bd_read_skip_still (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blurayResetStillImage (TYPE_1__*) ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  streamFlush (TYPE_2__*) ; 
 scalar_t__ vlc_tick_from_sec (unsigned int) ; 
 scalar_t__ vlc_tick_now () ; 
 int /*<<< orphan*/  vlc_tick_sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blurayStillImage( demux_t *p_demux, unsigned i_timeout )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    /* time period elapsed ? */
    if (p_sys->i_still_end_time != STILL_IMAGE_NOT_SET &&
        p_sys->i_still_end_time != STILL_IMAGE_INFINITE &&
        p_sys->i_still_end_time <= vlc_tick_now()) {
        msg_Dbg(p_demux, "Still image end");
        bd_read_skip_still(p_sys->bluray);

        blurayResetStillImage(p_demux);
        return;
    }

    /* show last frame as still image */
    if (p_sys->i_still_end_time == STILL_IMAGE_NOT_SET) {
        if (i_timeout) {
            msg_Dbg(p_demux, "Still image (%d seconds)", i_timeout);
            p_sys->i_still_end_time = vlc_tick_now() + vlc_tick_from_sec( i_timeout );
        } else {
            msg_Dbg(p_demux, "Still image (infinite)");
            p_sys->i_still_end_time = STILL_IMAGE_INFINITE;
        }

        /* flush demuxer and decoder (there won't be next video packet starting with ts PUSI) */
        streamFlush(p_sys);

        /* stop buffering */
        bool b_empty;
        es_out_Control( p_demux->out, ES_OUT_GET_EMPTY, &b_empty );
    }

    /* avoid busy loops (read returns no data) */
    vlc_tick_sleep( VLC_TICK_FROM_MS(40) );
}