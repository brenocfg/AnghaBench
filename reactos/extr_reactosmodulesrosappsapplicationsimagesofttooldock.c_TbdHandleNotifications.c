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
struct TYPE_10__ {scalar_t__ hwndFrom; int code; } ;
struct TYPE_9__ {scalar_t__* hRebar; } ;
typedef  TYPE_1__* PTOOLBAR_DOCKS ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPNMREBARCHEVRON ;
typedef  int /*<<< orphan*/  LPNMREBAR ;
typedef  TYPE_2__* LPNMHDR ;
typedef  size_t DOCK_POSITION ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t NO_DOCK ; 
#define  RBN_BEGINDRAG 131 
#define  RBN_CHEVRONPUSHED 130 
#define  RBN_ENDDRAG 129 
#define  RBN_HEIGHTCHANGE 128 
 size_t TOP_DOCK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TbnRebarBeginDrag (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TbnRebarChangeSize (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  TbnRebarChevronPushed (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TbnRebarEndDrag (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 

BOOL
TbdHandleNotifications(PTOOLBAR_DOCKS TbDocks,
                       LPNMHDR pnmh,
                       LRESULT *Result)
{
    BOOL Handled = FALSE;

    if (pnmh->hwndFrom != NULL)
    {
        DOCK_POSITION Position;

        for (Position = TOP_DOCK; Position < NO_DOCK; Position++)
        {
            if (pnmh->hwndFrom == TbDocks->hRebar[Position])
            {
                switch (pnmh->code)
                {
                    case RBN_HEIGHTCHANGE:
                    {
                        TbnRebarChangeSize(TbDocks,
                                           Position);
                        break;
                    }

                    case RBN_BEGINDRAG:
                    {
                        *Result = TbnRebarBeginDrag(TbDocks,
                                                    Position,
                                                    (LPNMREBAR)pnmh);
                        break;
                    }

                    case RBN_ENDDRAG:
                    {
                        TbnRebarEndDrag(TbDocks,
                                        Position,
                                        (LPNMREBAR)pnmh);
                        break;
                    }

                    case RBN_CHEVRONPUSHED:
                    {
                        TbnRebarChevronPushed(TbDocks,
                                              Position,
                                              (LPNMREBARCHEVRON)pnmh);
                        break;
                    }
                }

                Handled = TRUE;
                break;
            }
        }
    }

    return Handled;
}