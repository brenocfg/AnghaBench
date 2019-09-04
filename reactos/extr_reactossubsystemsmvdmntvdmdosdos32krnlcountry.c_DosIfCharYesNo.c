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
typedef  scalar_t__ WORD ;

/* Variables and functions */
 scalar_t__* YesNoTable ; 
 scalar_t__ toupper (scalar_t__) ; 

WORD DosIfCharYesNo(WORD Char)
{
    Char = toupper(Char);

    /* NO-type */
    if (Char == YesNoTable[1])
        return 0x0000;
    /* YES-type */
    if (Char == YesNoTable[0])
        return 0x0001;
    /* Unknown type */
        return 0x0002;
}