#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; int /*<<< orphan*/  hwndSelf; scalar_t__ region_posy; scalar_t__ region_posx; int /*<<< orphan*/  selection_start; int /*<<< orphan*/  bCaptureState; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_CharFromPos (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_ConfinePoint (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_EM_ScrollCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_SetSel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EF_FOCUSED ; 
 int MK_SHIFT ; 
 int /*<<< orphan*/  SetCapture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT EDIT_WM_LButtonDown(EDITSTATE *es, DWORD keys, INT x, INT y)
{
	INT e;
	BOOL after_wrap;

	es->bCaptureState = TRUE;
	SetCapture(es->hwndSelf);
	EDIT_ConfinePoint(es, &x, &y);
	e = EDIT_CharFromPos(es, x, y, &after_wrap);
	EDIT_EM_SetSel(es, (keys & MK_SHIFT) ? es->selection_start : e, e, after_wrap);
	EDIT_EM_ScrollCaret(es);
	es->region_posx = es->region_posy = 0;
	SetTimer(es->hwndSelf, 0, 100, NULL);

	if (!(es->flags & EF_FOCUSED))
            SetFocus(es->hwndSelf);

	return 0;
}