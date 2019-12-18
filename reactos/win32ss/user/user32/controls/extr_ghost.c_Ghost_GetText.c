#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int InternalGetWindowText (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static LPWSTR
Ghost_GetText(HWND hwndTarget, INT *pcchTextW, INT cchExtra)
{
    LPWSTR pszTextW = NULL, pszTextNewW;
    INT cchNonExtra, cchTextW = *pcchTextW;

    pszTextNewW = HeapAlloc(GetProcessHeap(), 0, cchTextW * sizeof(WCHAR));
    for (;;)
    {
        if (!pszTextNewW)
        {
            ERR("HeapAlloc failed\n");
            if (pszTextW)
                HeapFree(GetProcessHeap(), 0, pszTextW);
            return NULL;
        }
        pszTextW = pszTextNewW;

        cchNonExtra = cchTextW - cchExtra;
        if (InternalGetWindowText(hwndTarget, pszTextW,
                                  cchNonExtra) < cchNonExtra - 1)
        {
            break;
        }

        cchTextW *= 2;
        pszTextNewW = HeapReAlloc(GetProcessHeap(), 0, pszTextW,
                                  cchTextW * sizeof(WCHAR));
    }

    *pcchTextW = cchTextW;
    return pszTextW;
}