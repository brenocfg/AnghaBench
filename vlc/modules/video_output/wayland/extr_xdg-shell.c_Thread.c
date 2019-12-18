#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct wl_display* wl; } ;
struct TYPE_5__ {TYPE_1__ display; TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_window_t ;
struct TYPE_6__ {int /*<<< orphan*/  seats; } ;
typedef  TYPE_3__ vout_window_sys_t ;
struct wl_display {int dummy; } ;
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  cleanup_wl_display_read ; 
 int poll (struct pollfd*,int,int) ; 
 int seat_next_timeout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seat_timeout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cleanup_push (int /*<<< orphan*/ ,struct wl_display*) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  wl_display_dispatch_pending (struct wl_display*) ; 
 int /*<<< orphan*/  wl_display_flush (struct wl_display*) ; 
 int /*<<< orphan*/  wl_display_get_fd (struct wl_display*) ; 
 scalar_t__ wl_display_prepare_read (struct wl_display*) ; 
 int /*<<< orphan*/  wl_display_read_events (struct wl_display*) ; 

__attribute__((used)) static void *Thread(void *data)
{
    vout_window_t *wnd = data;
    vout_window_sys_t *sys = wnd->sys;
    struct wl_display *display = wnd->display.wl;
    struct pollfd ufd[1];

    int canc = vlc_savecancel();
    vlc_cleanup_push(cleanup_wl_display_read, display);

    ufd[0].fd = wl_display_get_fd(display);
    ufd[0].events = POLLIN;

    for (;;)
    {
        int timeout;

        while (wl_display_prepare_read(display) != 0)
            wl_display_dispatch_pending(display);

        wl_display_flush(display);
        timeout = seat_next_timeout(&sys->seats);
        vlc_restorecancel(canc);

        int val = poll(ufd, 1, timeout);

        canc = vlc_savecancel();
        if (val == 0)
            seat_timeout(&sys->seats);

        wl_display_read_events(display);
        wl_display_dispatch_pending(display);
    }
    vlc_assert_unreachable();
    vlc_cleanup_pop();
    //vlc_restorecancel(canc);
    //return NULL;
}