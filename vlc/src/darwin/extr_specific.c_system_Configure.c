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
typedef  int /*<<< orphan*/  libvlc_int_t ;

/* Variables and functions */

void system_Configure( libvlc_int_t *p_this,
                       int i_argc, const char *const ppsz_argv[] )
{
    (void)p_this;
    (void)i_argc;
    (void)ppsz_argv;
}