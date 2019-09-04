#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ uNumTools; } ;
struct TYPE_9__ {scalar_t__ cbSize; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ TTTOOLINFOW ;
typedef  TYPE_2__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TOOLTIPS_CopyInfoT (TYPE_2__ const*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int TOOLTIPS_GetToolFromInfoT (TYPE_2__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ TTTOOLINFOW_V1_SIZE ; 

__attribute__((used)) static LRESULT
TOOLTIPS_GetToolInfoT (const TOOLTIPS_INFO *infoPtr, TTTOOLINFOW *ti, BOOL isW)
{
    INT nTool;
    HWND hwnd;

    if (!ti) return FALSE;
    if (ti->cbSize < TTTOOLINFOW_V1_SIZE)
	return FALSE;
    if (infoPtr->uNumTools == 0)
	return FALSE;

    nTool = TOOLTIPS_GetToolFromInfoT (infoPtr, ti);
    if (nTool == -1)
	return FALSE;

    TRACE("tool %d\n", nTool);

    hwnd = ti->hwnd;
    TOOLTIPS_CopyInfoT (infoPtr, nTool, ti, isW);
    ti->hwnd = hwnd;

    return TRUE;
}