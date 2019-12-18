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
typedef  scalar_t__ xcb_window_t ;

/* Variables and functions */

__attribute__((used)) static int cmpapp (const void *a, const void *b)
{
    xcb_window_t wa = *(xcb_window_t *)a;
    xcb_window_t wb = *(xcb_window_t *)b;

    if (wa > wb)
        return 1;
    if (wa < wb)
        return -1;
    return 0;
}