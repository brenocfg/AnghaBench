#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ cx; scalar_t__ cy; } ;
struct TYPE_9__ {int nPos; int nMax; int /*<<< orphan*/  nMin; scalar_t__ nPage; } ;
struct TYPE_8__ {int nPos; int nMax; int /*<<< orphan*/  nMin; } ;
struct TYPE_11__ {int styleFlags; scalar_t__ nTotalWidth; scalar_t__ nTotalLength; int /*<<< orphan*/  texthost; TYPE_3__ sizeWindow; scalar_t__ hWnd; int /*<<< orphan*/  rcFormat; TYPE_2__ vert_si; TYPE_1__ horz_si; } ;
typedef  TYPE_4__ ME_TextEditor ;
typedef  int LONG ;
typedef  int BOOL ;

/* Variables and functions */
 int ES_DISABLENOSCROLL ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetWindowLongW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITextHost_TxInvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITextHost_TxScrollWindowEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITextHost_TxSetScrollPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITextHost_TxShowScrollBar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ME_Repaint (TYPE_4__*) ; 
 int /*<<< orphan*/  ME_UpdateScrollBar (TYPE_4__*) ; 
 int MulDiv (int,int,int) ; 
 int /*<<< orphan*/  SB_HORZ ; 
 int /*<<< orphan*/  SB_VERT ; 
 int /*<<< orphan*/  SW_INVALIDATE ; 
 int /*<<< orphan*/  TRUE ; 
 int WS_HSCROLL ; 
 int WS_VSCROLL ; 
 scalar_t__ abs (int) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 

void ME_ScrollAbs(ME_TextEditor *editor, int x, int y)
{
  BOOL bScrollBarIsVisible, bScrollBarWillBeVisible;
  int scrollX = 0, scrollY = 0;

  if (editor->horz_si.nPos != x) {
    x = min(x, editor->horz_si.nMax);
    x = max(x, editor->horz_si.nMin);
    scrollX = editor->horz_si.nPos - x;
    editor->horz_si.nPos = x;
    if (editor->horz_si.nMax > 0xFFFF) /* scale to 16-bit value */
      x = MulDiv(x, 0xFFFF, editor->horz_si.nMax);
    ITextHost_TxSetScrollPos(editor->texthost, SB_HORZ, x, TRUE);
  }

  if (editor->vert_si.nPos != y) {
    y = min(y, editor->vert_si.nMax - (int)editor->vert_si.nPage);
    y = max(y, editor->vert_si.nMin);
    scrollY = editor->vert_si.nPos - y;
    editor->vert_si.nPos = y;
    if (editor->vert_si.nMax > 0xFFFF) /* scale to 16-bit value */
      y = MulDiv(y, 0xFFFF, editor->vert_si.nMax);
    ITextHost_TxSetScrollPos(editor->texthost, SB_VERT, y, TRUE);
  }

  if (abs(scrollX) > editor->sizeWindow.cx ||
      abs(scrollY) > editor->sizeWindow.cy)
    ITextHost_TxInvalidateRect(editor->texthost, NULL, TRUE);
  else
    ITextHost_TxScrollWindowEx(editor->texthost, scrollX, scrollY,
                               &editor->rcFormat, &editor->rcFormat,
                               NULL, NULL, SW_INVALIDATE);
  ME_Repaint(editor);

  if (editor->hWnd)
  {
    LONG winStyle = GetWindowLongW(editor->hWnd, GWL_STYLE);
    if (editor->styleFlags & WS_HSCROLL)
    {
      bScrollBarIsVisible = (winStyle & WS_HSCROLL) != 0;
      bScrollBarWillBeVisible = (editor->nTotalWidth > editor->sizeWindow.cx
                                 && (editor->styleFlags & WS_HSCROLL))
                                || (editor->styleFlags & ES_DISABLENOSCROLL);
      if (bScrollBarIsVisible != bScrollBarWillBeVisible)
        ITextHost_TxShowScrollBar(editor->texthost, SB_HORZ,
                                  bScrollBarWillBeVisible);
    }

    if (editor->styleFlags & WS_VSCROLL)
    {
      bScrollBarIsVisible = (winStyle & WS_VSCROLL) != 0;
      bScrollBarWillBeVisible = (editor->nTotalLength > editor->sizeWindow.cy
                                 && (editor->styleFlags & WS_VSCROLL)
                                 && (editor->styleFlags & ES_MULTILINE))
                                || (editor->styleFlags & ES_DISABLENOSCROLL);
      if (bScrollBarIsVisible != bScrollBarWillBeVisible)
        ITextHost_TxShowScrollBar(editor->texthost, SB_VERT,
                                  bScrollBarWillBeVisible);
    }
  }
  ME_UpdateScrollBar(editor);
}