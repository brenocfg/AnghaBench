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
struct TYPE_7__ {int flags; int style; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  selection_end; int /*<<< orphan*/  line_height; int /*<<< orphan*/  selection_start; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCaret (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_InvalidateText (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_NOTIFY_PARENT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_SetCaretPos (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EDIT_WM_Paint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int EF_AFTER_WRAP ; 
 int EF_FOCUSED ; 
 int /*<<< orphan*/  EN_SETFOCUS ; 
 int ES_MULTILINE ; 
 int ES_NOHIDESEL ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ IsWindowVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowCaret (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EDIT_WM_SetFocus(EDITSTATE *es)
{
	es->flags |= EF_FOCUSED;

        if (!(es->style & ES_NOHIDESEL))
            EDIT_InvalidateText(es, es->selection_start, es->selection_end);

        /* single line edit updates itself */
        if (IsWindowVisible(es->hwndSelf) && !(es->style & ES_MULTILINE))
        {
            HDC hdc = GetDC(es->hwndSelf);
            EDIT_WM_Paint(es, hdc);
            ReleaseDC(es->hwndSelf, hdc);
        }

	CreateCaret(es->hwndSelf, 0, 1, es->line_height);
	EDIT_SetCaretPos(es, es->selection_end,
			 es->flags & EF_AFTER_WRAP);
	ShowCaret(es->hwndSelf);
	EDIT_NOTIFY_PARENT(es, EN_SETFOCUS);
}