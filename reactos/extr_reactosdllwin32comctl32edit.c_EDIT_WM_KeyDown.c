#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_22__ {int style; int /*<<< orphan*/  hwndParent; int /*<<< orphan*/  selection_end; int /*<<< orphan*/  selection_start; } ;
typedef  int LRESULT ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DC_HASDEFID ; 
 int /*<<< orphan*/  DM_GETDEFID ; 
 int /*<<< orphan*/  EDIT_CheckCombo (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EDIT_EM_SetSel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EDIT_IsInsideDialog (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_MoveBackward (TYPE_1__*,int) ; 
 int /*<<< orphan*/  EDIT_MoveDown_ML (TYPE_1__*,int) ; 
 int /*<<< orphan*/  EDIT_MoveEnd (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  EDIT_MoveForward (TYPE_1__*,int) ; 
 int /*<<< orphan*/  EDIT_MoveHome (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  EDIT_MovePageDown_ML (TYPE_1__*,int) ; 
 int /*<<< orphan*/  EDIT_MovePageUp_ML (TYPE_1__*,int) ; 
 int /*<<< orphan*/  EDIT_MoveUp_ML (TYPE_1__*,int) ; 
 int /*<<< orphan*/  EDIT_MoveWordBackward (TYPE_1__*,int) ; 
 int /*<<< orphan*/  EDIT_MoveWordForward (TYPE_1__*,int) ; 
 int /*<<< orphan*/  EDIT_NOTIFY_PARENT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_WM_Clear (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_WM_Copy (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_WM_Cut (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_WM_Paste (TYPE_1__*) ; 
 int /*<<< orphan*/  EN_CHANGE ; 
 int /*<<< orphan*/  EN_UPDATE ; 
 int ES_MULTILINE ; 
 int ES_READONLY ; 
 int ES_WANTRETURN ; 
 int FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetKeyState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  VK_CONTROL ; 
#define  VK_DELETE 141 
#define  VK_DOWN 140 
#define  VK_END 139 
#define  VK_ESCAPE 138 
#define  VK_F4 137 
#define  VK_HOME 136 
#define  VK_INSERT 135 
#define  VK_LEFT 134 
 int /*<<< orphan*/  VK_MENU ; 
#define  VK_NEXT 133 
#define  VK_PRIOR 132 
#define  VK_RETURN 131 
#define  VK_RIGHT 130 
 int /*<<< orphan*/  VK_SHIFT ; 
#define  VK_TAB 129 
#define  VK_UP 128 
 int /*<<< orphan*/  WM_CLOSE ; 
 int /*<<< orphan*/  WM_KEYDOWN ; 
 int /*<<< orphan*/  WM_NEXTDLGCTL ; 
 int /*<<< orphan*/  get_text_length (TYPE_1__*) ; 

__attribute__((used)) static LRESULT EDIT_WM_KeyDown(EDITSTATE *es, INT key)
{
	BOOL shift;
	BOOL control;

	if (GetKeyState(VK_MENU) & 0x8000)
		return 0;

	shift = GetKeyState(VK_SHIFT) & 0x8000;
	control = GetKeyState(VK_CONTROL) & 0x8000;

	switch (key) {
	case VK_F4:
	case VK_UP:
		if (EDIT_CheckCombo(es, WM_KEYDOWN, key) || key == VK_F4)
			break;

		/* fall through */
	case VK_LEFT:
		if ((es->style & ES_MULTILINE) && (key == VK_UP))
			EDIT_MoveUp_ML(es, shift);
		else
			if (control)
				EDIT_MoveWordBackward(es, shift);
			else
				EDIT_MoveBackward(es, shift);
		break;
	case VK_DOWN:
		if (EDIT_CheckCombo(es, WM_KEYDOWN, key))
			break;
		/* fall through */
	case VK_RIGHT:
		if ((es->style & ES_MULTILINE) && (key == VK_DOWN))
			EDIT_MoveDown_ML(es, shift);
		else if (control)
			EDIT_MoveWordForward(es, shift);
		else
			EDIT_MoveForward(es, shift);
		break;
	case VK_HOME:
		EDIT_MoveHome(es, shift, control);
		break;
	case VK_END:
		EDIT_MoveEnd(es, shift, control);
		break;
	case VK_PRIOR:
		if (es->style & ES_MULTILINE)
			EDIT_MovePageUp_ML(es, shift);
		else
			EDIT_CheckCombo(es, WM_KEYDOWN, key);
		break;
	case VK_NEXT:
		if (es->style & ES_MULTILINE)
			EDIT_MovePageDown_ML(es, shift);
		else
			EDIT_CheckCombo(es, WM_KEYDOWN, key);
		break;
	case VK_DELETE:
		if (!(es->style & ES_READONLY) && !(shift && control)) {
			if (es->selection_start != es->selection_end) {
				if (shift)
					EDIT_WM_Cut(es);
				else
					EDIT_WM_Clear(es);
			} else {
				if (shift) {
					/* delete character left of caret */
					EDIT_EM_SetSel(es, (UINT)-1, 0, FALSE);
					EDIT_MoveBackward(es, TRUE);
					EDIT_WM_Clear(es);
				} else if (control) {
					/* delete to end of line */
					EDIT_EM_SetSel(es, (UINT)-1, 0, FALSE);
					EDIT_MoveEnd(es, TRUE, FALSE);
					EDIT_WM_Clear(es);
				} else {
					/* delete character right of caret */
					EDIT_EM_SetSel(es, (UINT)-1, 0, FALSE);
					EDIT_MoveForward(es, TRUE);
					EDIT_WM_Clear(es);
				}
			}
		}
		break;
	case VK_INSERT:
		if (shift) {
			if (!(es->style & ES_READONLY))
				EDIT_WM_Paste(es);
		} else if (control)
			EDIT_WM_Copy(es);
		break;
	case VK_RETURN:
	    /* If the edit doesn't want the return send a message to the default object */
	    if(!(es->style & ES_MULTILINE) || !(es->style & ES_WANTRETURN))
	    {
                DWORD dw;

                if (!EDIT_IsInsideDialog(es)) break;
                if (control) break;
                dw = SendMessageW(es->hwndParent, DM_GETDEFID, 0, 0);
                if (HIWORD(dw) == DC_HASDEFID)
                {
                    HWND hwDefCtrl = GetDlgItem(es->hwndParent, LOWORD(dw));
                    if (hwDefCtrl)
                    {
                        SendMessageW(es->hwndParent, WM_NEXTDLGCTL, (WPARAM)hwDefCtrl, TRUE);
                        PostMessageW(hwDefCtrl, WM_KEYDOWN, VK_RETURN, 0);
                    }
                }
	    }
	    break;
        case VK_ESCAPE:
            if ((es->style & ES_MULTILINE) && EDIT_IsInsideDialog(es))
                PostMessageW(es->hwndParent, WM_CLOSE, 0, 0);
            break;
        case VK_TAB:
            if ((es->style & ES_MULTILINE) && EDIT_IsInsideDialog(es))
                SendMessageW(es->hwndParent, WM_NEXTDLGCTL, shift, 0);
            break;
        case 'A':
            if (control)
            {
                if (EDIT_EM_SetSel(es, 0, get_text_length(es), FALSE))
                {
                    EDIT_NOTIFY_PARENT(es, EN_UPDATE);
                    EDIT_NOTIFY_PARENT(es, EN_CHANGE);
                }
            }
            break;
	}
        return TRUE;
}