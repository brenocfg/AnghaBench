#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  char WORD ;
typedef  int ULONG ;
struct TYPE_14__ {int Mode; } ;
struct TYPE_16__ {int PauseFlags; TYPE_3__ InputBuffer; } ;
struct TYPE_12__ {char wVirtualKeyCode; int dwControlKeyState; scalar_t__ bKeyDown; } ;
struct TYPE_13__ {TYPE_1__ KeyEvent; } ;
struct TYPE_15__ {scalar_t__ EventType; TYPE_2__ Event; } ;
typedef  TYPE_4__* PINPUT_RECORD ;
typedef  TYPE_5__* PCONSRV_CONSOLE ;
typedef  int /*<<< orphan*/  INPUT_RECORD ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConioPause (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ConioUnpause (TYPE_5__*,int) ; 
 int ENABLE_LINE_INPUT ; 
 scalar_t__ KEY_EVENT ; 
 int LEFT_ALT_PRESSED ; 
 int LEFT_CTRL_PRESSED ; 
 int PAUSED_FROM_KEYBOARD ; 
 int RIGHT_ALT_PRESSED ; 
 int RIGHT_CTRL_PRESSED ; 
 int /*<<< orphan*/  RtlMoveMemory (TYPE_4__*,TYPE_4__*,int) ; 
 char VK_CAPITAL ; 
 char VK_LWIN ; 
 char VK_NUMLOCK ; 
 char VK_PAUSE ; 
 char VK_RWIN ; 
 char VK_SCROLL ; 
 char VK_SHIFT ; 

__attribute__((used)) static ULONG
PreprocessInput(PCONSRV_CONSOLE Console,
                PINPUT_RECORD InputEvent,
                ULONG NumEventsToWrite)
{
    ULONG NumEvents;

    /*
     * Loop each event, and for each, check for pause or unpause
     * and perform adequate behaviour.
     */
    for (NumEvents = NumEventsToWrite; NumEvents > 0; --NumEvents)
    {
        /* Check for pause or unpause */
        if (InputEvent->EventType == KEY_EVENT && InputEvent->Event.KeyEvent.bKeyDown)
        {
            WORD vk = InputEvent->Event.KeyEvent.wVirtualKeyCode;
            if (!(Console->PauseFlags & PAUSED_FROM_KEYBOARD))
            {
                DWORD cks = InputEvent->Event.KeyEvent.dwControlKeyState;
                if (Console->InputBuffer.Mode & ENABLE_LINE_INPUT &&
                    (vk == VK_PAUSE ||
                    (vk == 'S' && (cks & (LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED)) &&
                                 !(cks & (LEFT_ALT_PRESSED  | RIGHT_ALT_PRESSED)))))
                {
                    ConioPause(Console, PAUSED_FROM_KEYBOARD);

                    /* Skip the event */
                    RtlMoveMemory(InputEvent,
                                  InputEvent + 1,
                                  (NumEvents - 1) * sizeof(INPUT_RECORD));
                    --NumEventsToWrite;
                    continue;
                }
            }
            else
            {
                if ((vk < VK_SHIFT || vk > VK_CAPITAL) && vk != VK_LWIN &&
                    vk != VK_RWIN && vk != VK_NUMLOCK && vk != VK_SCROLL)
                {
                    ConioUnpause(Console, PAUSED_FROM_KEYBOARD);

                    /* Skip the event */
                    RtlMoveMemory(InputEvent,
                                  InputEvent + 1,
                                  (NumEvents - 1) * sizeof(INPUT_RECORD));
                    --NumEventsToWrite;
                    continue;
                }
            }
        }

        /* Go to the next event */
        ++InputEvent;
    }

    return NumEventsToWrite;
}