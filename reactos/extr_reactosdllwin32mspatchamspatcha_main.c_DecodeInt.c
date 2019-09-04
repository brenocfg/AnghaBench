#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PSAFE_READ ;
typedef  int INT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ ReadByte (int /*<<< orphan*/ ) ; 

INT DecodeInt(PSAFE_READ pRead)
{
    INT Result = 0, offset;

    for (offset = 0; offset < 32; offset += 6)
    {
        INT val = (INT)(DWORD)ReadByte(pRead);
        Result |= ((val & 0x3f) << offset);
        if (val & 0x80)
        {
            if (val & 0x40)
                Result *= -1;
            break;
        }
    }

    return Result;
}