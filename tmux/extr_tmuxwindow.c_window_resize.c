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
typedef  void* u_int ;
struct window {void* sy; void* sx; } ;

/* Variables and functions */

void
window_resize(struct window *w, u_int sx, u_int sy)
{
	w->sx = sx;
	w->sy = sy;
}