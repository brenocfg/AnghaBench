#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int style; int flags; int /*<<< orphan*/  selection_start; int /*<<< orphan*/  selection_end; } ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_1__ EDITSTATE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_CharFromPos (TYPE_1__*,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  EDIT_EM_PosFromChar (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EDIT_EM_ScrollCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_SetSel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int EF_AFTER_WRAP ; 
 int ES_MULTILINE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_text_length (TYPE_1__*) ; 

__attribute__((used)) static void EDIT_MoveEnd(EDITSTATE *es, BOOL extend, BOOL ctrl)
{
	BOOL after_wrap = FALSE;
	INT e;

	/* Pass a high value in x to make sure of receiving the end of the line */
	if (!ctrl && (es->style & ES_MULTILINE))
		e = EDIT_CharFromPos(es, 0x3fffffff,
			HIWORD(EDIT_EM_PosFromChar(es, es->selection_end, es->flags & EF_AFTER_WRAP)), &after_wrap);
	else
		e = get_text_length(es);
	EDIT_EM_SetSel(es, extend ? es->selection_start : e, e, after_wrap);
	EDIT_EM_ScrollCaret(es);
}