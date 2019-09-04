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
struct TYPE_9__ {int /*<<< orphan*/  hwndSelf; scalar_t__ region_posy; scalar_t__ region_posx; int /*<<< orphan*/  bCaptureState; scalar_t__ selection_end; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 scalar_t__ EDIT_CallWordBreakProc (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ EDIT_EM_LineFromChar (TYPE_1__*,scalar_t__) ; 
 scalar_t__ EDIT_EM_LineIndex (TYPE_1__*,scalar_t__) ; 
 scalar_t__ EDIT_EM_LineLength (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  EDIT_EM_ScrollCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_SetSel (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetCapture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WB_LEFT ; 
 int /*<<< orphan*/  WB_RIGHT ; 

__attribute__((used)) static LRESULT EDIT_WM_LButtonDblClk(EDITSTATE *es)
{
	INT s;
	INT e = es->selection_end;
	INT l;
	INT li;
	INT ll;

	es->bCaptureState = TRUE;
	SetCapture(es->hwndSelf);

	l = EDIT_EM_LineFromChar(es, e);
	li = EDIT_EM_LineIndex(es, l);
	ll = EDIT_EM_LineLength(es, e);
	s = li + EDIT_CallWordBreakProc(es, li, e - li, ll, WB_LEFT);
	e = li + EDIT_CallWordBreakProc(es, li, e - li, ll, WB_RIGHT);
	EDIT_EM_SetSel(es, s, e, FALSE);
	EDIT_EM_ScrollCaret(es);
	es->region_posx = es->region_posy = 0;
	SetTimer(es->hwndSelf, 0, 100, NULL);
	return 0;
}