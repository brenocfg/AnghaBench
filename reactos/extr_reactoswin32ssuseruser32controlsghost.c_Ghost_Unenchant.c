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
struct TYPE_3__ {int /*<<< orphan*/  bDestroyTarget; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ GHOST_DATA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 TYPE_1__* Ghost_GetData (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
Ghost_Unenchant(HWND hwnd, BOOL bDestroyTarget)
{
    GHOST_DATA *pData = Ghost_GetData(hwnd);
    if (!pData)
        return;

    pData->bDestroyTarget |= bDestroyTarget;
    DestroyWindow(hwnd);
}