#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rbi ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/ * hRebar; } ;
struct TYPE_4__ {int cbSize; int /*<<< orphan*/  lParam; int /*<<< orphan*/  fMask; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ REBARBANDINFO ;
typedef  TYPE_2__* PTOOLBAR_DOCKS ;
typedef  int /*<<< orphan*/ * PDOCKBAR_ITEM ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  size_t DOCK_POSITION ;

/* Variables and functions */
 int /*<<< orphan*/  RBBIM_LPARAM ; 
 int /*<<< orphan*/  RB_GETBANDINFO ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PDOCKBAR_ITEM
TbnDockbarItemFromBandId(PTOOLBAR_DOCKS TbDocks,
                         DOCK_POSITION Position,
                         UINT uBand)
{
    REBARBANDINFO rbi = {0};

    rbi.cbSize = sizeof(rbi);
    rbi.fMask = RBBIM_LPARAM;

    if (SendMessage(TbDocks->hRebar[Position],
                    RB_GETBANDINFO,
                    (WPARAM)uBand,
                    (LPARAM)&rbi))
    {
        return (PDOCKBAR_ITEM)rbi.lParam;
    }

    return NULL;
}