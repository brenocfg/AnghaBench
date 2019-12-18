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
struct TYPE_7__ {int /*<<< orphan*/  wID; int /*<<< orphan*/  uBand; } ;
struct TYPE_6__ {int /*<<< orphan*/  DraggingBandId; int /*<<< orphan*/ * Dragging; } ;
typedef  TYPE_1__* PTOOLBAR_DOCKS ;
typedef  int /*<<< orphan*/ * PDOCKBAR_ITEM ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__* LPNMREBAR ;
typedef  int /*<<< orphan*/  DOCK_POSITION ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * TbnDockbarItemFromBandId (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
TbnRebarBeginDrag(PTOOLBAR_DOCKS TbDocks,
                  DOCK_POSITION Position,
                  LPNMREBAR lpnmrb)
{
    PDOCKBAR_ITEM Item;

    Item = TbnDockbarItemFromBandId(TbDocks,
                                    Position,
                                    lpnmrb->uBand);

    if (Item != NULL)
    {
        TbDocks->Dragging = Item;
        TbDocks->DraggingBandId = lpnmrb->wID;
        return FALSE;
    }

    return TRUE;
}