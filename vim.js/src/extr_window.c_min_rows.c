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
struct TYPE_3__ {int /*<<< orphan*/  tp_topframe; struct TYPE_3__* tp_next; } ;
typedef  TYPE_1__ tabpage_T ;

/* Variables and functions */
 int MIN_LINES ; 
 TYPE_1__* first_tabpage ; 
 int /*<<< orphan*/ * firstwin ; 
 int frame_minheight (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tabline_height () ; 

int
min_rows()
{
    int		total;
#ifdef FEAT_WINDOWS
    tabpage_T	*tp;
    int		n;
#endif

    if (firstwin == NULL)	/* not initialized yet */
	return MIN_LINES;

#ifdef FEAT_WINDOWS
    total = 0;
    for (tp = first_tabpage; tp != NULL; tp = tp->tp_next)
    {
	n = frame_minheight(tp->tp_topframe, NULL);
	if (total < n)
	    total = n;
    }
    total += tabline_height();
#else
    total = 1;		/* at least one window should have a line! */
#endif
    total += 1;		/* count the room for the command line */
    return total;
}