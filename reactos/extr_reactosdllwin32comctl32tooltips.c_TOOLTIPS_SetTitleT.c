#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT_PTR ;
typedef  int UINT ;
struct TYPE_3__ {int /*<<< orphan*/  hTitleIcon; int /*<<< orphan*/ * pszTitle; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  HICON ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 void* Alloc (int) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CopyIcon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TRUE ; 
 size_t TTI_ERROR ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__) ; 
 int /*<<< orphan*/ * hTooltipIcons ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int strlenW (scalar_t__) ; 

__attribute__((used)) static LRESULT
TOOLTIPS_SetTitleT (TOOLTIPS_INFO *infoPtr, UINT_PTR uTitleIcon, LPCWSTR pszTitle,
                    BOOL isW)
{
    UINT size;

    TRACE("hwnd = %p, title = %s, icon = %p\n", infoPtr->hwndSelf, debugstr_w(pszTitle),
        (void*)uTitleIcon);

    Free(infoPtr->pszTitle);

    if (pszTitle)
    {
        if (isW)
        {
            size = (strlenW(pszTitle)+1)*sizeof(WCHAR);
            infoPtr->pszTitle = Alloc(size);
            if (!infoPtr->pszTitle)
                return FALSE;
            memcpy(infoPtr->pszTitle, pszTitle, size);
        }
        else
        {
            size = sizeof(WCHAR)*MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszTitle, -1, NULL, 0);
            infoPtr->pszTitle = Alloc(size);
            if (!infoPtr->pszTitle)
                return FALSE;
            MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszTitle, -1, infoPtr->pszTitle, size/sizeof(WCHAR));
        }
    }
    else
        infoPtr->pszTitle = NULL;

    if (uTitleIcon <= TTI_ERROR)
        infoPtr->hTitleIcon = hTooltipIcons[uTitleIcon];
    else
        infoPtr->hTitleIcon = CopyIcon((HICON)uTitleIcon);

    TRACE("icon = %p\n", infoPtr->hTitleIcon);

    return TRUE;
}