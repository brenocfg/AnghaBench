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
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PCONSRV_CONSOLE ;
typedef  int* LPWSTR ;
typedef  int /*<<< orphan*/  HDROP ;

/* Variables and functions */
 scalar_t__ ARRAYSIZE (int*) ; 
 int /*<<< orphan*/  DragFinish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DragQueryFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  PasteText (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringCchCatW (int*,scalar_t__,char*) ; 
 int /*<<< orphan*/ * wcschr (int*,int) ; 
 int /*<<< orphan*/  wcslen (int*) ; 

__attribute__((used)) static VOID
OnDropFiles(PCONSRV_CONSOLE Console, HDROP hDrop)
{
    LPWSTR pszPath;
    WCHAR szPath[MAX_PATH + 2];

    szPath[0] = L'"';

    DragQueryFileW(hDrop, 0, &szPath[1], ARRAYSIZE(szPath) - 1);
    DragFinish(hDrop);

    if (wcschr(&szPath[1], L' ') != NULL)
    {
        StringCchCatW(szPath, ARRAYSIZE(szPath), L"\"");
        pszPath = szPath;
    }
    else
    {
        pszPath = &szPath[1];
    }

    PasteText(Console, pszPath, wcslen(pszPath));
}