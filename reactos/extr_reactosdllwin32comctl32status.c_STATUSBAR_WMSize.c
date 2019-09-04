#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_7__ {scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_6__ {scalar_t__ height; int /*<<< orphan*/  Self; int /*<<< orphan*/  Notify; } ;
typedef  TYPE_1__ STATUS_INFO ;
typedef  TYPE_2__ RECT ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CCS_NORESIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MoveWindow (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SIZE_MAXIMIZED ; 
 scalar_t__ SIZE_RESTORED ; 
 int /*<<< orphan*/  STATUSBAR_SetPartBounds (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static BOOL
STATUSBAR_WMSize (STATUS_INFO *infoPtr, WORD flags)
{
    INT  width, x, y;
    RECT parent_rect;

    /* Need to resize width to match parent */
    TRACE("flags %04x\n", flags);

    if (flags != SIZE_RESTORED && flags != SIZE_MAXIMIZED) {
	WARN("flags MUST be SIZE_RESTORED or SIZE_MAXIMIZED\n");
	return FALSE;
    }

    if (GetWindowLongW(infoPtr->Self, GWL_STYLE) & CCS_NORESIZE) return FALSE;

    /* width and height don't apply */
    if (!GetClientRect (infoPtr->Notify, &parent_rect))
        return FALSE;

    width = parent_rect.right - parent_rect.left;
    x = parent_rect.left;
    y = parent_rect.bottom - infoPtr->height;
    MoveWindow (infoPtr->Self, x, y, width, infoPtr->height, TRUE);
    STATUSBAR_SetPartBounds (infoPtr);
    return TRUE;
}