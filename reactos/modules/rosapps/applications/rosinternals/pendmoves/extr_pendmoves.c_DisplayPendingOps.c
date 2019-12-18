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
typedef  scalar_t__ TCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__* BeautifyPath (scalar_t__*,int*) ; 
 scalar_t__ GetFileAttributes (scalar_t__*) ; 
 scalar_t__* GetLastError () ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 scalar_t__* _T (char*) ; 
 int /*<<< orphan*/  _ftprintf (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 scalar_t__ _tcslen (scalar_t__*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static
DWORD
DisplayPendingOps(TCHAR * Value, DWORD Len)
{
    DWORD Chars, i, j, Count, SrcLen, TgtLen;
    TCHAR * SrcFile, * Target, * Current;

    /* Compute the amount of chars
     * NULL char isn't relaible EOF (MULTI_SZ)
     */
    Chars = Len / sizeof(TCHAR);

    i = 0;
    Count = 0;
    Current = Value;
    /* Browse the whole string */
    while (i < Chars)
    {
        /* Jump to the next NULL (end of source) */
        for (j = i; j < Chars && Value[j] != 0; ++j);
        /* Get len & clean path */
        SrcLen = _tcslen(Current);
        SrcFile = BeautifyPath(Current, &SrcLen);
        /* Source file is null - likely the end of the MULTI_SZ, quit */
        if (SrcLen == 0)
        {
            break;
        }

        /* Remember position, jump to the begin of the target */
        i = j;
        ++i;
        /* Update position in MULTI_SZ */
        Current = Value + i;

        /* Jump to the next NULL (end of target) */
        for (j = i; j < Chars && Value[j] != 0; ++j);
        /* Get len & clean path */
        TgtLen = _tcslen(Current);
        Target = BeautifyPath(Current, &TgtLen);
        /* Remember position, jump to the begin of the next source */
        i = j;
        ++i;
        Current = Value + i;

        /* Display source */
        _ftprintf(stdout, _T("Source: %s\n"), SrcFile);
        /* If is accessible? Warn if not */
        if (GetFileAttributes(SrcFile) == INVALID_FILE_ATTRIBUTES)
        {
            _ftprintf(stdout, _T("\t *** Source file lookup error: %d\n"), GetLastError());
        }
        /* And display target - if empty, it's for deletion, mark as it */
        _ftprintf(stdout, _T("Target: %s\n\n"), (_tcslen(Target) != 0 ? Target: _T("DELETE")));

        /* Remember position and number of entries */
        Current = Value + i;
        ++Count;
    }

    return Count;
}