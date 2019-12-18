#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {size_t Position; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* CreateClient ) (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_15__ {size_t PrevDock; struct TYPE_15__* Next; int /*<<< orphan*/  hWndClient; TYPE_4__ DockBar; TYPE_3__ const* Callbacks; int /*<<< orphan*/ * hWndTool; int /*<<< orphan*/  Context; } ;
struct TYPE_14__ {TYPE_2__* Items; int /*<<< orphan*/ ** hRebar; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PTOOLBAR_DOCKS ;
typedef  TYPE_2__* PDOCKBAR_ITEM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  TYPE_3__ DOCKBAR_ITEM_CALLBACKS ;
typedef  int /*<<< orphan*/  DOCKBAR_ITEM ;
typedef  TYPE_4__ DOCKBAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ProcessHeap ; 
 int /*<<< orphan*/  TdbInsertToolbar (TYPE_1__*,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL
TbdAddToolbar(PTOOLBAR_DOCKS TbDocks,
              const DOCKBAR *Dockbar,
              PVOID Context,
              const DOCKBAR_ITEM_CALLBACKS *Callbacks)
{
    PDOCKBAR_ITEM Item;
    HWND hRebar;

    hRebar = TbDocks->hRebar[Dockbar->Position];
    if (hRebar != NULL)
    {
        Item = HeapAlloc(ProcessHeap,
                         0,
                         sizeof(DOCKBAR_ITEM));
        if (Item != NULL)
        {
            /* Initialize the item */
            Item->DockBar = *Dockbar;
            Item->Context = Context;
            Item->hWndTool = NULL;
            Item->PrevDock = Dockbar->Position;

            Item->Callbacks = Callbacks;

            /* Create the client control */
            if (Callbacks->CreateClient != NULL &&
                !Callbacks->CreateClient(TbDocks,
                                         &Item->DockBar,
                                         Context,
                                         hRebar,
                                         &Item->hWndClient))
            {
                HeapFree(ProcessHeap,
                         0,
                         Item);

                return FALSE;
            }

            /* Insert the item into the list */
            Item->Next = TbDocks->Items;
            TbDocks->Items = Item;

            return TdbInsertToolbar(TbDocks,
                                    Item,
                                    Dockbar->Position);
        }
    }

    return FALSE;
}