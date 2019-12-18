#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {int /*<<< orphan*/  Buffer; } ;
struct TYPE_9__ {TYPE_1__ Title; } ;
struct TYPE_8__ {int /*<<< orphan*/  hWindow; TYPE_3__* Console; } ;
typedef  int /*<<< orphan*/  PTEXTMODE_SCREEN_BUFFER ;
typedef  TYPE_2__* PGUI_CONSOLE_DATA ;
typedef  int /*<<< orphan*/  PGRAPHICS_SCREEN_BUFFER ;
typedef  scalar_t__ PCONSOLE_SCREEN_BUFFER ;
typedef  TYPE_3__* PCONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseClipboard () ; 
 scalar_t__ ConDrvGetActiveScreenBuffer (TYPE_3__*) ; 
 scalar_t__ GetType (scalar_t__) ; 
 int /*<<< orphan*/  GuiConsoleUpdateSelection (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GuiCopyFromGraphicsBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GuiCopyFromTextModeBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ OpenClipboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowText (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEXTMODE_BUFFER ; 

__attribute__((used)) static VOID
GuiConsoleCopy(PGUI_CONSOLE_DATA GuiData)
{
    if (OpenClipboard(GuiData->hWindow))
    {
        PCONSOLE Console = GuiData->Console;
        PCONSOLE_SCREEN_BUFFER Buffer = ConDrvGetActiveScreenBuffer(Console);

        if (GetType(Buffer) == TEXTMODE_BUFFER)
        {
            GuiCopyFromTextModeBuffer((PTEXTMODE_SCREEN_BUFFER)Buffer);
        }
        else /* if (GetType(Buffer) == GRAPHICS_BUFFER) */
        {
            GuiCopyFromGraphicsBuffer((PGRAPHICS_SCREEN_BUFFER)Buffer);
        }

        CloseClipboard();

        /* Clear the selection */
        GuiConsoleUpdateSelection(Console, NULL);
        SetWindowText(GuiData->hWindow, Console->Title.Buffer);
    }
}