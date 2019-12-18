#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ coladd; scalar_t__ col; int lnum; } ;
typedef  TYPE_1__ pos_T ;
typedef  scalar_t__ colnr_T ;
struct TYPE_10__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ STRLEN (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 TYPE_1__ VIsual ; 
 int /*<<< orphan*/  curbuf ; 
 TYPE_7__* curwin ; 
 int /*<<< orphan*/  equalpos (TYPE_1__,TYPE_1__) ; 
 scalar_t__ lt (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  mb_adjustpos (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ml_get (int) ; 
 char* p_sel ; 

__attribute__((used)) static int
unadjust_for_sel()
{
    pos_T	*pp;

    if (*p_sel == 'e' && !equalpos(VIsual, curwin->w_cursor))
    {
	if (lt(VIsual, curwin->w_cursor))
	    pp = &curwin->w_cursor;
	else
	    pp = &VIsual;
#ifdef FEAT_VIRTUALEDIT
	if (pp->coladd > 0)
	    --pp->coladd;
	else
#endif
	if (pp->col > 0)
	{
	    --pp->col;
#ifdef FEAT_MBYTE
	    mb_adjustpos(curbuf, pp);
#endif
	}
	else if (pp->lnum > 1)
	{
	    --pp->lnum;
	    pp->col = (colnr_T)STRLEN(ml_get(pp->lnum));
	    return TRUE;
	}
    }
    return FALSE;
}