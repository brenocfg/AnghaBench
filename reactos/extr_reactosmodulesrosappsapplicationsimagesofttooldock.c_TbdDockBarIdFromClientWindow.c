#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/  BarId; } ;
struct TYPE_7__ {scalar_t__ hWndClient; struct TYPE_7__* Next; TYPE_1__ DockBar; } ;
struct TYPE_6__ {TYPE_3__* Items; } ;
typedef  TYPE_2__* PTOOLBAR_DOCKS ;
typedef  TYPE_3__* PDOCKBAR_ITEM ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
TbdDockBarIdFromClientWindow(PTOOLBAR_DOCKS TbDocks,
                             HWND hWndClient,
                             UINT *Id)
{
    PDOCKBAR_ITEM Item;
    BOOL Ret = FALSE;

    Item = TbDocks->Items;
    while (Item != NULL)
    {
        if (Item->hWndClient == hWndClient)
        {
            *Id = Item->DockBar.BarId;
            Ret = TRUE;
            break;
        }

        Item = Item->Next;
    }

    return Ret;
}