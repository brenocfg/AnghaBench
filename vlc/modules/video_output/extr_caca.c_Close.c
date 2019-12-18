#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_6__ {int /*<<< orphan*/  cv; int /*<<< orphan*/  dp; scalar_t__ dither; int /*<<< orphan*/ * fifo; int /*<<< orphan*/  thread; } ;
typedef  TYPE_2__ vout_display_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeConsole () ; 
 int /*<<< orphan*/  block_FifoRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  caca_free_display (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cucul_free_canvas (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cucul_free_dither (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;

    if (sys->fifo != NULL) {
        vlc_cancel(sys->thread);
        vlc_join(sys->thread, NULL);
        block_FifoRelease(sys->fifo);
    }
    if (sys->dither)
        cucul_free_dither(sys->dither);
    caca_free_display(sys->dp);
    cucul_free_canvas(sys->cv);

#if defined(_WIN32)
    FreeConsole();
#endif

    free(sys);
}