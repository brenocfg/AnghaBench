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
struct TYPE_6__ {int frontend; int demux; int dir; int /*<<< orphan*/ * cam; TYPE_1__* pids; int /*<<< orphan*/  budget; } ;
typedef  TYPE_2__ dvb_device_t ;
struct TYPE_5__ {int fd; } ;

/* Variables and functions */
 size_t MAX_PIDS ; 
 int /*<<< orphan*/  en50221_End (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_close (int) ; 

void dvb_close (dvb_device_t *d)
{
#ifndef USE_DMX
    if (!d->budget)
    {
        for (size_t i = 0; i < MAX_PIDS; i++)
            if (d->pids[i].fd != -1)
                vlc_close (d->pids[i].fd);
    }
#endif
    if (d->cam != NULL)
        en50221_End (d->cam);
    if (d->frontend != -1)
        vlc_close (d->frontend);
    vlc_close (d->demux);
    vlc_close (d->dir);
    free (d);
}