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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_13__ {int nCurrentTool; scalar_t__* szTipText; TYPE_1__* tools; } ;
struct TYPE_12__ {scalar_t__ cbSize; int /*<<< orphan*/  lParam; int /*<<< orphan*/ * lpszText; int /*<<< orphan*/  hinst; int /*<<< orphan*/  rect; int /*<<< orphan*/  uId; int /*<<< orphan*/  hwnd; int /*<<< orphan*/  uFlags; } ;
struct TYPE_11__ {int /*<<< orphan*/  lParam; int /*<<< orphan*/ * lpszText; int /*<<< orphan*/  hinst; int /*<<< orphan*/  rect; int /*<<< orphan*/  uId; int /*<<< orphan*/  hwnd; int /*<<< orphan*/  uFlags; } ;
typedef  TYPE_1__ TTTOOL_INFO ;
typedef  TYPE_2__ TTTOOLINFOW ;
typedef  TYPE_3__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 void* Alloc (int) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_INTRESOURCE (int /*<<< orphan*/ *) ; 
 int LOWORD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LPSTR_TEXTCALLBACKW ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TOOLTIPS_GetTipText (TYPE_3__*,int,scalar_t__*) ; 
 int TOOLTIPS_GetToolFromInfoT (TYPE_3__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  TOOLTIPS_Hide (TYPE_3__*) ; 
 scalar_t__ TOOLTIPS_IsCallbackString (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  TOOLTIPS_Show (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 scalar_t__ TTTOOLINFOW_V1_SIZE ; 
 scalar_t__ TTTOOLINFOW_V2_SIZE ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT
TOOLTIPS_SetToolInfoT (TOOLTIPS_INFO *infoPtr, const TTTOOLINFOW *ti, BOOL isW)
{
    TTTOOL_INFO *toolPtr;
    INT nTool;

    if (!ti) return 0;
    if (ti->cbSize < TTTOOLINFOW_V1_SIZE)
	return 0;

    nTool = TOOLTIPS_GetToolFromInfoT (infoPtr, ti);
    if (nTool == -1) return 0;

    TRACE("tool %d\n", nTool);

    toolPtr = &infoPtr->tools[nTool];

    /* copy tool data */
    toolPtr->uFlags = ti->uFlags;
    toolPtr->hwnd   = ti->hwnd;
    toolPtr->uId    = ti->uId;
    toolPtr->rect   = ti->rect;
    toolPtr->hinst  = ti->hinst;

    if (IS_INTRESOURCE(ti->lpszText)) {
	TRACE("set string id %x\n", LOWORD(ti->lpszText));
	toolPtr->lpszText = ti->lpszText;
    }
    else {
	if (TOOLTIPS_IsCallbackString(ti->lpszText, isW))
	    toolPtr->lpszText = LPSTR_TEXTCALLBACKW;
	else {
	    if ( (toolPtr->lpszText) &&
		 !IS_INTRESOURCE(toolPtr->lpszText) ) {
		if( toolPtr->lpszText != LPSTR_TEXTCALLBACKW)
                    Free (toolPtr->lpszText);
		toolPtr->lpszText = NULL;
	    }
	    if (ti->lpszText) {
		if (isW) {
		    INT len = lstrlenW (ti->lpszText);
		    toolPtr->lpszText = Alloc ((len+1)*sizeof(WCHAR));
		    strcpyW (toolPtr->lpszText, ti->lpszText);
		}
		else {
		    INT len = MultiByteToWideChar(CP_ACP, 0, (LPSTR)ti->lpszText,
					      -1, NULL, 0);
		    toolPtr->lpszText = Alloc (len * sizeof(WCHAR));
		    MultiByteToWideChar(CP_ACP, 0, (LPSTR)ti->lpszText, -1,
					toolPtr->lpszText, len);
		}
	    }
	}
    }

    if (ti->cbSize >= TTTOOLINFOW_V2_SIZE)
	toolPtr->lParam = ti->lParam;

    if (infoPtr->nCurrentTool == nTool)
    {
        TOOLTIPS_GetTipText (infoPtr, infoPtr->nCurrentTool, infoPtr->szTipText);

        if (infoPtr->szTipText[0] == 0)
            TOOLTIPS_Hide(infoPtr);
        else
            TOOLTIPS_Show (infoPtr, FALSE);
    }

    return 0;
}