#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_50__   TYPE_9__ ;
typedef  struct TYPE_49__   TYPE_8__ ;
typedef  struct TYPE_48__   TYPE_7__ ;
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_28__ ;
typedef  struct TYPE_41__   TYPE_1__ ;
typedef  struct TYPE_40__   TYPE_19__ ;
typedef  struct TYPE_39__   TYPE_12__ ;
typedef  struct TYPE_38__   TYPE_11__ ;
typedef  struct TYPE_37__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  char WCHAR ;
struct TYPE_40__ {scalar_t__ wNumbering; } ;
struct TYPE_49__ {int nFlags; TYPE_7__* eop_run; TYPE_19__ fmt; TYPE_11__* prev_para; TYPE_11__* next_para; int /*<<< orphan*/  nCharOfs; } ;
struct TYPE_50__ {TYPE_8__ para; } ;
struct TYPE_48__ {int /*<<< orphan*/ * style; } ;
struct TYPE_46__ {scalar_t__ nCharOfs; int nFlags; int /*<<< orphan*/ * style; } ;
struct TYPE_47__ {TYPE_5__ run; } ;
struct TYPE_45__ {TYPE_3__* pFirst; } ;
struct TYPE_41__ {TYPE_11__* next_para; } ;
struct TYPE_43__ {TYPE_1__ para; } ;
struct TYPE_44__ {TYPE_2__ member; } ;
struct TYPE_42__ {TYPE_6__ member; } ;
struct TYPE_39__ {scalar_t__ nOffset; TYPE_28__* pRun; TYPE_11__* pPara; } ;
struct TYPE_38__ {TYPE_9__ member; } ;
struct TYPE_37__ {int styleFlags; int nTextLimit; int /*<<< orphan*/  bEmulateVersion10; TYPE_12__* pCursors; TYPE_4__* pBuffer; scalar_t__ hwndParent; scalar_t__ bDialogMode; } ;
typedef  TYPE_10__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Style ;
typedef  TYPE_11__ ME_DisplayItem ;
typedef  TYPE_12__ ME_Cursor ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ DC_HASDEFID ; 
 int /*<<< orphan*/  DM_GETDEFID ; 
 int ES_MULTILINE ; 
 int ES_READONLY ; 
 int ES_WANTRETURN ; 
 int FALSE ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int GetKeyState (int /*<<< orphan*/ ) ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MB_ICONERROR ; 
 int MEPF_ROWEND ; 
 int MEPF_ROWSTART ; 
 int MERF_ENDPARA ; 
 TYPE_11__* ME_AppendTableRow (TYPE_10__*,TYPE_11__*) ; 
 int /*<<< orphan*/  ME_CheckTablesForCorruption (TYPE_10__*) ; 
 int /*<<< orphan*/  ME_CommitCoalescingUndo (TYPE_10__*) ; 
 int /*<<< orphan*/  ME_CommitUndo (TYPE_10__*) ; 
 int /*<<< orphan*/  ME_ContinueCoalescingTransaction (TYPE_10__*) ; 
 TYPE_28__* ME_FindItemBack (TYPE_11__*,int /*<<< orphan*/ ) ; 
 void* ME_FindItemFwd (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ME_GetInsertStyle (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_GetSelectionOfs (TYPE_10__*,int*,int*) ; 
 int ME_GetTextLength (TYPE_10__*) ; 
 int /*<<< orphan*/  ME_InsertEndRowFromCursor (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_InsertTextFromCursor (TYPE_10__*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ME_IsInTable (TYPE_11__*) ; 
 int /*<<< orphan*/  ME_ReleaseStyle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_SaveTempStyle (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_SetDefaultParaFormat (TYPE_10__*,TYPE_19__*) ; 
 int /*<<< orphan*/  ME_UpdateRepaint (TYPE_10__*,int) ; 
 int /*<<< orphan*/  ME_UpdateSelectionLinkAttribute (TYPE_10__*) ; 
 int /*<<< orphan*/  MessageBeep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetCursor (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  VK_CONTROL ; 
 int /*<<< orphan*/  VK_RETURN ; 
 int /*<<< orphan*/  VK_SHIFT ; 
 int /*<<< orphan*/  WM_KEYDOWN ; 
 int /*<<< orphan*/  WM_NEXTDLGCTL ; 
 int /*<<< orphan*/  diRun ; 
 int /*<<< orphan*/  mark_para_rewrap (TYPE_10__*,TYPE_11__*) ; 

__attribute__((used)) static BOOL handle_enter(ME_TextEditor *editor)
{
    BOOL ctrl_is_down = GetKeyState(VK_CONTROL) & 0x8000;
    BOOL shift_is_down = GetKeyState(VK_SHIFT) & 0x8000;

    if (editor->bDialogMode)
    {
        if (ctrl_is_down)
            return TRUE;

        if (!(editor->styleFlags & ES_WANTRETURN))
        {
            if (editor->hwndParent)
            {
                DWORD dw;
                dw = SendMessageW(editor->hwndParent, DM_GETDEFID, 0, 0);
                if (HIWORD(dw) == DC_HASDEFID)
                {
                    HWND hwDefCtrl = GetDlgItem(editor->hwndParent, LOWORD(dw));
                    if (hwDefCtrl)
                    {
                        SendMessageW(editor->hwndParent, WM_NEXTDLGCTL, (WPARAM)hwDefCtrl, TRUE);
                        PostMessageW(hwDefCtrl, WM_KEYDOWN, VK_RETURN, 0);
                    }
                }
            }
            return TRUE;
        }
    }

    if (editor->styleFlags & ES_MULTILINE)
    {
        static const WCHAR endl = '\r';
        static const WCHAR endlv10[] = {'\r','\n'};
        ME_Cursor cursor = editor->pCursors[0];
        ME_DisplayItem *para = cursor.pPara;
        int from, to;
        ME_Style *style, *eop_style;

        if (editor->styleFlags & ES_READONLY)
        {
            MessageBeep(MB_ICONERROR);
            return TRUE;
        }

        ME_GetSelectionOfs(editor, &from, &to);
        if (editor->nTextLimit > ME_GetTextLength(editor) - (to-from))
        {
            if (!editor->bEmulateVersion10) /* v4.1 */
            {
                if (para->member.para.nFlags & MEPF_ROWEND)
                {
                    /* Add a new table row after this row. */
                    para = ME_AppendTableRow(editor, para);
                    para = para->member.para.next_para;
                    editor->pCursors[0].pPara = para;
                    editor->pCursors[0].pRun = ME_FindItemFwd(para, diRun);
                    editor->pCursors[0].nOffset = 0;
                    editor->pCursors[1] = editor->pCursors[0];
                    ME_CommitUndo(editor);
                    ME_CheckTablesForCorruption(editor);
                    ME_UpdateRepaint(editor, FALSE);
                    return TRUE;
                }
                else if (para == editor->pCursors[1].pPara &&
                    cursor.nOffset + cursor.pRun->member.run.nCharOfs == 0 &&
                    para->member.para.prev_para->member.para.nFlags & MEPF_ROWSTART &&
                    !para->member.para.prev_para->member.para.nCharOfs)
                {
                    /* Insert a newline before the table. */
                    para = para->member.para.prev_para;
                    para->member.para.nFlags &= ~MEPF_ROWSTART;
                    editor->pCursors[0].pPara = para;
                    editor->pCursors[0].pRun = ME_FindItemFwd(para, diRun);
                    editor->pCursors[1] = editor->pCursors[0];
                    ME_InsertTextFromCursor(editor, 0, &endl, 1,
                    editor->pCursors[0].pRun->member.run.style);
                    para = editor->pBuffer->pFirst->member.para.next_para;
                    ME_SetDefaultParaFormat(editor, &para->member.para.fmt);
                    para->member.para.nFlags = 0;
                    mark_para_rewrap(editor, para);
                    editor->pCursors[0].pPara = para;
                    editor->pCursors[0].pRun = ME_FindItemFwd(para, diRun);
                    editor->pCursors[1] = editor->pCursors[0];
                    para->member.para.next_para->member.para.nFlags |= MEPF_ROWSTART;
                    ME_CommitCoalescingUndo(editor);
                    ME_CheckTablesForCorruption(editor);
                    ME_UpdateRepaint(editor, FALSE);
                    return TRUE;
                }
            }
            else /* v1.0 - 3.0 */
            {
                ME_DisplayItem *para = cursor.pPara;
                if (ME_IsInTable(para))
                {
                    if (cursor.pRun->member.run.nFlags & MERF_ENDPARA)
                    {
                        if (from == to)
                        {
                            ME_ContinueCoalescingTransaction(editor);
                            para = ME_AppendTableRow(editor, para);
                            editor->pCursors[0].pPara = para;
                            editor->pCursors[0].pRun = ME_FindItemFwd(para, diRun);
                            editor->pCursors[0].nOffset = 0;
                            editor->pCursors[1] = editor->pCursors[0];
                            ME_CommitCoalescingUndo(editor);
                            ME_UpdateRepaint(editor, FALSE);
                            return TRUE;
                        }
                    }
                    else
                    {
                        ME_ContinueCoalescingTransaction(editor);
                        if (cursor.pRun->member.run.nCharOfs + cursor.nOffset == 0 &&
                                !ME_IsInTable(para->member.para.prev_para))
                        {
                            /* Insert newline before table */
                            cursor.pRun = ME_FindItemBack(para, diRun);
                            if (cursor.pRun)
                            {
                                editor->pCursors[0].pRun = cursor.pRun;
                                editor->pCursors[0].pPara = para->member.para.prev_para;
                            }
                            editor->pCursors[0].nOffset = 0;
                            editor->pCursors[1] = editor->pCursors[0];
                            ME_InsertTextFromCursor(editor, 0, &endl, 1,
                            editor->pCursors[0].pRun->member.run.style);
                        }
                        else
                        {
                            editor->pCursors[1] = editor->pCursors[0];
                            para = ME_AppendTableRow(editor, para);
                            editor->pCursors[0].pPara = para;
                            editor->pCursors[0].pRun = ME_FindItemFwd(para, diRun);
                            editor->pCursors[0].nOffset = 0;
                            editor->pCursors[1] = editor->pCursors[0];
                        }
                        ME_CommitCoalescingUndo(editor);
                        ME_UpdateRepaint(editor, FALSE);
                        return TRUE;
                    }
                }
            }

            style = ME_GetInsertStyle(editor, 0);

            /* Normally the new eop style is the insert style, however in a list it is copied from the existing
            eop style (this prevents the list label style changing when the new eop is inserted).
            No extra ref is taken here on eop_style. */
            if (para->member.para.fmt.wNumbering)
                eop_style = para->member.para.eop_run->style;
            else
                eop_style = style;
            ME_ContinueCoalescingTransaction(editor);
            if (shift_is_down)
                ME_InsertEndRowFromCursor(editor, 0);
            else
                if (!editor->bEmulateVersion10)
                    ME_InsertTextFromCursor(editor, 0, &endl, 1, eop_style);
                else
                    ME_InsertTextFromCursor(editor, 0, endlv10, 2, eop_style);
            ME_CommitCoalescingUndo(editor);
            SetCursor(NULL);

            ME_UpdateSelectionLinkAttribute(editor);
            ME_UpdateRepaint(editor, FALSE);
            ME_SaveTempStyle(editor, style); /* set the temp insert style for the new para */
            ME_ReleaseStyle(style);
        }
        return TRUE;
    }
    return FALSE;
}