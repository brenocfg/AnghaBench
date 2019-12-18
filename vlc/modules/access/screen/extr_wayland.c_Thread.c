#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct wl_display {int dummy; } ;
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct TYPE_8__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_9__ {float rate; int /*<<< orphan*/ * es; struct wl_display* display; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 float CLOCK_FREQ ; 
 scalar_t__ DisplayError (TYPE_1__*,struct wl_display*) ; 
 int /*<<< orphan*/  POLLIN ; 
 TYPE_3__* Shoot (TYPE_1__*) ; 
 int /*<<< orphan*/  cleanup_wl_display_read ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int lroundf (float) ; 
 scalar_t__ poll (struct pollfd*,int,unsigned int) ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cleanup_push (int /*<<< orphan*/ ,struct wl_display*) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_tick_now () ; 
 int /*<<< orphan*/  wl_display_dispatch_pending (struct wl_display*) ; 
 int /*<<< orphan*/  wl_display_flush (struct wl_display*) ; 
 int /*<<< orphan*/  wl_display_get_fd (struct wl_display*) ; 
 scalar_t__ wl_display_prepare_read (struct wl_display*) ; 
 int /*<<< orphan*/  wl_display_read_events (struct wl_display*) ; 

__attribute__((used)) static void *Thread(void *data)
{
    demux_t *demux = data;
    demux_sys_t *sys = demux->p_sys;
    struct wl_display *display = sys->display;
    struct pollfd ufd[1];
    unsigned interval = lroundf(CLOCK_FREQ / (sys->rate * 1000.f));

    int canc = vlc_savecancel();
    vlc_cleanup_push(cleanup_wl_display_read, display);

    ufd[0].fd = wl_display_get_fd(display);
    ufd[0].events = POLLIN;

    for (;;)
    {
        if (DisplayError(demux, display))
            break;

        if (sys->es != NULL)
        {
            block_t *block = Shoot(demux);

            block->i_pts = block->i_dts = vlc_tick_now();
            es_out_SetPCR(demux->out, block->i_pts);
            es_out_Send(demux->out, sys->es, block);
        }

        while (wl_display_prepare_read(display) != 0)
            wl_display_dispatch_pending(display);
        wl_display_flush(display);
        vlc_restorecancel(canc);

        while (poll(ufd, 1, interval) < 0);

        canc = vlc_savecancel();
        wl_display_read_events(display);
        wl_display_dispatch_pending(display);
    }
    vlc_cleanup_pop();
    vlc_restorecancel(canc);
    return NULL;
}