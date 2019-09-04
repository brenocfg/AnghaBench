#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {scalar_t__ bInstalled; scalar_t__ bVirtual; int /*<<< orphan*/  ucOriginalOpcode; scalar_t__ ulAddress; } ;
typedef  int /*<<< orphan*/ * PUCHAR ;
typedef  TYPE_1__* PSW_BP ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 scalar_t__ FALSE ; 
 TYPE_1__* FindSwBp (int /*<<< orphan*/ ) ; 
 scalar_t__ IsAddressValid (int /*<<< orphan*/ ) ; 
 scalar_t__ IsAddressWriteable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  SetAddressWriteable (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TRUE ; 

BOOLEAN DeInstallSWBreakpoint(ULONG ulAddress)
{
    PSW_BP p;
    BOOLEAN bResult = FALSE;

    ENTER_FUNC();
    DPRINT((0,"DeInstallSWBreakpoint()\n"));

    if( (p = FindSwBp(ulAddress)) )
    {
        if(IsAddressValid(ulAddress) && p->bInstalled == TRUE && p->bVirtual==FALSE)
        {
			BOOLEAN isWriteable;
			if( !( isWriteable = IsAddressWriteable(ulAddress) ) )
				SetAddressWriteable(ulAddress,TRUE);
            // restore original opcode
            *(PUCHAR)(p->ulAddress) = p->ucOriginalOpcode;
			if( !isWriteable )
				SetAddressWriteable(ulAddress,FALSE);
        }

        p->bInstalled = FALSE;

        bResult = TRUE;
    }

    LEAVE_FUNC();

    return bResult;
}