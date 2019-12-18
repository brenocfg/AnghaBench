#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int /*<<< orphan*/  x; int /*<<< orphan*/  y; } ;
struct TYPE_8__ {int /*<<< orphan*/ * hRebar; } ;
struct TYPE_7__ {int top; int bottom; int left; int right; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__* PTOOLBAR_DOCKS ;
typedef  TYPE_3__ POINT ;
typedef  size_t DOCK_POSITION ;

/* Variables and functions */
#define  BOTTOM_DOCK 131 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
#define  LEFT_DOCK 130 
#define  RIGHT_DOCK 129 
#define  TOP_DOCK 128 

__attribute__((used)) static UINT
TbdCalculateInsertIndex(PTOOLBAR_DOCKS TbDocks,
                        DOCK_POSITION Position,
                        POINT pt)
{
    RECT rcRebar;
    UINT Ret = 0;

    GetWindowRect(TbDocks->hRebar[Position],
                  &rcRebar);

    switch (Position)
    {
        case TOP_DOCK:
        case BOTTOM_DOCK:
            if (pt.y > rcRebar.top + ((rcRebar.bottom - rcRebar.top) / 2))
                Ret = (UINT)-1;
            break;

        case LEFT_DOCK:
        case RIGHT_DOCK:
            if (pt.x > rcRebar.left + ((rcRebar.right - rcRebar.left) / 2))
                Ret = (UINT)-1;
            break;

        default:
            break;
    }

    return Ret;
}