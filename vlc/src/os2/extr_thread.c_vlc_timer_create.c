#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  struct vlc_timer* vlc_timer_t ;
struct vlc_timer {void (* func ) (void*) ;int quit; int /*<<< orphan*/  tid; scalar_t__ interval; int /*<<< orphan*/  htimer; int /*<<< orphan*/  hev; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_SEM_SHARED ; 
 int /*<<< orphan*/  DosCreateEventSem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NULLHANDLE ; 
 int /*<<< orphan*/  _beginthread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct vlc_timer*) ; 
 struct vlc_timer* malloc (int) ; 
 int /*<<< orphan*/  vlc_timer_do ; 

int vlc_timer_create (vlc_timer_t *id, void (*func) (void *), void *data)
{
    struct vlc_timer *timer = malloc (sizeof (*timer));

    if (timer == NULL)
        return ENOMEM;

    timer->func = func;
    timer->data = data;

    DosCreateEventSem (NULL, &timer->hev, DC_SEM_SHARED, FALSE);
    timer->htimer = NULLHANDLE;
    timer->interval = 0;
    timer->quit = false;
    timer->tid  = _beginthread (vlc_timer_do, NULL, 1024 * 1024, timer);

    *id = timer;
    return 0;
}