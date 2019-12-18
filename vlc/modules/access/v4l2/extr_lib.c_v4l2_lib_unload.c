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
 int /*<<< orphan*/  dlclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * v4l2_handle ; 

__attribute__((used)) __attribute__((destructor))
static void v4l2_lib_unload (void)
{
    if (v4l2_handle != NULL)
        dlclose (v4l2_handle);
}