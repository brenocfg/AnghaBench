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
typedef  int WORD ;
struct TYPE_4__ {int Number; int VesaNumber; } ;
typedef  TYPE_1__* PCVBE_MODE ;
typedef  size_t INT ;

/* Variables and functions */
 TYPE_1__* Modes ; 
 size_t VBE_MODE_COUNT ; 

PCVBE_MODE VbeGetModeByNumber(WORD Number)
{
    INT i;

    Number &= 0x1FF;

    /* Find the mode */
    for (i = 0; i < VBE_MODE_COUNT; i++)
    {
        if ((!(Number & 0x100) && (Number == Modes[i].Number))
            || ((Number & 0x100) && (Number== Modes[i].VesaNumber)))
        {
            return &Modes[i];
        }
    }

    return NULL;
}