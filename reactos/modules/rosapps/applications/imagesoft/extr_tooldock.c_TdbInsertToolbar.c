#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rbi ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int UINT ;
struct TYPE_23__ {scalar_t__ DisplayTextId; int Position; int /*<<< orphan*/  BarId; } ;
struct TYPE_22__ {size_t PrevDock; int PrevBandIndex; TYPE_7__ DockBar; int /*<<< orphan*/ * hWndClient; int /*<<< orphan*/  Context; TYPE_1__* Callbacks; } ;
struct TYPE_21__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_20__ {int /*<<< orphan*/ * hRebar; } ;
struct TYPE_19__ {int cbSize; int fMask; int /*<<< orphan*/ * hwndChild; int /*<<< orphan*/ * lpText; scalar_t__ lParam; int /*<<< orphan*/  fStyle; int /*<<< orphan*/  wID; int /*<<< orphan*/  member_0; } ;
struct TYPE_18__ {int (* InsertBand ) (TYPE_3__*,TYPE_7__*,int /*<<< orphan*/ ,int*,TYPE_2__*) ;int /*<<< orphan*/  (* DockBand ) (TYPE_3__*,TYPE_7__*,int /*<<< orphan*/ ,int const,int,TYPE_2__*) ;} ;
typedef  TYPE_2__ REBARBANDINFO ;
typedef  TYPE_3__* PTOOLBAR_DOCKS ;
typedef  TYPE_4__ POINT ;
typedef  TYPE_5__* PDOCKBAR_ITEM ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HLOCAL ;
typedef  size_t DOCK_POSITION ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ AllocAndLoadString (int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__) ; 
 int FALSE ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
#define  NO_DOCK 128 
 int RBBIM_CHILD ; 
 int RBBIM_ID ; 
 int RBBIM_LPARAM ; 
 int RBBIM_STYLE ; 
 int RBBIM_TEXT ; 
 int /*<<< orphan*/  RBBS_GRIPPERALWAYS ; 
 int /*<<< orphan*/  RB_IDTOINDEX ; 
 int /*<<< orphan*/  RB_INSERTBAND ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int TRUE ; 
 int TbdCreateToolbarWnd (TYPE_3__*,TYPE_5__*,int,int,TYPE_2__*,TYPE_4__,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  hInstance ; 
 int stub1 (TYPE_3__*,TYPE_7__*,int /*<<< orphan*/ ,int*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,TYPE_7__*,int /*<<< orphan*/ ,int const,int,TYPE_2__*) ; 

__attribute__((used)) static BOOL
TdbInsertToolbar(PTOOLBAR_DOCKS TbDocks,
                 PDOCKBAR_ITEM Item,
                 DOCK_POSITION Position)
{
    LPTSTR lpCaption = NULL;
    REBARBANDINFO rbi = {0};
    BOOL Ret = FALSE;

    rbi.cbSize = sizeof(rbi);
    rbi.fMask = RBBIM_ID | RBBIM_STYLE | RBBIM_LPARAM;
    rbi.wID = Item->DockBar.BarId;
    rbi.fStyle = RBBS_GRIPPERALWAYS;
    rbi.lParam = (LPARAM)Item;

    if (Item->DockBar.DisplayTextId != 0)
    {
        if (AllocAndLoadString(&lpCaption,
                               hInstance,
                               Item->DockBar.DisplayTextId))
        {
            rbi.fMask |= RBBIM_TEXT;
            rbi.lpText = lpCaption;
        }
    }

    if (Item->hWndClient != NULL)
    {
        rbi.fMask |= RBBIM_CHILD;
        rbi.hwndChild = Item->hWndClient;
    }

    switch (Item->DockBar.Position)
    {
        case NO_DOCK:
        {
            POINT pt = {0};

            /* FIXME - calculate size */
            Ret = TbdCreateToolbarWnd(TbDocks,
                                      Item,
                                      Item->DockBar.Position,
                                      (UINT)-1,
                                      &rbi,
                                      pt,
                                      NULL,
                                      (UINT)-1,
                                      FALSE);
            break;
        }

        default:
        {
            UINT Index = -1;
            BOOL AddBand = TRUE;

            if (Item->Callbacks->InsertBand != NULL)
            {
                AddBand = Item->Callbacks->InsertBand(TbDocks,
                                                      &Item->DockBar,
                                                      Item->Context,
                                                      &Index,
                                                      &rbi);
            }

            if (AddBand)
            {
                Item->Callbacks->DockBand(TbDocks,
                                          &Item->DockBar,
                                          Item->Context,
                                          NO_DOCK,
                                          Item->DockBar.Position,
                                          &rbi);

                if (rbi.fMask & RBBIM_CHILD)
                    Item->hWndClient = rbi.hwndChild;
                else
                    Item->hWndClient = NULL;

                Ret = SendMessage(TbDocks->hRebar[Position],
                                  RB_INSERTBAND,
                                  (WPARAM)Index,
                                  (LPARAM)&rbi) != 0;
                if (Ret)
                {
                    Item->PrevDock = Position;
                    Item->PrevBandIndex = (UINT)SendMessage(TbDocks->hRebar[Position],
                                                            RB_IDTOINDEX,
                                                            (WPARAM)Item->DockBar.BarId,
                                                            0);
                }
            }

            break;
        }
    }

    if (lpCaption != NULL)
    {
        LocalFree((HLOCAL)lpCaption);
    }

    return Ret;
}