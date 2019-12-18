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
struct TYPE_4__ {unsigned int priority; void* cbs_data; struct vlc_clock_cbs const* cbs; scalar_t__ delay; int /*<<< orphan*/ * owner; } ;
typedef  TYPE_1__ vlc_clock_t ;
typedef  int /*<<< orphan*/  vlc_clock_main_t ;
struct vlc_clock_cbs {scalar_t__ on_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static vlc_clock_t *vlc_clock_main_Create(vlc_clock_main_t *main_clock,
                                          unsigned priority,
                                          const struct vlc_clock_cbs *cbs,
                                          void *cbs_data)
{
    vlc_clock_t *clock = malloc(sizeof(vlc_clock_t));
    if (clock == NULL)
        return NULL;

    clock->owner = main_clock;
    clock->delay = 0;
    clock->cbs = cbs;
    clock->cbs_data = cbs_data;
    clock->priority = priority;
    assert(!cbs || cbs->on_update);

    return clock;
}