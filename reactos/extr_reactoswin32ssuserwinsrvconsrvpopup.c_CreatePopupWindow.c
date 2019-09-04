#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  PopupWindows; } ;
struct TYPE_16__ {int X; int Y; } ;
struct TYPE_15__ {void* Y; void* X; } ;
struct TYPE_20__ {int /*<<< orphan*/  ListEntry; int /*<<< orphan*/ * OldContents; TYPE_2__ Size; TYPE_1__ Origin; TYPE_5__* ScreenBuffer; } ;
struct TYPE_17__ {scalar_t__ Console; } ;
struct TYPE_19__ {TYPE_3__ Header; } ;
struct TYPE_18__ {void* Bottom; void* Right; void* Top; void* Left; } ;
typedef  TYPE_4__ SMALL_RECT ;
typedef  void* SHORT ;
typedef  TYPE_5__* PTEXTMODE_SCREEN_BUFFER ;
typedef  TYPE_6__* PPOPUP_WINDOW ;
typedef  TYPE_7__* PCONSRV_CONSOLE ;
typedef  scalar_t__ PCONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ConDrvReadConsoleOutput (scalar_t__,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 void* ConsoleAllocHeap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ConsoleFreeHeap (TYPE_6__*) ; 
 int /*<<< orphan*/  DrawBox (TYPE_5__*,void*,void*,void*,void*) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

PPOPUP_WINDOW
CreatePopupWindow(PCONSRV_CONSOLE Console,
                  PTEXTMODE_SCREEN_BUFFER Buffer,
                  SHORT xLeft,
                  SHORT yTop,
                  SHORT Width,
                  SHORT Height)
{
    PPOPUP_WINDOW Popup;
    SMALL_RECT Region;

    ASSERT((PCONSOLE)Console == Buffer->Header.Console);

    /* Create the popup window */
    Popup = ConsoleAllocHeap(HEAP_ZERO_MEMORY, sizeof(*Popup));
    if (Popup == NULL) return NULL;

    Popup->ScreenBuffer = Buffer;
    Popup->Origin.X = xLeft;
    Popup->Origin.Y = yTop;
    Popup->Size.X = Width;
    Popup->Size.Y = Height;

    /* Save old contents */
    Popup->OldContents = ConsoleAllocHeap(HEAP_ZERO_MEMORY,
                                          Popup->Size.X * Popup->Size.Y *
                                            sizeof(*Popup->OldContents));
    if (Popup->OldContents == NULL)
    {
        ConsoleFreeHeap(Popup);
        return NULL;
    }
    Region.Left   = Popup->Origin.X;
    Region.Top    = Popup->Origin.Y;
    Region.Right  = Popup->Origin.X + Popup->Size.X - 1;
    Region.Bottom = Popup->Origin.Y + Popup->Size.Y - 1;
    ConDrvReadConsoleOutput(Buffer->Header.Console,
                            Buffer,
                            TRUE,
                            Popup->OldContents,
                            &Region);

    /* Draw it */
    DrawBox(Buffer,
            xLeft, yTop,
            Width, Height);

    /* Add it into the list of popups */
    InsertTailList(&Console->PopupWindows, &Popup->ListEntry);

    return Popup;
}