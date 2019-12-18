#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct window {int lastlayout; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* arrange ) (struct window*) ;} ;

/* Variables and functions */
 TYPE_1__* layout_sets ; 
 int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct window*) ; 

u_int
layout_set_previous(struct window *w)
{
	u_int	layout;

	if (w->lastlayout == -1)
		layout = nitems(layout_sets) - 1;
	else {
		layout = w->lastlayout;
		if (layout == 0)
			layout = nitems(layout_sets) - 1;
		else
			layout--;
	}

	if (layout_sets[layout].arrange != NULL)
		layout_sets[layout].arrange(w);
	w->lastlayout = layout;
	return (layout);
}