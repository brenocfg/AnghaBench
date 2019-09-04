#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ lpszName; } ;
struct TYPE_12__ {scalar_t__ lpszName; } ;
struct TYPE_11__ {int styleFlags; int /*<<< orphan*/ * pCursors; int /*<<< orphan*/  texthost; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LPARAM ;
typedef  int INT ;
typedef  TYPE_2__ CREATESTRUCTW ;
typedef  TYPE_3__ CREATESTRUCTA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ESB_DISABLE_BOTH ; 
 int ES_DISABLENOSCROLL ; 
 int /*<<< orphan*/  ITextHost_TxEnableScrollBar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITextHost_TxSetScrollRange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITextHost_TxShowScrollBar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_CommitUndo (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_MoveCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_SetCursorToStart (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_SetDefaultFormatRect (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_SetText (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_WrapMarkedParagraphs (TYPE_1__*) ; 
 int /*<<< orphan*/  SB_HORZ ; 
 int /*<<< orphan*/  SB_VERT ; 
 int /*<<< orphan*/  TRUE ; 
 int WS_HSCROLL ; 
 int WS_VSCROLL ; 

__attribute__((used)) static LRESULT ME_WmCreate(ME_TextEditor *editor, LPARAM lParam, BOOL unicode)
{
  CREATESTRUCTW *createW = (CREATESTRUCTW*)lParam;
  CREATESTRUCTA *createA = (CREATESTRUCTA*)lParam;
  void *text = NULL;
  INT max;

  if (lParam)
    text = unicode ? (void*)createW->lpszName : (void*)createA->lpszName;

  ME_SetDefaultFormatRect(editor);

  max = (editor->styleFlags & ES_DISABLENOSCROLL) ? 1 : 0;
  if (~editor->styleFlags & ES_DISABLENOSCROLL || editor->styleFlags & WS_VSCROLL)
    ITextHost_TxSetScrollRange(editor->texthost, SB_VERT, 0, max, TRUE);

  if (~editor->styleFlags & ES_DISABLENOSCROLL || editor->styleFlags & WS_HSCROLL)
    ITextHost_TxSetScrollRange(editor->texthost, SB_HORZ, 0, max, TRUE);

  if (editor->styleFlags & ES_DISABLENOSCROLL)
  {
    if (editor->styleFlags & WS_VSCROLL)
    {
      ITextHost_TxEnableScrollBar(editor->texthost, SB_VERT, ESB_DISABLE_BOTH);
      ITextHost_TxShowScrollBar(editor->texthost, SB_VERT, TRUE);
    }
    if (editor->styleFlags & WS_HSCROLL)
    {
      ITextHost_TxEnableScrollBar(editor->texthost, SB_HORZ, ESB_DISABLE_BOTH);
      ITextHost_TxShowScrollBar(editor->texthost, SB_HORZ, TRUE);
    }
  }

  if (text)
  {
    ME_SetText(editor, text, unicode);
    ME_SetCursorToStart(editor, &editor->pCursors[0]);
    ME_SetCursorToStart(editor, &editor->pCursors[1]);
  }

  ME_CommitUndo(editor);
  ME_WrapMarkedParagraphs(editor);
  ME_MoveCaret(editor);
  return 0;
}