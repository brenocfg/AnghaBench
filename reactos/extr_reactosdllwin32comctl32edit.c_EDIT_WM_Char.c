#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {int style; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  selection_end; int /*<<< orphan*/  selection_start; } ;
typedef  int LRESULT ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_EM_ReplaceSel (TYPE_1__*,int /*<<< orphan*/ ,int const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_EM_SetSel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_IsInsideDialog (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_MoveBackward (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_MoveDown_ML (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_MoveHome (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_WM_Clear (TYPE_1__*) ; 
 int ES_MULTILINE ; 
 int ES_NUMBER ; 
 int ES_PASSWORD ; 
 int ES_READONLY ; 
 int ES_WANTRETURN ; 
 int /*<<< orphan*/  FALSE ; 
 int GetKeyState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
#define  VK_BACK 128 
 int /*<<< orphan*/  VK_CONTROL ; 
 int /*<<< orphan*/  WM_COPY ; 
 int /*<<< orphan*/  WM_CUT ; 
 int /*<<< orphan*/  WM_PASTE ; 
 int /*<<< orphan*/  WM_UNDO ; 

__attribute__((used)) static LRESULT EDIT_WM_Char(EDITSTATE *es, WCHAR c)
{
        BOOL control;

	control = GetKeyState(VK_CONTROL) & 0x8000;

	switch (c) {
	case '\r':
            /* If it's not a multiline edit box, it would be ignored below.
             * For multiline edit without ES_WANTRETURN, we have to make a
             * special case.
             */
            if ((es->style & ES_MULTILINE) && !(es->style & ES_WANTRETURN))
                if (EDIT_IsInsideDialog(es))
                    break;
	case '\n':
		if (es->style & ES_MULTILINE) {
			if (es->style & ES_READONLY) {
				EDIT_MoveHome(es, FALSE, FALSE);
				EDIT_MoveDown_ML(es, FALSE);
			} else {
				static const WCHAR cr_lfW[] = {'\r','\n'};
				EDIT_EM_ReplaceSel(es, TRUE, cr_lfW, 2, TRUE, TRUE);
			}
		}
		break;
	case '\t':
		if ((es->style & ES_MULTILINE) && !(es->style & ES_READONLY))
		{
			static const WCHAR tabW[] = {'\t'};
                        if (EDIT_IsInsideDialog(es))
                            break;
			EDIT_EM_ReplaceSel(es, TRUE, tabW, 1, TRUE, TRUE);
		}
		break;
	case VK_BACK:
		if (!(es->style & ES_READONLY) && !control) {
			if (es->selection_start != es->selection_end)
				EDIT_WM_Clear(es);
			else {
				/* delete character left of caret */
				EDIT_EM_SetSel(es, (UINT)-1, 0, FALSE);
				EDIT_MoveBackward(es, TRUE);
				EDIT_WM_Clear(es);
			}
		}
		break;
	case 0x03: /* ^C */
		if (!(es->style & ES_PASSWORD))
		    SendMessageW(es->hwndSelf, WM_COPY, 0, 0);
		break;
	case 0x16: /* ^V */
	        if (!(es->style & ES_READONLY))
		    SendMessageW(es->hwndSelf, WM_PASTE, 0, 0);
		break;
	case 0x18: /* ^X */
	        if (!((es->style & ES_READONLY) || (es->style & ES_PASSWORD)))
		    SendMessageW(es->hwndSelf, WM_CUT, 0, 0);
		break;
	case 0x1A: /* ^Z */
	        if (!(es->style & ES_READONLY))
		    SendMessageW(es->hwndSelf, WM_UNDO, 0, 0);
		break;

	default:
		/*If Edit control style is ES_NUMBER allow users to key in only numeric values*/
		if( (es->style & ES_NUMBER) && !( c >= '0' && c <= '9') )
			break;

		if (!(es->style & ES_READONLY) && (c >= ' ') && (c != 127))
			EDIT_EM_ReplaceSel(es, TRUE, &c, 1, TRUE, TRUE);
		break;
	}
    return 1;
}