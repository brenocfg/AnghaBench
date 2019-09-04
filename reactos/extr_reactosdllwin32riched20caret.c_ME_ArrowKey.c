#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  texthost; int /*<<< orphan*/ * pCursors; void* bCaretAtEnd; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Cursor ;
typedef  void* BOOL ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  ITextHost_TxShowCaret (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ME_ArrowCtrlEnd (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_ArrowCtrlHome (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_ArrowEnd (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_ArrowHome (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_ArrowPageDown (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_ArrowPageUp (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_CheckCharOffsets (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_EnsureVisible (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_InvalidateSelection (TYPE_1__*) ; 
 void* ME_MoveCursorChars (TYPE_1__*,int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  ME_MoveCursorLines (TYPE_1__*,int /*<<< orphan*/ *,int,void*) ; 
 void* ME_MoveCursorWords (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ME_Repaint (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_SendSelChange (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_ShowCaret (TYPE_1__*) ; 
#define  VK_DOWN 135 
#define  VK_END 134 
#define  VK_HOME 133 
#define  VK_LEFT 132 
#define  VK_NEXT 131 
#define  VK_PRIOR 130 
#define  VK_RIGHT 129 
#define  VK_UP 128 

BOOL
ME_ArrowKey(ME_TextEditor *editor, int nVKey, BOOL extend, BOOL ctrl)
{
  int nCursor = 0;
  ME_Cursor *p = &editor->pCursors[nCursor];
  ME_Cursor tmp_curs = *p;
  BOOL success = FALSE;

  ME_CheckCharOffsets(editor);
  switch(nVKey) {
    case VK_LEFT:
      editor->bCaretAtEnd = FALSE;
      if (ctrl)
        success = ME_MoveCursorWords(editor, &tmp_curs, -1);
      else
        success = ME_MoveCursorChars(editor, &tmp_curs, -1, extend);
      break;
    case VK_RIGHT:
      editor->bCaretAtEnd = FALSE;
      if (ctrl)
        success = ME_MoveCursorWords(editor, &tmp_curs, +1);
      else
        success = ME_MoveCursorChars(editor, &tmp_curs, +1, extend);
      break;
    case VK_UP:
      ME_MoveCursorLines(editor, &tmp_curs, -1, extend);
      break;
    case VK_DOWN:
      ME_MoveCursorLines(editor, &tmp_curs, +1, extend);
      break;
    case VK_PRIOR:
      ME_ArrowPageUp(editor, &tmp_curs);
      break;
    case VK_NEXT:
      ME_ArrowPageDown(editor, &tmp_curs);
      break;
    case VK_HOME: {
      if (ctrl)
        ME_ArrowCtrlHome(editor, &tmp_curs);
      else
        ME_ArrowHome(editor, &tmp_curs);
      editor->bCaretAtEnd = FALSE;
      break;
    }
    case VK_END:
      if (ctrl)
        ME_ArrowCtrlEnd(editor, &tmp_curs);
      else
        ME_ArrowEnd(editor, &tmp_curs);
      break;
  }

  if (!extend)
    editor->pCursors[1] = tmp_curs;
  *p = tmp_curs;

  ME_InvalidateSelection(editor);
  ME_Repaint(editor);
  ITextHost_TxShowCaret(editor->texthost, FALSE);
  ME_EnsureVisible(editor, &tmp_curs);
  ME_ShowCaret(editor);
  ME_SendSelChange(editor);
  return success;
}