#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sbi ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_23__ {TYPE_3__* pRun; } ;
struct TYPE_17__ {short top; short left; short bottom; } ;
struct TYPE_22__ {scalar_t__ nSelectionType; int /*<<< orphan*/  texthost; TYPE_1__ rcFormat; scalar_t__ bEmulateVersion10; scalar_t__ bMouseCaptured; scalar_t__ hWnd; } ;
struct TYPE_21__ {short x; short y; } ;
struct TYPE_20__ {int cbSize; int* rgstate; int /*<<< orphan*/  rcScrollBar; } ;
struct TYPE_18__ {int /*<<< orphan*/  run; } ;
struct TYPE_19__ {TYPE_2__ member; } ;
typedef  TYPE_4__ SCROLLBARINFO ;
typedef  TYPE_5__ POINT ;
typedef  TYPE_6__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Run ;
typedef  TYPE_7__ ME_Cursor ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetMessagePos () ; 
 int /*<<< orphan*/  GetScrollBarInfo (scalar_t__,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ IDC_ARROW ; 
 scalar_t__ IDC_HAND ; 
 scalar_t__ IDC_IBEAM ; 
 int /*<<< orphan*/  ITextHost_TxScreenToClient (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ITextHost_TxSetCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadCursorW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_CharFromPos (TYPE_6__*,short,short,TYPE_7__*,scalar_t__*) ; 
 int ME_GetCursorOfs (TYPE_7__*) ; 
 int /*<<< orphan*/  ME_GetSelectionOfs (TYPE_6__*,int*,int*) ; 
 scalar_t__ ME_IsSelection (TYPE_6__*) ; 
 int /*<<< orphan*/  OBJID_HSCROLL ; 
 int /*<<< orphan*/  OBJID_VSCROLL ; 
 scalar_t__ PtInRect (int /*<<< orphan*/ *,TYPE_5__) ; 
 int STATE_SYSTEM_INVISIBLE ; 
 int STATE_SYSTEM_OFFSCREEN ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  hLeft ; 
 scalar_t__ is_link (int /*<<< orphan*/ *) ; 
 scalar_t__ stLine ; 

__attribute__((used)) static BOOL ME_SetCursor(ME_TextEditor *editor)
{
  ME_Cursor cursor;
  POINT pt;
  BOOL isExact;
  SCROLLBARINFO sbi;
  DWORD messagePos = GetMessagePos();
  pt.x = (short)LOWORD(messagePos);
  pt.y = (short)HIWORD(messagePos);

  if (editor->hWnd)
  {
    sbi.cbSize = sizeof(sbi);
    GetScrollBarInfo(editor->hWnd, OBJID_HSCROLL, &sbi);
    if (!(sbi.rgstate[0] & (STATE_SYSTEM_INVISIBLE|STATE_SYSTEM_OFFSCREEN)) &&
        PtInRect(&sbi.rcScrollBar, pt))
    {
        ITextHost_TxSetCursor(editor->texthost,
                              LoadCursorW(NULL, (WCHAR*)IDC_ARROW), FALSE);
        return TRUE;
    }
    sbi.cbSize = sizeof(sbi);
    GetScrollBarInfo(editor->hWnd, OBJID_VSCROLL, &sbi);
    if (!(sbi.rgstate[0] & (STATE_SYSTEM_INVISIBLE|STATE_SYSTEM_OFFSCREEN)) &&
        PtInRect(&sbi.rcScrollBar, pt))
    {
        ITextHost_TxSetCursor(editor->texthost,
                              LoadCursorW(NULL, (WCHAR*)IDC_ARROW), FALSE);
        return TRUE;
    }
  }
  ITextHost_TxScreenToClient(editor->texthost, &pt);

  if (editor->nSelectionType == stLine && editor->bMouseCaptured) {
      ITextHost_TxSetCursor(editor->texthost, hLeft, FALSE);
      return TRUE;
  }
  if (!editor->bEmulateVersion10 /* v4.1 */ &&
      pt.y < editor->rcFormat.top &&
      pt.x < editor->rcFormat.left)
  {
      ITextHost_TxSetCursor(editor->texthost, hLeft, FALSE);
      return TRUE;
  }
  if (pt.y < editor->rcFormat.top || pt.y > editor->rcFormat.bottom)
  {
      if (editor->bEmulateVersion10) /* v1.0 - 3.0 */
          ITextHost_TxSetCursor(editor->texthost,
                                LoadCursorW(NULL, (WCHAR*)IDC_ARROW), FALSE);
      else /* v4.1 */
          ITextHost_TxSetCursor(editor->texthost,
                                LoadCursorW(NULL, (WCHAR*)IDC_IBEAM), TRUE);
      return TRUE;
  }
  if (pt.x < editor->rcFormat.left)
  {
      ITextHost_TxSetCursor(editor->texthost, hLeft, FALSE);
      return TRUE;
  }
  ME_CharFromPos(editor, pt.x, pt.y, &cursor, &isExact);
  if (isExact)
  {
      ME_Run *run;

      run = &cursor.pRun->member.run;
      if (is_link( run ))
      {
          ITextHost_TxSetCursor(editor->texthost,
                                LoadCursorW(NULL, (WCHAR*)IDC_HAND),
                                FALSE);
          return TRUE;
      }

      if (ME_IsSelection(editor))
      {
          int selStart, selEnd;
          int offset = ME_GetCursorOfs(&cursor);

          ME_GetSelectionOfs(editor, &selStart, &selEnd);
          if (selStart <= offset && selEnd >= offset) {
              ITextHost_TxSetCursor(editor->texthost,
                                    LoadCursorW(NULL, (WCHAR*)IDC_ARROW),
                                    FALSE);
              return TRUE;
          }
      }
  }
  ITextHost_TxSetCursor(editor->texthost,
                        LoadCursorW(NULL, (WCHAR*)IDC_IBEAM), TRUE);
  return TRUE;
}