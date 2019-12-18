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
struct TYPE_3__ {scalar_t__ hFindFile; } ;
typedef  TYPE_1__* LPLFNDTA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 

BOOL
WFFindClose(LPLFNDTA lpFind)
{
    BOOL bRet;

//    ASSERT(lpFind->hFindFile != INVALID_HANDLE_VALUE);

// This section WAS #defined DBG, but removed
// Basically, when copying a directory into ITS subdirectory, we detect
// an error.  Since the error is detected late (after the file handle
// is closed), we jump to error code that pops up a message, then tries
// to close the same handle.  This cause the a bomb.  By un #define DBG ing
// this code, we allow multiple file closes.  This is sloppy, but works.

// A better solution is to put another flag in the error code "ret" in
// WFMoveCopyDriver right after it calls GetNextPair.

    if (lpFind->hFindFile == INVALID_HANDLE_VALUE) {
        return(FALSE);
    }

    bRet = FindClose(lpFind->hFindFile);

// This section WAS #defined DBG, but removed
    lpFind->hFindFile = INVALID_HANDLE_VALUE;

    return(bRet);
}