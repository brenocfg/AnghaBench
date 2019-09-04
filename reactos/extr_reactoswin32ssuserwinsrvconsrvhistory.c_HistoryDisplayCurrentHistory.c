#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ ActiveBuffer; } ;
struct TYPE_18__ {scalar_t__ NumEntries; } ;
struct TYPE_17__ {int /*<<< orphan*/ * PopupInputRoutine; } ;
struct TYPE_15__ {int X; int Y; } ;
struct TYPE_14__ {int X; int Y; } ;
struct TYPE_16__ {TYPE_2__ ViewSize; TYPE_1__ ViewOrigin; } ;
typedef  int SHORT ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  TYPE_3__* PTEXTMODE_SCREEN_BUFFER ;
typedef  TYPE_4__* PPOPUP_WINDOW ;
typedef  TYPE_5__* PHISTORY_BUFFER ;
typedef  TYPE_6__* PCONSRV_CONSOLE ;

/* Variables and functions */
 TYPE_4__* CreatePopupWindow (TYPE_6__*,TYPE_3__*,int,int,int,int) ; 
 scalar_t__ GetType (scalar_t__) ; 
 TYPE_5__* HistoryCurrentBuffer (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TEXTMODE_BUFFER ; 

PPOPUP_WINDOW
HistoryDisplayCurrentHistory(PCONSRV_CONSOLE Console,
                             PUNICODE_STRING ExeName)
{
    PTEXTMODE_SCREEN_BUFFER ActiveBuffer;
    PPOPUP_WINDOW Popup;

    SHORT xLeft, yTop;
    SHORT Width, Height;

    PHISTORY_BUFFER Hist = HistoryCurrentBuffer(Console, ExeName);

    if (!Hist) return NULL;
    if (Hist->NumEntries == 0) return NULL;

    if (GetType(Console->ActiveBuffer) != TEXTMODE_BUFFER) return NULL;
    ActiveBuffer = (PTEXTMODE_SCREEN_BUFFER)Console->ActiveBuffer;

    Width  = 40;
    Height = 10;

    /* Center the popup window on the screen */
    xLeft = ActiveBuffer->ViewOrigin.X + (ActiveBuffer->ViewSize.X - Width ) / 2;
    yTop  = ActiveBuffer->ViewOrigin.Y + (ActiveBuffer->ViewSize.Y - Height) / 2;

    /* Create the popup */
    Popup = CreatePopupWindow(Console, ActiveBuffer,
                              xLeft, yTop, Width, Height);
    if (Popup == NULL) return NULL;

    Popup->PopupInputRoutine = NULL;

    return Popup;
}