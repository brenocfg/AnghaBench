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
typedef  int u_int ;
struct screen {int cstyle; } ;

/* Variables and functions */

void
screen_set_cursor_style(struct screen *s, u_int style)
{
	if (style <= 6)
		s->cstyle = style;
}