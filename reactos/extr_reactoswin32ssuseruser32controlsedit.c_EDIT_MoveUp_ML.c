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
struct TYPE_7__ {short selection_start; short selection_end; int flags; short line_height; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  short INT ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int BOOL ;

/* Variables and functions */
 short EDIT_CharFromPos (TYPE_1__*,short,short,int*) ; 
 int /*<<< orphan*/  EDIT_EM_PosFromChar (TYPE_1__*,short,int) ; 
 int /*<<< orphan*/  EDIT_EM_ScrollCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_SetSel (TYPE_1__*,short,short,int) ; 
 int EF_AFTER_WRAP ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EDIT_MoveUp_ML(EDITSTATE *es, BOOL extend)
{
	INT s = es->selection_start;
	INT e = es->selection_end;
	BOOL after_wrap = (es->flags & EF_AFTER_WRAP);
	LRESULT pos = EDIT_EM_PosFromChar(es, e, after_wrap);
	INT x = (short)LOWORD(pos);
	INT y = (short)HIWORD(pos);

	e = EDIT_CharFromPos(es, x, y - es->line_height, &after_wrap);
	if (!extend)
		s = e;
	EDIT_EM_SetSel(es, s, e, after_wrap);
	EDIT_EM_ScrollCaret(es);
}