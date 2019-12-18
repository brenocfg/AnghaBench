#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int Mode; } ;
typedef  TYPE_1__* PPIT_CHANNEL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  PIT_MODE_HARDWARE_ONE_SHOT 133 
#define  PIT_MODE_HARDWARE_STROBE 132 
#define  PIT_MODE_INT_ON_TERMINAL_COUNT 131 
#define  PIT_MODE_RATE_GENERATOR 130 
#define  PIT_MODE_SOFTWARE_STROBE 129 
#define  PIT_MODE_SQUARE_WAVE 128 
 int /*<<< orphan*/  PitSetOut (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static VOID PitInitCounter(PPIT_CHANNEL Channel)
{
    switch (Channel->Mode)
    {
        case PIT_MODE_INT_ON_TERMINAL_COUNT:
            PitSetOut(Channel, FALSE);
            break;

        case PIT_MODE_HARDWARE_ONE_SHOT:
        case PIT_MODE_RATE_GENERATOR:
        case PIT_MODE_SQUARE_WAVE:
        case PIT_MODE_SOFTWARE_STROBE:
        case PIT_MODE_HARDWARE_STROBE:
            PitSetOut(Channel, TRUE);
            break;
    }
}