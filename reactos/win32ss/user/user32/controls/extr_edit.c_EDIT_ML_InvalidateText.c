#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ y_offset; int /*<<< orphan*/  format_rect; int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 scalar_t__ EDIT_EM_LineFromChar (TYPE_1__*,scalar_t__) ; 
 scalar_t__ EDIT_EM_LineIndex (TYPE_1__*,scalar_t__) ; 
 scalar_t__ EDIT_EM_LineLength (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  EDIT_GetLineRect (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_UpdateText (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IntersectRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ get_vertical_line_count (TYPE_1__*) ; 

__attribute__((used)) static void EDIT_ML_InvalidateText(EDITSTATE *es, INT start, INT end)
{
	INT vlc = get_vertical_line_count(es);
	INT sl = EDIT_EM_LineFromChar(es, start);
	INT el = EDIT_EM_LineFromChar(es, end);
	INT sc;
	INT ec;
	RECT rc1;
	RECT rcWnd;
	RECT rcLine;
	RECT rcUpdate;
	INT l;

	if ((el < es->y_offset) || (sl > es->y_offset + vlc))
		return;

	sc = start - EDIT_EM_LineIndex(es, sl);
	ec = end - EDIT_EM_LineIndex(es, el);
	if (sl < es->y_offset) {
		sl = es->y_offset;
		sc = 0;
	}
	if (el > es->y_offset + vlc) {
		el = es->y_offset + vlc;
		ec = EDIT_EM_LineLength(es, EDIT_EM_LineIndex(es, el));
	}
	GetClientRect(es->hwndSelf, &rc1);
	IntersectRect(&rcWnd, &rc1, &es->format_rect);
	if (sl == el) {
		EDIT_GetLineRect(es, sl, sc, ec, &rcLine);
		if (IntersectRect(&rcUpdate, &rcWnd, &rcLine))
			EDIT_UpdateText(es, &rcUpdate, TRUE);
	} else {
		EDIT_GetLineRect(es, sl, sc,
				EDIT_EM_LineLength(es,
					EDIT_EM_LineIndex(es, sl)),
				&rcLine);
		if (IntersectRect(&rcUpdate, &rcWnd, &rcLine))
			EDIT_UpdateText(es, &rcUpdate, TRUE);
		for (l = sl + 1 ; l < el ; l++) {
			EDIT_GetLineRect(es, l, 0,
				EDIT_EM_LineLength(es,
					EDIT_EM_LineIndex(es, l)),
				&rcLine);
			if (IntersectRect(&rcUpdate, &rcWnd, &rcLine))
				EDIT_UpdateText(es, &rcUpdate, TRUE);
		}
		EDIT_GetLineRect(es, el, 0, ec, &rcLine);
		if (IntersectRect(&rcUpdate, &rcWnd, &rcLine))
			EDIT_UpdateText(es, &rcUpdate, TRUE);
	}
}