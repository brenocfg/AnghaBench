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
typedef  scalar_t__ HWND ;

/* Variables and functions */

__attribute__((used)) static int window_to_index(HWND hwnd, HWND *window, int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        if (!window[i]) break;
        if (window[i] == hwnd) return i;
    }
    return -1;
}