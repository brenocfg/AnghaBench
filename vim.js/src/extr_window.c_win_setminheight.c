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
struct TYPE_3__ {scalar_t__ w_height; struct TYPE_3__* w_next; } ;
typedef  TYPE_1__ win_T ;

/* Variables and functions */
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_noroom ; 
 TYPE_1__* firstwin ; 
 int p_wh ; 
 scalar_t__ p_wmh ; 

void
win_setminheight()
{
    int		room;
    int		first = TRUE;
    win_T	*wp;

    /* loop until there is a 'winminheight' that is possible */
    while (p_wmh > 0)
    {
	/* TODO: handle vertical splits */
	room = -p_wh;
	for (wp = firstwin; wp != NULL; wp = wp->w_next)
	    room += wp->w_height - p_wmh;
	if (room >= 0)
	    break;
	--p_wmh;
	if (first)
	{
	    EMSG(_(e_noroom));
	    first = FALSE;
	}
    }
}