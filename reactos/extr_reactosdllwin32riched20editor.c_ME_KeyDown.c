#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  chf ;
typedef  int WORD ;
struct TYPE_26__ {int cbSize; } ;
struct TYPE_25__ {int nUDArrowX; int styleFlags; int /*<<< orphan*/  hwndParent; int /*<<< orphan*/  bDialogMode; int /*<<< orphan*/  bEmulateVersion10; int /*<<< orphan*/  nSelectionType; scalar_t__ bMouseCaptured; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  TYPE_2__ CHARFORMAT2W ;
typedef  int BOOL ;

/* Variables and functions */
 int ES_READONLY ; 
 int FALSE ; 
 int GetKeyState (int) ; 
 int /*<<< orphan*/  MB_OK ; 
 int /*<<< orphan*/  ME_ArrowKey (TYPE_1__*,int const,int,int) ; 
 int /*<<< orphan*/  ME_CheckCharOffsets (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_CommitCoalescingUndo (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_CommitUndo (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_ContinueCoalescingTransaction (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_DeleteSelection (TYPE_1__*) ; 
 int ME_DeleteTextAtCursor (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ME_DumpStyleToBuf (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ME_GetSelectionCharFormat (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ME_IsSelection (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_MoveCursorFromTableRowStartParagraph (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_Redo (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_SendRequestResize (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ME_Undo (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_UpdateRepaint (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ME_UpdateSelectionLinkAttribute (TYPE_1__*) ; 
 int /*<<< orphan*/  MessageBoxA (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int TRUE ; 
#define  VK_BACK 140 
 int VK_CONTROL ; 
#define  VK_DELETE 139 
#define  VK_DOWN 138 
#define  VK_END 137 
#define  VK_ESCAPE 136 
#define  VK_HOME 135 
#define  VK_LEFT 134 
 int VK_MENU ; 
#define  VK_NEXT 133 
#define  VK_PRIOR 132 
#define  VK_RETURN 131 
#define  VK_RIGHT 130 
 int VK_SHIFT ; 
#define  VK_TAB 129 
#define  VK_UP 128 
 int /*<<< orphan*/  WM_CLOSE ; 
 int /*<<< orphan*/  WM_NEXTDLGCTL ; 
 int copy_or_cut (TYPE_1__*,int) ; 
 int /*<<< orphan*/  handle_EM_EXSETSEL (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int handle_enter (TYPE_1__*) ; 
 int paste_special (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stPosition ; 

__attribute__((used)) static BOOL
ME_KeyDown(ME_TextEditor *editor, WORD nKey)
{
  BOOL ctrl_is_down = GetKeyState(VK_CONTROL) & 0x8000;
  BOOL shift_is_down = GetKeyState(VK_SHIFT) & 0x8000;

  if (editor->bMouseCaptured)
      return FALSE;
  if (nKey != VK_SHIFT && nKey != VK_CONTROL && nKey != VK_MENU)
      editor->nSelectionType = stPosition;

  switch (nKey)
  {
    case VK_LEFT:
    case VK_RIGHT:
    case VK_HOME:
    case VK_END:
        editor->nUDArrowX = -1;
        /* fall through */
    case VK_UP:
    case VK_DOWN:
    case VK_PRIOR:
    case VK_NEXT:
      ME_CommitUndo(editor); /* End coalesced undos for typed characters */
      ME_ArrowKey(editor, nKey, shift_is_down, ctrl_is_down);
      return TRUE;
    case VK_BACK:
    case VK_DELETE:
      editor->nUDArrowX = -1;
      /* FIXME backspace and delete aren't the same, they act different wrt paragraph style of the merged paragraph */
      if (editor->styleFlags & ES_READONLY)
        return FALSE;
      if (ME_IsSelection(editor))
      {
        ME_DeleteSelection(editor);
        ME_CommitUndo(editor);
      }
      else if (nKey == VK_DELETE)
      {
        /* Delete stops group typing.
         * (See MSDN remarks on EM_STOPGROUPTYPING message) */
        ME_DeleteTextAtCursor(editor, 1, 1);
        ME_CommitUndo(editor);
      }
      else if (ME_ArrowKey(editor, VK_LEFT, FALSE, FALSE))
      {
        BOOL bDeletionSucceeded;
        /* Backspace can be grouped for a single undo */
        ME_ContinueCoalescingTransaction(editor);
        bDeletionSucceeded = ME_DeleteTextAtCursor(editor, 1, 1);
        if (!bDeletionSucceeded && !editor->bEmulateVersion10) { /* v4.1 */
          /* Deletion was prevented so the cursor is moved back to where it was.
           * (e.g. this happens when trying to delete cell boundaries)
           */
          ME_ArrowKey(editor, VK_RIGHT, FALSE, FALSE);
        }
        ME_CommitCoalescingUndo(editor);
      }
      else
        return TRUE;
      ME_MoveCursorFromTableRowStartParagraph(editor);
      ME_UpdateSelectionLinkAttribute(editor);
      ME_UpdateRepaint(editor, FALSE);
      ME_SendRequestResize(editor, FALSE);
      return TRUE;
    case VK_RETURN:
      if (!editor->bEmulateVersion10)
          return handle_enter(editor);
      break;
    case VK_ESCAPE:
      if (editor->bDialogMode && editor->hwndParent)
        PostMessageW(editor->hwndParent, WM_CLOSE, 0, 0);
      return TRUE;
    case VK_TAB:
      if (editor->bDialogMode && editor->hwndParent)
        SendMessageW(editor->hwndParent, WM_NEXTDLGCTL, shift_is_down, 0);
      return TRUE;
    case 'A':
      if (ctrl_is_down)
      {
        handle_EM_EXSETSEL( editor, 0, -1 );
        return TRUE;
      }
      break;
    case 'V':
      if (ctrl_is_down)
        return paste_special( editor, 0, NULL, FALSE );
      break;
    case 'C':
    case 'X':
      if (ctrl_is_down)
        return copy_or_cut(editor, nKey == 'X');
      break;
    case 'Z':
      if (ctrl_is_down)
      {
        ME_Undo(editor);
        return TRUE;
      }
      break;
    case 'Y':
      if (ctrl_is_down)
      {
        ME_Redo(editor);
        return TRUE;
      }
      break;

    default:
      if (nKey != VK_SHIFT && nKey != VK_CONTROL && nKey && nKey != VK_MENU)
          editor->nUDArrowX = -1;
      if (ctrl_is_down)
      {
        if (nKey == 'W')
        {
          CHARFORMAT2W chf;
          char buf[2048];
          chf.cbSize = sizeof(chf);
          
          ME_GetSelectionCharFormat(editor, &chf);
          ME_DumpStyleToBuf(&chf, buf);
          MessageBoxA(NULL, buf, "Style dump", MB_OK);
        }
        if (nKey == 'Q')
        {
          ME_CheckCharOffsets(editor);
        }
      }
  }
  return FALSE;
}