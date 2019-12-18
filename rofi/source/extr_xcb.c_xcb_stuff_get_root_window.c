#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
struct TYPE_4__ {TYPE_1__* screen; } ;
struct TYPE_3__ {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 TYPE_2__* xcb ; 

xcb_window_t xcb_stuff_get_root_window ( void )
{
    return xcb->screen->root;
}