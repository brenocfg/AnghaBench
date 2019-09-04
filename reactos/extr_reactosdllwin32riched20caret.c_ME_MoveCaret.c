#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ right; } ;
struct TYPE_7__ {int /*<<< orphan*/  texthost; TYPE_1__ rcFormat; scalar_t__ bHaveFocus; int /*<<< orphan*/ * pCursors; } ;
typedef  TYPE_2__ ME_TextEditor ;

/* Variables and functions */
 int /*<<< orphan*/  ITextHost_TxCreateCaret (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ITextHost_TxSetCaretPos (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ME_GetCursorCoordinates (TYPE_2__*,int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/  ME_IsSelection (TYPE_2__*) ; 
 int min (int,scalar_t__) ; 

void
ME_MoveCaret(ME_TextEditor *editor)
{
  int x, y, height;

  ME_GetCursorCoordinates(editor, &editor->pCursors[0], &x, &y, &height);
  if(editor->bHaveFocus && !ME_IsSelection(editor))
  {
    x = min(x, editor->rcFormat.right-1);
    ITextHost_TxCreateCaret(editor->texthost, NULL, 0, height);
    ITextHost_TxSetCaretPos(editor->texthost, x, y);
  }
}