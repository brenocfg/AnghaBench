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
typedef  int /*<<< orphan*/  vlc_va_surface_t ;
struct TYPE_4__ {scalar_t__ surface_count; } ;
typedef  TYPE_1__ va_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GetSurface (TYPE_1__*) ; 
 unsigned int MAX_GET_RETRIES ; 
 int /*<<< orphan*/  VOUT_OUTMEM_SLEEP ; 
 int /*<<< orphan*/  vlc_tick_sleep (int /*<<< orphan*/ ) ; 

vlc_va_surface_t *va_pool_Get(va_pool_t *va_pool)
{
    unsigned tries = MAX_GET_RETRIES;
    vlc_va_surface_t *surface;

    if (va_pool->surface_count == 0)
        return NULL;

    while ((surface = GetSurface(va_pool)) == NULL)
    {
        if (--tries == 0)
            return NULL;
        /* Pool empty. Wait for some time as in src/input/decoder.c.
         * XXX: Both this and the core should use a semaphore or a CV. */
        vlc_tick_sleep(VOUT_OUTMEM_SLEEP);
    }
    return surface;
}