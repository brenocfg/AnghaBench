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
typedef  int* PUCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentCS ; 
 int /*<<< orphan*/  CurrentEIP ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLinearAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN IsRetAtEIP(void)
{
	PUCHAR linear;
	BOOLEAN bResult = FALSE;

    ENTER_FUNC();
	DPRINT((0,"IsRetAtEIP()\n"));

	linear=(PUCHAR)GetLinearAddress(CurrentCS,CurrentEIP);

    switch(*linear)
    {
        case 0xc2:
        case 0xc3:
        case 0xca:
        case 0xcb:
        case 0xcf: // IRET/IRETD
			bResult = TRUE;
            break;
    }

    LEAVE_FUNC();

    return bResult;
}