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
typedef  int /*<<< orphan*/  vlc_vdp_video_field_t ;
typedef  int /*<<< orphan*/  vlc_va_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GetSurface (int /*<<< orphan*/ *) ; 
 unsigned int VLC_TICK_FROM_SEC (int) ; 
 unsigned int VOUT_OUTMEM_SLEEP ; 
 int /*<<< orphan*/  vlc_tick_sleep (unsigned int) ; 

__attribute__((used)) static vlc_vdp_video_field_t *Get(vlc_va_sys_t *sys)
{
    vlc_vdp_video_field_t *field;
    unsigned tries = (VLC_TICK_FROM_SEC(1) + VOUT_OUTMEM_SLEEP) / VOUT_OUTMEM_SLEEP;

    while ((field = GetSurface(sys)) == NULL)
    {
        if (--tries == 0)
            return NULL;
        /* Pool empty. Wait for some time as in src/input/decoder.c.
         * XXX: Both this and the core should use a semaphore or a CV. */
        vlc_tick_sleep(VOUT_OUTMEM_SLEEP);
    }

    return field;
}