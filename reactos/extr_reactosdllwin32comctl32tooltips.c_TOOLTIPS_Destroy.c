#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_8__ {size_t uNumTools; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  hTitleFont; int /*<<< orphan*/  hFont; int /*<<< orphan*/  hTitleIcon; struct TYPE_8__* pszTitle; struct TYPE_8__* tools; struct TYPE_8__* lpszText; } ;
typedef  TYPE_1__ TTTOOL_INFO ;
typedef  TYPE_1__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_INTRESOURCE (TYPE_1__*) ; 
 TYPE_1__* LPSTR_TEXTCALLBACKW ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TOOLTIPS_GetTitleIconIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOOLTIPS_ResetSubclass (TYPE_1__*) ; 
 scalar_t__ TTI_ERROR ; 

__attribute__((used)) static LRESULT
TOOLTIPS_Destroy (TOOLTIPS_INFO *infoPtr)
{
    TTTOOL_INFO *toolPtr;
    UINT i;

    /* free tools */
    if (infoPtr->tools) {
	for (i = 0; i < infoPtr->uNumTools; i++) {
	    toolPtr = &infoPtr->tools[i];
	    if (toolPtr->lpszText) {
		if ( (toolPtr->lpszText != LPSTR_TEXTCALLBACKW) &&
		     !IS_INTRESOURCE(toolPtr->lpszText) )
		{
		    Free (toolPtr->lpszText);
		    toolPtr->lpszText = NULL;
		}
	    }

            TOOLTIPS_ResetSubclass (toolPtr);
        }

	Free (infoPtr->tools);
    }

    /* free title string */
    Free (infoPtr->pszTitle);
    /* free title icon if not a standard one */
    if (TOOLTIPS_GetTitleIconIndex(infoPtr->hTitleIcon) > TTI_ERROR)
        DeleteObject(infoPtr->hTitleIcon);

    /* delete fonts */
    DeleteObject (infoPtr->hFont);
    DeleteObject (infoPtr->hTitleFont);

    /* free tool tips info data */
    SetWindowLongPtrW(infoPtr->hwndSelf, 0, 0);
    Free (infoPtr);

    return 0;
}