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
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ selection_start; scalar_t__ selection_end; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ EDITSTATE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_InvalidateText (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  EF_AFTER_WRAP ; 
 int /*<<< orphan*/  ORDER_UINT (scalar_t__,scalar_t__) ; 
 scalar_t__ get_text_length (TYPE_1__*) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void EDIT_EM_SetSel(EDITSTATE *es, UINT start, UINT end, BOOL after_wrap)
{
	UINT old_start = es->selection_start;
	UINT old_end = es->selection_end;
	UINT len = get_text_length(es);

	if (start == (UINT)-1) {
		start = es->selection_end;
		end = es->selection_end;
	} else {
		start = min(start, len);
		end = min(end, len);
	}
	es->selection_start = start;
	es->selection_end = end;
	if (after_wrap)
		es->flags |= EF_AFTER_WRAP;
	else
		es->flags &= ~EF_AFTER_WRAP;
	/* Compute the necessary invalidation region. */
	/* Note that we don't need to invalidate regions which have
	 * "never" been selected, or those which are "still" selected.
	 * In fact, every time we hit a selection boundary, we can
	 * *toggle* whether we need to invalidate.  Thus we can optimize by
	 * *sorting* the interval endpoints.  Let's assume that we sort them
	 * in this order:
	 *        start <= end <= old_start <= old_end
	 * Knuth 5.3.1 (p 183) assures us that this can be done optimally
	 * in 5 comparisons; i.e. it is impossible to do better than the
	 * following: */
        ORDER_UINT(end, old_end);
        ORDER_UINT(start, old_start);
        ORDER_UINT(old_start, old_end);
        ORDER_UINT(start, end);
	/* Note that at this point 'end' and 'old_start' are not in order, but
	 * start is definitely the min. and old_end is definitely the max. */
	if (end != old_start)
        {
/*
 * One can also do
 *          ORDER_UINT32(end, old_start);
 *          EDIT_InvalidateText(es, start, end);
 *          EDIT_InvalidateText(es, old_start, old_end);
 * in place of the following if statement.
 * (That would complete the optimal five-comparison four-element sort.)
 */
            if (old_start > end )
            {
                EDIT_InvalidateText(es, start, end);
                EDIT_InvalidateText(es, old_start, old_end);
            }
            else
            {
                EDIT_InvalidateText(es, start, old_start);
                EDIT_InvalidateText(es, end, old_end);
            }
	}
        else EDIT_InvalidateText(es, start, old_end);
}