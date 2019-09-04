#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_22__ {int fsStyle; int iString; int /*<<< orphan*/  dwData; int /*<<< orphan*/  fsState; int /*<<< orphan*/  idCommand; int /*<<< orphan*/  iBitmap; } ;
struct TYPE_21__ {int fsStyle; int /*<<< orphan*/  dwData; int /*<<< orphan*/  fsState; int /*<<< orphan*/  idCommand; int /*<<< orphan*/  iBitmap; } ;
struct TYPE_20__ {int nNumButtons; scalar_t__ nNumStrings; int /*<<< orphan*/  hwndSelf; TYPE_2__* buttons; } ;
typedef  TYPE_1__ TOOLBAR_INFO ;
typedef  TYPE_2__ TBUTTON_INFO ;
typedef  TYPE_3__ TBBUTTON ;
typedef  int INT_PTR ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BTNS_SEP ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* ReAlloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  TOOLBAR_AutoSize (TYPE_1__*) ; 
 scalar_t__ TOOLBAR_ButtonHasString (TYPE_2__*) ; 
 int /*<<< orphan*/  TOOLBAR_CalcToolbar (TYPE_1__*) ; 
 int /*<<< orphan*/  TOOLBAR_DumpTBButton (TYPE_3__ const*,scalar_t__) ; 
 int /*<<< orphan*/  TOOLBAR_DumpToolbar (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TOOLBAR_LayoutToolbar (TYPE_1__*) ; 
 int /*<<< orphan*/  TOOLBAR_TooltipAddTool (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memmove (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  set_string_index (TYPE_2__*,int,scalar_t__) ; 

__attribute__((used)) static BOOL
TOOLBAR_InternalInsertButtonsT(TOOLBAR_INFO *infoPtr, INT iIndex, UINT nAddButtons, const TBBUTTON *lpTbb, BOOL fUnicode)
{
    INT nOldButtons, nNewButtons, iButton;
    BOOL fHasString = FALSE;

    if (iIndex < 0)  /* iIndex can be negative, what means adding at the end */
        iIndex = infoPtr->nNumButtons;

    nOldButtons = infoPtr->nNumButtons;
    nNewButtons = nOldButtons + nAddButtons;

    infoPtr->buttons = ReAlloc(infoPtr->buttons, sizeof(TBUTTON_INFO)*nNewButtons);
    memmove(&infoPtr->buttons[iIndex + nAddButtons], &infoPtr->buttons[iIndex],
            (nOldButtons - iIndex) * sizeof(TBUTTON_INFO));
    infoPtr->nNumButtons += nAddButtons;

    /* insert new buttons data */
    for (iButton = 0; iButton < nAddButtons; iButton++) {
        TBUTTON_INFO *btnPtr = &infoPtr->buttons[iIndex + iButton];
        INT_PTR str;

        TOOLBAR_DumpTBButton(lpTbb + iButton, fUnicode);

        ZeroMemory(btnPtr, sizeof(*btnPtr));

        btnPtr->iBitmap   = lpTbb[iButton].iBitmap;
        btnPtr->idCommand = lpTbb[iButton].idCommand;
        btnPtr->fsState   = lpTbb[iButton].fsState;
        btnPtr->fsStyle   = lpTbb[iButton].fsStyle;
        btnPtr->dwData    = lpTbb[iButton].dwData;

        if (btnPtr->fsStyle & BTNS_SEP)
            str = -1;
        else
            str = lpTbb[iButton].iString;
        set_string_index( btnPtr, str, fUnicode );
        fHasString |= TOOLBAR_ButtonHasString( btnPtr );

        TOOLBAR_TooltipAddTool(infoPtr, btnPtr);
    }

    if (infoPtr->nNumStrings > 0 || fHasString)
        TOOLBAR_CalcToolbar(infoPtr);
    else
        TOOLBAR_LayoutToolbar(infoPtr);
    TOOLBAR_AutoSize(infoPtr);

    TOOLBAR_DumpToolbar(infoPtr, __LINE__);
    InvalidateRect(infoPtr->hwndSelf, NULL, TRUE);
    return TRUE;
}