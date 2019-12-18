#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int dwSize; int /*<<< orphan*/  bVisible; } ;
struct TYPE_5__ {void* Y; void* X; } ;
typedef  void* SHORT ;
typedef  int DWORD ;
typedef  TYPE_1__ COORD ;
typedef  TYPE_2__ CONSOLE_CURSOR_INFO ;
typedef  scalar_t__ BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,void*,void*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetConsoleCursorInfo (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SetConsoleCursorPosition (int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  TextConsoleBuffer ; 

VOID
VgaConsoleUpdateTextCursor(BOOL CursorVisible,
                           BYTE CursorStart,
                           BYTE CursorEnd,
                           BYTE TextSize,
                           DWORD ScanlineSize,
                           WORD Location)
{
    COORD Position;
    CONSOLE_CURSOR_INFO CursorInfo;

    if (CursorStart < CursorEnd)
    {
        /* Visible cursor */
        CursorInfo.bVisible = CursorVisible;
        CursorInfo.dwSize   = (100 * (CursorEnd - CursorStart)) / TextSize;
    }
    else
    {
        /* Hidden cursor */
        CursorInfo.bVisible = FALSE;
        CursorInfo.dwSize   = 1; // The size needs to be non-zero for SetConsoleCursorInfo to succeed.
    }

    /* Find the coordinates of the new position */
    Position.X = (SHORT)(Location % ScanlineSize);
    Position.Y = (SHORT)(Location / ScanlineSize);

    DPRINT("VgaConsoleUpdateTextCursor: (X = %d ; Y = %d)\n", Position.X, Position.Y);

    /* Update the physical cursor */
    SetConsoleCursorInfo(TextConsoleBuffer, &CursorInfo);
    SetConsoleCursorPosition(TextConsoleBuffer, Position);
}