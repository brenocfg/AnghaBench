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
typedef  int* LPWSTR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int*) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  ERROR_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  ExpandEnvironmentStringsW (char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _wcsupr (int*) ; 
 int /*<<< orphan*/  wcscat (int*,int*) ; 
 scalar_t__ wcslen (int*) ; 

BOOL
AppendSystemPostfix(LPWSTR lpName,
                    DWORD dwMaxLength)
{
    WCHAR szSystemRoot[MAX_PATH];
    LPWSTR lpszPostfix;
    LPWSTR lpszPtr;

    /* Build profile name postfix */
    if (!ExpandEnvironmentStringsW(L"%SystemRoot%",
                                   szSystemRoot,
                                   ARRAYSIZE(szSystemRoot)))
    {
        DPRINT1("Error: %lu\n", GetLastError());
        return FALSE;
    }

    _wcsupr(szSystemRoot);

    /* Get name postfix */
    szSystemRoot[2] = L'.';
    lpszPostfix = &szSystemRoot[2];
    lpszPtr = lpszPostfix;
    while (*lpszPtr != (WCHAR)0)
    {
        if (*lpszPtr == L'\\')
            *lpszPtr = L'_';
        lpszPtr++;
    }

    if (wcslen(lpName) + wcslen(lpszPostfix) + 1 >= dwMaxLength)
    {
        DPRINT1("Error: buffer overflow\n");
        SetLastError(ERROR_BUFFER_OVERFLOW);
        return FALSE;
    }

    wcscat(lpName, lpszPostfix);

    return TRUE;
}