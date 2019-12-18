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

/* Variables and functions */
 int vlc_killed () ; 

__attribute__((used)) static int UrlInterruptCallback(void *access)
{
    /* NOTE: This works so long as libavformat invokes the callback from the
     * same thread that invokes libavformat. Currently libavformat does not
     * create internal threads at all. This is not proper event handling in any
     * case; libavformat needs fixing. */
    (void) access;
    return vlc_killed();
}