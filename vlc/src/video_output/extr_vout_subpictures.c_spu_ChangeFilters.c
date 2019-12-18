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
struct TYPE_4__ {TYPE_2__* p; } ;
typedef  TYPE_1__ spu_t ;
struct TYPE_5__ {char const* filter_chain_update; char const* filter_chain_current; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ spu_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char const*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void spu_ChangeFilters(spu_t *spu, const char *filters)
{
    spu_private_t *sys = spu->p;

    vlc_mutex_lock(&sys->lock);

    free(sys->filter_chain_update);
    if (filters)
    {
        sys->filter_chain_update = strdup(filters);
        free(sys->filter_chain_current);
        sys->filter_chain_current = strdup(filters);
    }
    else if (sys->filter_chain_current)
        sys->filter_chain_update = strdup(sys->filter_chain_current);

    vlc_mutex_unlock(&sys->lock);
}