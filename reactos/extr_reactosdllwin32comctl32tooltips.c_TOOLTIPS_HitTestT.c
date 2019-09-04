#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cbSize; } ;
struct TYPE_4__ {TYPE_3__ ti; int /*<<< orphan*/  pt; int /*<<< orphan*/  hwnd; } ;
typedef  int /*<<< orphan*/  TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__* LPTTHITTESTINFOW ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TOOLTIPS_CopyInfoT (int /*<<< orphan*/  const*,int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int TOOLTIPS_GetToolFromPoint (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ TTTOOLINFOW_V1_SIZE ; 

__attribute__((used)) static LRESULT
TOOLTIPS_HitTestT (const TOOLTIPS_INFO *infoPtr, LPTTHITTESTINFOW lptthit,
                   BOOL isW)
{
    INT nTool;

    if (lptthit == 0)
	return FALSE;

    nTool = TOOLTIPS_GetToolFromPoint (infoPtr, lptthit->hwnd, &lptthit->pt);
    if (nTool == -1)
	return FALSE;

    TRACE("tool %d\n", nTool);

    /* copy tool data */
    if (lptthit->ti.cbSize >= TTTOOLINFOW_V1_SIZE)
        TOOLTIPS_CopyInfoT (infoPtr, nTool, &lptthit->ti, isW);

    return TRUE;
}