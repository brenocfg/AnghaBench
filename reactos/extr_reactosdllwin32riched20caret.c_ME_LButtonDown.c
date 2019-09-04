#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int left; } ;
struct TYPE_14__ {scalar_t__ nPos; } ;
struct TYPE_13__ {scalar_t__ nPos; } ;
struct TYPE_16__ {int nUDArrowX; scalar_t__ nSelectionType; int /*<<< orphan*/  texthost; int /*<<< orphan*/ * pCursors; TYPE_3__ rcFormat; int /*<<< orphan*/  bCaretAtEnd; TYPE_2__ vert_si; TYPE_1__ horz_si; } ;
typedef  TYPE_4__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Cursor ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ GetKeyState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITextHost_TxShowCaret (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ME_ExtendAnchorSelection (TYPE_4__*) ; 
 int /*<<< orphan*/  ME_FindPixelPos (TYPE_4__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ME_InvalidateSelection (TYPE_4__*) ; 
 int ME_IsSelection (TYPE_4__*) ; 
 int /*<<< orphan*/  ME_SelectByType (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_SendSelChange (TYPE_4__*) ; 
 int /*<<< orphan*/  ME_ShowCaret (TYPE_4__*) ; 
 int /*<<< orphan*/  VK_SHIFT ; 
 int /*<<< orphan*/  stDocument ; 
 int /*<<< orphan*/  stLine ; 
 int /*<<< orphan*/  stParagraph ; 
 scalar_t__ stPosition ; 
 int /*<<< orphan*/  stWord ; 

void ME_LButtonDown(ME_TextEditor *editor, int x, int y, int clickNum)
{
  ME_Cursor tmp_cursor;
  BOOL is_selection = FALSE, is_shift;

  editor->nUDArrowX = -1;

  x += editor->horz_si.nPos;
  y += editor->vert_si.nPos;

  tmp_cursor = editor->pCursors[0];
  is_selection = ME_IsSelection(editor);
  is_shift = GetKeyState(VK_SHIFT) < 0;

  ME_FindPixelPos(editor, x, y, &editor->pCursors[0], &editor->bCaretAtEnd, FALSE);

  if (x >= editor->rcFormat.left || is_shift)
  {
    if (clickNum > 1)
    {
      editor->pCursors[1] = editor->pCursors[0];
      if (is_shift) {
          if (x >= editor->rcFormat.left)
              ME_SelectByType(editor, stWord);
          else
              ME_SelectByType(editor, stParagraph);
      } else if (clickNum % 2 == 0) {
          ME_SelectByType(editor, stWord);
      } else {
          ME_SelectByType(editor, stParagraph);
      }
    }
    else if (!is_shift)
    {
      editor->nSelectionType = stPosition;
      editor->pCursors[1] = editor->pCursors[0];
    }
    else if (!is_selection)
    {
      editor->nSelectionType = stPosition;
      editor->pCursors[1] = tmp_cursor;
    }
    else if (editor->nSelectionType != stPosition)
    {
      ME_ExtendAnchorSelection(editor);
    }
  }
  else
  {
    if (clickNum < 2) {
        ME_SelectByType(editor, stLine);
    } else if (clickNum % 2 == 0 || is_shift) {
        ME_SelectByType(editor, stParagraph);
    } else {
        ME_SelectByType(editor, stDocument);
    }
  }
  ME_InvalidateSelection(editor);
  ITextHost_TxShowCaret(editor->texthost, FALSE);
  ME_ShowCaret(editor);
  ME_SendSelChange(editor);
}