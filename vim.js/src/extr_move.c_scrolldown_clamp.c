#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ w_topfill; int w_topline; int w_wrow; scalar_t__ w_width; int w_cline_height; int w_virtcol; int w_height; int w_valid; int /*<<< orphan*/  w_botline; scalar_t__ w_p_wrap; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int VALID_BOTLINE ; 
 int VALID_CROW ; 
 int VALID_WROW ; 
 int W_WIDTH (TYPE_1__*) ; 
 int /*<<< orphan*/  check_topfill (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* curwin ; 
 scalar_t__ diff_check_fill (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hasFolding (int,int*,int /*<<< orphan*/ *) ; 
 int p_so ; 
 scalar_t__ plines (int) ; 
 scalar_t__ plines_nofill (int) ; 
 int /*<<< orphan*/  validate_cheight () ; 
 int /*<<< orphan*/  validate_cursor () ; 
 int /*<<< orphan*/  validate_virtcol () ; 

void
scrolldown_clamp()
{
    int		end_row;
#ifdef FEAT_DIFF
    int		can_fill = (curwin->w_topfill
				< diff_check_fill(curwin, curwin->w_topline));
#endif

    if (curwin->w_topline <= 1
#ifdef FEAT_DIFF
	    && !can_fill
#endif
	    )
	return;

    validate_cursor();	    /* w_wrow needs to be valid */

    /*
     * Compute the row number of the last row of the cursor line
     * and make sure it doesn't go off the screen. Make sure the cursor
     * doesn't go past 'scrolloff' lines from the screen end.
     */
    end_row = curwin->w_wrow;
#ifdef FEAT_DIFF
    if (can_fill)
	++end_row;
    else
	end_row += plines_nofill(curwin->w_topline - 1);
#else
    end_row += plines(curwin->w_topline - 1);
#endif
    if (curwin->w_p_wrap
#ifdef FEAT_VERTSPLIT
		&& curwin->w_width != 0
#endif
	    )
    {
	validate_cheight();
	validate_virtcol();
	end_row += curwin->w_cline_height - 1 -
	    curwin->w_virtcol / W_WIDTH(curwin);
    }
    if (end_row < curwin->w_height - p_so)
    {
#ifdef FEAT_DIFF
	if (can_fill)
	{
	    ++curwin->w_topfill;
	    check_topfill(curwin, TRUE);
	}
	else
	{
	    --curwin->w_topline;
	    curwin->w_topfill = 0;
	}
#else
	--curwin->w_topline;
#endif
#ifdef FEAT_FOLDING
	hasFolding(curwin->w_topline, &curwin->w_topline, NULL);
#endif
	--curwin->w_botline;	    /* approximate w_botline */
	curwin->w_valid &= ~(VALID_WROW|VALID_CROW|VALID_BOTLINE);
    }
}