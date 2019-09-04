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
struct TYPE_9__ {scalar_t__ selection_end; scalar_t__ selection_start; int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int LRESULT ;
typedef  scalar_t__* LPCWSTR ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_EM_EmptyUndoBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_ReplaceSel (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_EM_ScrollCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_SetRectNP (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_UpdateScrollInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_WM_SetFont (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 

__attribute__((used)) static LRESULT EDIT_WM_Create(EDITSTATE *es, LPCWSTR name)
{
        RECT clientRect;

	TRACE("%s\n", debugstr_w(name));
       /*
        *	To initialize some final structure members, we call some helper
        *	functions.  However, since the EDITSTATE is not consistent (i.e.
        *	not fully initialized), we should be very careful which
        *	functions can be called, and in what order.
        */
        EDIT_WM_SetFont(es, 0, FALSE);
        EDIT_EM_EmptyUndoBuffer(es);

        /* We need to calculate the format rect
           (applications may send EM_SETMARGINS before the control gets visible) */
        GetClientRect(es->hwndSelf, &clientRect);
        EDIT_SetRectNP(es, &clientRect);

       if (name && *name) {
	   EDIT_EM_ReplaceSel(es, FALSE, name, FALSE, FALSE);
	   /* if we insert text to the editline, the text scrolls out
            * of the window, as the caret is placed after the insert
            * pos normally; thus we reset es->selection... to 0 and
            * update caret
            */
	   es->selection_start = es->selection_end = 0;
           /* Adobe Photoshop does NOT like this. and MSDN says that EN_CHANGE
            * Messages are only to be sent when the USER does something to
            * change the contents. So I am removing this EN_CHANGE
            *
            * EDIT_NOTIFY_PARENT(es, EN_CHANGE);
            */
	   EDIT_EM_ScrollCaret(es);
       }
       /* force scroll info update */
       EDIT_UpdateScrollInfo(es);
       /* The rule seems to return 1 here for success */
       /* Power Builder masked edit controls will crash  */
       /* if not. */
       /* FIXME: is that in all cases so ? */
       return 1;
}