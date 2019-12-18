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
 int FR_OK ; 
 int f_mount (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_Filesystem ; 
 int isMounted ; 

int need_mount(void)
{
    int r;

    if (isMounted)
        return FR_OK;

    r = f_mount(&g_Filesystem, "0:", 0);
    if (r)
        return r;

    isMounted = 1;
    return FR_OK;
}