#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_19__ {void* Bottom; void* Right; void* Top; void* Left; } ;
struct TYPE_17__ {int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
struct TYPE_18__ {int dwFlags; TYPE_4__ srSelection; TYPE_2__ dwSelectionAnchor; } ;
struct TYPE_21__ {int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
struct TYPE_16__ {TYPE_5__* Data; } ;
struct TYPE_22__ {TYPE_3__ Selection; TYPE_6__ dwSelectionCursor; TYPE_1__ TermIFace; } ;
struct TYPE_20__ {int /*<<< orphan*/  hWindow; } ;
typedef  TYPE_4__ SMALL_RECT ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_5__* PGUI_CONSOLE_DATA ;
typedef  TYPE_6__* PCOORD ;
typedef  TYPE_7__* PCONSOLE ;
typedef  int /*<<< orphan*/  HRGN ;

/* Variables and functions */
 int CONSOLE_NO_SELECTION ; 
 int CONSOLE_SELECTION_NOT_EMPTY ; 
 scalar_t__ CombineRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConioPause (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConioUnpause (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateRectRgnIndirect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAUSED_FROM_SELECTION ; 
 int /*<<< orphan*/  RGN_XOR ; 
 int /*<<< orphan*/  SmallRectToRect (TYPE_5__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 void* max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (TYPE_4__*,TYPE_4__*,int) ; 
 void* min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
GuiConsoleUpdateSelection(PCONSOLE Console, PCOORD coord)
{
    PGUI_CONSOLE_DATA GuiData = Console->TermIFace.Data;
    RECT oldRect, newRect;

    SmallRectToRect(GuiData, &oldRect, &Console->Selection.srSelection);

    if (coord != NULL)
    {
        SMALL_RECT rc;
        /* exchange left/top with right/bottom if required */
        rc.Left   = min(Console->Selection.dwSelectionAnchor.X, coord->X);
        rc.Top    = min(Console->Selection.dwSelectionAnchor.Y, coord->Y);
        rc.Right  = max(Console->Selection.dwSelectionAnchor.X, coord->X);
        rc.Bottom = max(Console->Selection.dwSelectionAnchor.Y, coord->Y);

        SmallRectToRect(GuiData, &newRect, &rc);

        if (Console->Selection.dwFlags & CONSOLE_SELECTION_NOT_EMPTY)
        {
            if (memcmp(&rc, &Console->Selection.srSelection, sizeof(SMALL_RECT)) != 0)
            {
                HRGN rgn1, rgn2;

                /* calculate the region that needs to be updated */
                if ((rgn1 = CreateRectRgnIndirect(&oldRect)))
                {
                    if ((rgn2 = CreateRectRgnIndirect(&newRect)))
                    {
                        if (CombineRgn(rgn1, rgn2, rgn1, RGN_XOR) != ERROR)
                        {
                            InvalidateRgn(GuiData->hWindow, rgn1, FALSE);
                        }
                        DeleteObject(rgn2);
                    }
                    DeleteObject(rgn1);
                }
            }
        }
        else
        {
            InvalidateRect(GuiData->hWindow, &newRect, FALSE);
        }
        Console->Selection.dwFlags |= CONSOLE_SELECTION_NOT_EMPTY;
        Console->Selection.srSelection = rc;
        Console->dwSelectionCursor = *coord;
        ConioPause(Console, PAUSED_FROM_SELECTION);
    }
    else
    {
        /* clear the selection */
        if (Console->Selection.dwFlags & CONSOLE_SELECTION_NOT_EMPTY)
        {
            InvalidateRect(GuiData->hWindow, &oldRect, FALSE);
        }
        Console->Selection.dwFlags = CONSOLE_NO_SELECTION;
        ConioUnpause(Console, PAUSED_FROM_SELECTION);
    }
}