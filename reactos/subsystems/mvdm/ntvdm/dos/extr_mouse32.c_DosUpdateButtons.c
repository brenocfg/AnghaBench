#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int USHORT ;
struct TYPE_2__ {int ButtonState; int /*<<< orphan*/  Position; int /*<<< orphan*/ * LastRelease; int /*<<< orphan*/ * ReleaseCount; int /*<<< orphan*/ * LastPress; int /*<<< orphan*/ * PressCount; } ;
typedef  int BYTE ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CallMouseUserHandlers (int) ; 
 TYPE_1__ DriverState ; 
 int NUM_MOUSE_BUTTONS ; 

__attribute__((used)) static inline VOID DosUpdateButtons(BYTE ButtonState) // WORD ButtonState
{
    USHORT i;
    USHORT CallMask = 0x0000; // We use MS MOUSE v1.0+ format

    for (i = 0; i < NUM_MOUSE_BUTTONS; i++)
    {
        BOOLEAN OldState = (DriverState.ButtonState >> i) & 1;
        BOOLEAN NewState = (ButtonState >> i) & 1;

        if (NewState > OldState)
        {
            /* Mouse press */
            DriverState.PressCount[i]++;
            DriverState.LastPress[i] = DriverState.Position;

            CallMask |= (1 << (2 * i + 1));
        }
        else if (NewState < OldState)
        {
            /* Mouse release */
            DriverState.ReleaseCount[i]++;
            DriverState.LastRelease[i] = DriverState.Position;

            CallMask |= (1 << (2 * i + 2));
        }
    }

    DriverState.ButtonState = ButtonState;

    /* Call the mouse handlers */
    CallMouseUserHandlers(CallMask);
}