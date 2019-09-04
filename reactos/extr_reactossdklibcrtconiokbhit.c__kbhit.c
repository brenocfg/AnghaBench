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
struct TYPE_6__ {scalar_t__ bKeyDown; } ;
struct TYPE_7__ {TYPE_1__ KeyEvent; } ;
struct TYPE_8__ {scalar_t__ EventType; TYPE_2__ Event; } ;
typedef  TYPE_3__* PINPUT_RECORD ;
typedef  int /*<<< orphan*/  INPUT_RECORD ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CriticalSection ; 
 scalar_t__ CriticalSectionInitialized ; 
 int ENABLE_PROCESSED_INPUT ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetConsoleMode (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetNumberOfConsoleInputEvents (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeCriticalSectionAndSpinCount (int /*<<< orphan*/ *,int) ; 
 scalar_t__ KEY_EVENT ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PeekConsoleInput (int /*<<< orphan*/ ,TYPE_3__*,int,int*) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  SetConsoleMode (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 
 scalar_t__ char_avail ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 scalar_t__ malloc (int) ; 

int _kbhit(void)
{
    PINPUT_RECORD InputRecord = NULL;
    DWORD NumberRead = 0;
    DWORD EventsRead = 0;
    DWORD RecordIndex = 0;
    DWORD BufferIndex = 0;
    HANDLE StdInputHandle = 0;
    DWORD ConsoleInputMode = 0;

    /* Attempt some thread safety */
    if (!CriticalSectionInitialized)
    {
        InitializeCriticalSectionAndSpinCount(&CriticalSection, 0x80000400);
        CriticalSectionInitialized = TRUE;
    }

    EnterCriticalSection(&CriticalSection);

    if (char_avail)
    {
        LeaveCriticalSection(&CriticalSection);
        return 1;
    }

    StdInputHandle = GetStdHandle(STD_INPUT_HANDLE);

    /* Turn off processed input so we get key modifiers as well */
    GetConsoleMode(StdInputHandle, &ConsoleInputMode);

    SetConsoleMode(StdInputHandle, ConsoleInputMode & ~ENABLE_PROCESSED_INPUT);

    /* Start the process */
    if (!GetNumberOfConsoleInputEvents(StdInputHandle, &EventsRead))
    {
        LeaveCriticalSection(&CriticalSection);
        return 0;
    }

    if (!EventsRead)
    {
        LeaveCriticalSection(&CriticalSection);
        return 0;
    }

    if (!(InputRecord = (PINPUT_RECORD)malloc(EventsRead * sizeof(INPUT_RECORD))))
    {
        LeaveCriticalSection(&CriticalSection);
        return 0;
    }

    if (!PeekConsoleInput(StdInputHandle, InputRecord, EventsRead, &NumberRead))
    {
        free(InputRecord);
        LeaveCriticalSection(&CriticalSection);
        return 0;
    }

    for (RecordIndex = 0; RecordIndex < NumberRead; RecordIndex++)
    {
        if (InputRecord[RecordIndex].EventType == KEY_EVENT &&
            InputRecord[RecordIndex].Event.KeyEvent.bKeyDown)
        {
            BufferIndex = 1;
            break;
        }
    }

    free(InputRecord);

    /* Restore console input mode */
    SetConsoleMode(StdInputHandle, ConsoleInputMode);

    LeaveCriticalSection(&CriticalSection);

    return BufferIndex;
}