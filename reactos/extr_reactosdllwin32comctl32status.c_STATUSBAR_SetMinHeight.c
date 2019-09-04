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
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  minHeight; } ;
typedef  TYPE_1__ STATUS_INFO ;
typedef  int /*<<< orphan*/  INT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CYSIZE ; 
 int /*<<< orphan*/  STATUSBAR_ComputeHeight (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL
STATUSBAR_SetMinHeight (STATUS_INFO *infoPtr, INT height)
{
    DWORD ysize = GetSystemMetrics(SM_CYSIZE);
    if (ysize & 1) ysize--;
    infoPtr->minHeight = max(height, ysize);
    infoPtr->height = STATUSBAR_ComputeHeight(infoPtr);
    /* like native, don't resize the control */
    return TRUE;
}