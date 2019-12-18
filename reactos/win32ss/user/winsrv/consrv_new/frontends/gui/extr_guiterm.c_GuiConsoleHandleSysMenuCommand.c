#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_22__ {int /*<<< orphan*/  Buffer; int /*<<< orphan*/  Length; } ;
struct TYPE_18__ {int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
struct TYPE_21__ {int dwFlags; TYPE_10__ dwSelectionAnchor; } ;
struct TYPE_25__ {int /*<<< orphan*/  Lock; TYPE_4__ Title; TYPE_10__ dwSelectionCursor; TYPE_3__ Selection; } ;
struct TYPE_20__ {int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
struct TYPE_19__ {int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
struct TYPE_24__ {TYPE_2__ ViewSize; TYPE_1__ ViewOrigin; } ;
struct TYPE_23__ {scalar_t__ cmdIdLow; scalar_t__ cmdIdHigh; int /*<<< orphan*/  hWindow; TYPE_7__* Console; } ;
typedef  int SIZE_T ;
typedef  TYPE_5__* PGUI_CONSOLE_DATA ;
typedef  TYPE_6__* PCONSOLE_SCREEN_BUFFER ;
typedef  TYPE_7__* PCONSOLE ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int CONSOLE_MOUSE_SELECTION ; 
 int /*<<< orphan*/  CONSOLE_RUNNING ; 
 int CONSOLE_SELECTION_IN_PROGRESS ; 
 TYPE_6__* ConDrvGetActiveScreenBuffer (TYPE_7__*) ; 
 int /*<<< orphan*/  ConDrvValidateConsoleUnsafe (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * ConsoleAllocHeap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ConsoleFreeHeap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ DefWindowProcW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GuiConsoleCopy (TYPE_5__*) ; 
 int /*<<< orphan*/  GuiConsolePaste (TYPE_5__*) ; 
 int /*<<< orphan*/  GuiConsoleShowConsoleProperties (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  GuiConsoleUpdateSelection (TYPE_7__*,TYPE_10__*) ; 
 int /*<<< orphan*/  GuiSendMenuEvent (TYPE_7__*,scalar_t__) ; 
#define  ID_SYSTEM_DEFAULTS 135 
#define  ID_SYSTEM_EDIT_COPY 134 
#define  ID_SYSTEM_EDIT_FIND 133 
#define  ID_SYSTEM_EDIT_MARK 132 
#define  ID_SYSTEM_EDIT_PASTE 131 
#define  ID_SYSTEM_EDIT_SCROLL 130 
#define  ID_SYSTEM_EDIT_SELECTALL 129 
#define  ID_SYSTEM_PROPERTIES 128 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetWindowText (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WM_SYSCOMMAND ; 
 int /*<<< orphan*/  wcscat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static LRESULT
GuiConsoleHandleSysMenuCommand(PGUI_CONSOLE_DATA GuiData, WPARAM wParam, LPARAM lParam)
{
    LRESULT Ret = TRUE;
    PCONSOLE Console = GuiData->Console;
    PCONSOLE_SCREEN_BUFFER ActiveBuffer;

    if (!ConDrvValidateConsoleUnsafe(Console, CONSOLE_RUNNING, TRUE))
    {
        Ret = FALSE;
        goto Quit;
    }
    ActiveBuffer = ConDrvGetActiveScreenBuffer(Console);

    /*
     * In case the selected menu item belongs to the user-reserved menu id range,
     * send to him a menu event and return directly. The user must handle those
     * reserved menu commands...
     */
    if (GuiData->cmdIdLow <= (UINT)wParam && (UINT)wParam <= GuiData->cmdIdHigh)
    {
        GuiSendMenuEvent(Console, (UINT)wParam);
        goto Unlock_Quit;
    }

    /* ... otherwise, perform actions. */
    switch (wParam)
    {
        case ID_SYSTEM_EDIT_MARK:
        {
            LPWSTR WindowTitle = NULL;
            SIZE_T Length = 0;

            Console->dwSelectionCursor.X = ActiveBuffer->ViewOrigin.X;
            Console->dwSelectionCursor.Y = ActiveBuffer->ViewOrigin.Y;
            Console->Selection.dwSelectionAnchor = Console->dwSelectionCursor;
            Console->Selection.dwFlags |= CONSOLE_SELECTION_IN_PROGRESS;
            GuiConsoleUpdateSelection(Console, &Console->Selection.dwSelectionAnchor);

            Length = Console->Title.Length + sizeof(L"Mark - ")/sizeof(WCHAR) + 1;
            WindowTitle = ConsoleAllocHeap(0, Length * sizeof(WCHAR));
            wcscpy(WindowTitle, L"Mark - ");
            wcscat(WindowTitle, Console->Title.Buffer);
            SetWindowText(GuiData->hWindow, WindowTitle);
            ConsoleFreeHeap(WindowTitle);

            break;
        }

        case ID_SYSTEM_EDIT_COPY:
            GuiConsoleCopy(GuiData);
            break;

        case ID_SYSTEM_EDIT_PASTE:
            GuiConsolePaste(GuiData);
            break;

        case ID_SYSTEM_EDIT_SELECTALL:
        {
            LPWSTR WindowTitle = NULL;
            SIZE_T Length = 0;

            Console->Selection.dwSelectionAnchor.X = 0;
            Console->Selection.dwSelectionAnchor.Y = 0;
            Console->dwSelectionCursor.X = ActiveBuffer->ViewSize.X - 1;
            Console->dwSelectionCursor.Y = ActiveBuffer->ViewSize.Y - 1;
            Console->Selection.dwFlags |= CONSOLE_SELECTION_IN_PROGRESS | CONSOLE_MOUSE_SELECTION;
            GuiConsoleUpdateSelection(Console, &Console->dwSelectionCursor);

            Length = Console->Title.Length + sizeof(L"Selection - ")/sizeof(WCHAR) + 1;
            WindowTitle = ConsoleAllocHeap(0, Length * sizeof(WCHAR));
            wcscpy(WindowTitle, L"Selection - ");
            wcscat(WindowTitle, Console->Title.Buffer);
            SetWindowText(GuiData->hWindow, WindowTitle);
            ConsoleFreeHeap(WindowTitle);

            break;
        }

        case ID_SYSTEM_EDIT_SCROLL:
            DPRINT1("Scrolling is not handled yet\n");
            break;

        case ID_SYSTEM_EDIT_FIND:
            DPRINT1("Finding is not handled yet\n");
            break;

        case ID_SYSTEM_DEFAULTS:
            GuiConsoleShowConsoleProperties(GuiData, TRUE);
            break;

        case ID_SYSTEM_PROPERTIES:
            GuiConsoleShowConsoleProperties(GuiData, FALSE);
            break;

        default:
            Ret = FALSE;
            break;
    }

Unlock_Quit:
    LeaveCriticalSection(&Console->Lock);
Quit:
    if (!Ret)
        Ret = DefWindowProcW(GuiData->hWindow, WM_SYSCOMMAND, wParam, lParam);

    return Ret;
}