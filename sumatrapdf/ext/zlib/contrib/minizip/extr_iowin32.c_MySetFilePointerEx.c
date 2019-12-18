#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int LowPart; int /*<<< orphan*/  HighPart; } ;
typedef  int /*<<< orphan*/  LONG ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ NO_ERROR ; 
 int SetFilePointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ SetFilePointerEx (int /*<<< orphan*/ ,TYPE_1__,TYPE_1__*,int) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static BOOL MySetFilePointerEx(HANDLE hFile, LARGE_INTEGER pos, LARGE_INTEGER *newPos,  DWORD dwMoveMethod)
{
#ifdef IOWIN32_USING_WINRT_API
    return SetFilePointerEx(hFile, pos, newPos, dwMoveMethod);
#else
    LONG lHigh = pos.HighPart;
    DWORD dwNewPos = SetFilePointer(hFile, pos.LowPart, &lHigh, dwMoveMethod);
    BOOL fOk = TRUE;
    if (dwNewPos == 0xFFFFFFFF)
        if (GetLastError() != NO_ERROR)
            fOk = FALSE;
    if ((newPos != NULL) && (fOk))
    {
        newPos->LowPart = dwNewPos;
        newPos->HighPart = lHigh;
    }
    return fOk;
#endif
}