#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {int /*<<< orphan*/  ViewOrigin; } ;
struct TYPE_6__ {int /*<<< orphan*/  dwFlags; } ;
struct TYPE_7__ {int /*<<< orphan*/  dwSelectionCursor; TYPE_1__ Selection; TYPE_3__* ActiveBuffer; } ;
typedef  TYPE_2__* PGUI_CONSOLE_DATA ;
typedef  TYPE_3__* PCONSOLE_SCREEN_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  CONSOLE_NO_SELECTION ; 
 int /*<<< orphan*/  UpdateSelection (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VOID
Mark(PGUI_CONSOLE_DATA GuiData)
{
    PCONSOLE_SCREEN_BUFFER ActiveBuffer = GuiData->ActiveBuffer;

    /* Clear the old selection */
    GuiData->Selection.dwFlags = CONSOLE_NO_SELECTION;

    /* Restart a new selection */
    GuiData->dwSelectionCursor = ActiveBuffer->ViewOrigin;
    UpdateSelection(GuiData,
                    &GuiData->dwSelectionCursor,
                    &GuiData->dwSelectionCursor);
}