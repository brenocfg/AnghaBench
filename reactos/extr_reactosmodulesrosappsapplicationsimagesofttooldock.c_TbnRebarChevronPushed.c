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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_9__ {int /*<<< orphan*/  uBand; } ;
struct TYPE_8__ {int /*<<< orphan*/  hWndClient; int /*<<< orphan*/  Context; int /*<<< orphan*/  DockBar; TYPE_1__* Callbacks; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* ChevronPushed ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ;} ;
typedef  int /*<<< orphan*/  PTOOLBAR_DOCKS ;
typedef  TYPE_2__* PDOCKBAR_ITEM ;
typedef  TYPE_3__* LPNMREBARCHEVRON ;
typedef  int /*<<< orphan*/  DOCK_POSITION ;

/* Variables and functions */
 TYPE_2__* TbnDockbarItemFromBandId (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static VOID
TbnRebarChevronPushed(PTOOLBAR_DOCKS TbDocks,
                      DOCK_POSITION Position,
                      LPNMREBARCHEVRON lpnm)
{
    PDOCKBAR_ITEM Item;

    Item = TbnDockbarItemFromBandId(TbDocks,
                                    Position,
                                    lpnm->uBand);

    if (Item != NULL && Item->Callbacks->ChevronPushed)
    {
        Item->Callbacks->ChevronPushed(TbDocks,
                                       &Item->DockBar,
                                       Item->Context,
                                       Item->hWndClient,
                                       lpnm);
    }
}