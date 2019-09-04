#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dwStyle; void* nWidth; void* nHeight; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ PAGER_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  void* INT ;

/* Variables and functions */
 int /*<<< orphan*/  PAGER_RecalcSize (TYPE_1__*) ; 
 int PGS_HORZ ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void*,void*) ; 

__attribute__((used)) static LRESULT
PAGER_Size (PAGER_INFO* infoPtr, INT type, INT x, INT y)
{
    /* note that WM_SIZE is sent whenever NCCalcSize resizes the client wnd */

    TRACE("[%p] %d,%d\n", infoPtr->hwndSelf, x, y);

    if (infoPtr->dwStyle & PGS_HORZ)
        infoPtr->nHeight = y;
    else
        infoPtr->nWidth = x;

    return PAGER_RecalcSize(infoPtr);
}