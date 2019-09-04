#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ nOffset; TYPE_3__* pRun; } ;
struct TYPE_21__ {TYPE_7__* pCursors; } ;
struct TYPE_18__ {int nFlags; scalar_t__ len; } ;
struct TYPE_19__ {TYPE_1__ run; } ;
struct TYPE_20__ {TYPE_2__ member; } ;
typedef  TYPE_4__ ME_TextEditor ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MERF_ENDPARA ; 
 int /*<<< orphan*/  ME_CursorFromCharOfs (TYPE_4__*,int,TYPE_7__*) ; 
 int /*<<< orphan*/  ME_GetSelectionOfs (TYPE_4__*,int*,int*) ; 
 int ME_GetTextLength (TYPE_4__*) ; 
 int /*<<< orphan*/  ME_InvalidateSelection (TYPE_4__*) ; 
 int /*<<< orphan*/  ME_MoveCursorChars (TYPE_4__*,TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_Repaint (TYPE_4__*) ; 
 int /*<<< orphan*/  ME_SetCursorToEnd (TYPE_4__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_SetCursorToStart (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  TRUE ; 

int ME_SetSelection(ME_TextEditor *editor, int from, int to)
{
  int selectionEnd = 0;
  const int len = ME_GetTextLength(editor);

  /* all negative values are effectively the same */
  if (from < 0)
    from = -1;
  if (to < 0)
    to = -1;

  /* select all */
  if (from == 0 && to == -1)
  {
    ME_SetCursorToStart(editor, &editor->pCursors[1]);
    ME_SetCursorToEnd(editor, &editor->pCursors[0], TRUE);
    ME_InvalidateSelection(editor);
    return len + 1;
  }

  /* if both values are equal and also out of bound, that means to */
  /* put the selection at the end of the text */
  if ((from == to) && (to < 0 || to > len))
  {
    selectionEnd = 1;
  }
  else
  {
    /* if from is negative and to is positive then selection is */
    /* deselected and caret moved to end of the current selection */
    if (from < 0)
    {
      int start, end;
      ME_GetSelectionOfs(editor, &start, &end);
      if (start != end)
      {
          if (end > len)
          {
              editor->pCursors[0].nOffset = 0;
              end --;
          }
          editor->pCursors[1] = editor->pCursors[0];
          ME_Repaint(editor);
      }
      return end;
    }

    /* adjust to if it's a negative value */
    if (to < 0)
      to = len + 1;

    /* flip from and to if they are reversed */
    if (from>to)
    {
      int tmp = from;
      from = to;
      to = tmp;
    }

    /* after fiddling with the values, we find from > len && to > len */
    if (from > len)
      selectionEnd = 1;
    /* special case with to too big */
    else if (to > len)
      to = len + 1;
  }

  if (selectionEnd)
  {
    ME_SetCursorToEnd(editor, &editor->pCursors[0], FALSE);
    editor->pCursors[1] = editor->pCursors[0];
    ME_InvalidateSelection(editor);
    return len;
  }

  ME_CursorFromCharOfs(editor, from, &editor->pCursors[1]);
  editor->pCursors[0] = editor->pCursors[1];
  ME_MoveCursorChars(editor, &editor->pCursors[0], to - from, FALSE);
  /* Selection is not allowed in the middle of an end paragraph run. */
  if (editor->pCursors[1].pRun->member.run.nFlags & MERF_ENDPARA)
    editor->pCursors[1].nOffset = 0;
  if (editor->pCursors[0].pRun->member.run.nFlags & MERF_ENDPARA)
  {
    if (to > len)
      editor->pCursors[0].nOffset = editor->pCursors[0].pRun->member.run.len;
    else
      editor->pCursors[0].nOffset = 0;
  }
  return to;
}