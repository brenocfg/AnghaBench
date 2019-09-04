#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_18__ {scalar_t__ Y; scalar_t__ X; } ;
struct TYPE_17__ {scalar_t__ Y; scalar_t__ X; } ;
struct TYPE_13__ {scalar_t__ Y; scalar_t__ X; } ;
struct TYPE_12__ {scalar_t__ Y; } ;
struct TYPE_16__ {TYPE_2__ ScreenBufferSize; TYPE_1__ CursorPosition; } ;
struct TYPE_14__ {int /*<<< orphan*/  dwFlags; } ;
struct TYPE_15__ {TYPE_9__ dwSelectionCursor; TYPE_3__ Selection; TYPE_5__* ActiveBuffer; } ;
typedef  TYPE_4__* PGUI_CONSOLE_DATA ;
typedef  TYPE_5__* PCONSOLE_SCREEN_BUFFER ;
typedef  TYPE_6__ COORD ;

/* Variables and functions */
 int /*<<< orphan*/  CONSOLE_MOUSE_SELECTION ; 
 int /*<<< orphan*/  CONSOLE_NO_SELECTION ; 
 scalar_t__ GetType (TYPE_5__*) ; 
 scalar_t__ TEXTMODE_BUFFER ; 
 int /*<<< orphan*/  UpdateSelection (TYPE_4__*,TYPE_6__*,TYPE_9__*) ; 

__attribute__((used)) static VOID
SelectAll(PGUI_CONSOLE_DATA GuiData)
{
    PCONSOLE_SCREEN_BUFFER ActiveBuffer = GuiData->ActiveBuffer;
    COORD SelectionAnchor;

    /* Clear the old selection */
    GuiData->Selection.dwFlags = CONSOLE_NO_SELECTION;

    /*
     * The selection area extends to the whole screen buffer's width.
     */
    SelectionAnchor.X = SelectionAnchor.Y = 0;
    GuiData->dwSelectionCursor.X = ActiveBuffer->ScreenBufferSize.X - 1;

    /*
     * Determine whether the selection must extend to just some part
     * (for text-mode screen buffers) or to all of the screen buffer's
     * height (for graphics ones).
     */
    if (GetType(ActiveBuffer) == TEXTMODE_BUFFER)
    {
        /*
         * We select all the characters from the first line
         * to the line where the cursor is positioned.
         */
        GuiData->dwSelectionCursor.Y = ActiveBuffer->CursorPosition.Y;
    }
    else /* if (GetType(ActiveBuffer) == GRAPHICS_BUFFER) */
    {
        /*
         * We select all the screen buffer area.
         */
        GuiData->dwSelectionCursor.Y = ActiveBuffer->ScreenBufferSize.Y - 1;
    }

    /* Restart a new selection */
    GuiData->Selection.dwFlags |= CONSOLE_MOUSE_SELECTION;
    UpdateSelection(GuiData, &SelectionAnchor, &GuiData->dwSelectionCursor);
}