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
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ col; int /*<<< orphan*/  lnum; } ;
typedef  TYPE_1__ pos_T ;
typedef  scalar_t__ colnr_T ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_8__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 scalar_t__ STRLEN (int /*<<< orphan*/ *) ; 
 TYPE_1__ VIsual ; 
 int /*<<< orphan*/  VIsual_active ; 
 TYPE_4__* curwin ; 
 int /*<<< orphan*/  hasAnyFolding (TYPE_4__*) ; 
 scalar_t__ hasFolding (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ has_mbyte ; 
 scalar_t__ ltoreq (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  mb_adjust_cursor () ; 
 int /*<<< orphan*/ * ml_get (int /*<<< orphan*/ ) ; 
 char* p_sel ; 

void
foldAdjustVisual()
{
    pos_T	*start, *end;
    char_u	*ptr;

    if (!VIsual_active || !hasAnyFolding(curwin))
	return;

    if (ltoreq(VIsual, curwin->w_cursor))
    {
	start = &VIsual;
	end = &curwin->w_cursor;
    }
    else
    {
	start = &curwin->w_cursor;
	end = &VIsual;
    }
    if (hasFolding(start->lnum, &start->lnum, NULL))
	start->col = 0;
    if (hasFolding(end->lnum, NULL, &end->lnum))
    {
	ptr = ml_get(end->lnum);
	end->col = (colnr_T)STRLEN(ptr);
	if (end->col > 0 && *p_sel == 'o')
	    --end->col;
#ifdef FEAT_MBYTE
	/* prevent cursor from moving on the trail byte */
	if (has_mbyte)
	    mb_adjust_cursor();
#endif
    }
}