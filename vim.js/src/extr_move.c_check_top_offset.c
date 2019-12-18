#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ lnum; scalar_t__ fill; scalar_t__ height; } ;
typedef  TYPE_2__ lineoff_T ;
struct TYPE_6__ {scalar_t__ lnum; } ;
struct TYPE_8__ {scalar_t__ w_topline; int w_topfill; TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 TYPE_4__* curwin ; 
 scalar_t__ hasAnyFolding (TYPE_4__*) ; 
 int p_so ; 
 int /*<<< orphan*/  topline_back (TYPE_2__*) ; 

__attribute__((used)) static int
check_top_offset()
{
    lineoff_T	loff;
    int		n;

    if (curwin->w_cursor.lnum < curwin->w_topline + p_so
#ifdef FEAT_FOLDING
		    || hasAnyFolding(curwin)
#endif
	    )
    {
	loff.lnum = curwin->w_cursor.lnum;
#ifdef FEAT_DIFF
	loff.fill = 0;
	n = curwin->w_topfill;	    /* always have this context */
#else
	n = 0;
#endif
	/* Count the visible screen lines above the cursor line. */
	while (n < p_so)
	{
	    topline_back(&loff);
	    /* Stop when included a line above the window. */
	    if (loff.lnum < curwin->w_topline
#ifdef FEAT_DIFF
		    || (loff.lnum == curwin->w_topline && loff.fill > 0)
#endif
		    )
		break;
	    n += loff.height;
	}
	if (n < p_so)
	    return TRUE;
    }
    return FALSE;
}