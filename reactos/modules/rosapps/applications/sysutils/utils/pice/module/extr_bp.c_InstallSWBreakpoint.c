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
typedef  void* ULONG ;
struct TYPE_4__ {int ucOriginalOpcode; void (* Callback ) () ;void* bPermanent; void* ulNextInstr; void* ulAddress; void* bInstalled; void* bUsed; } ;
typedef  int* PUCHAR ;
typedef  TYPE_1__* PSW_BP ;
typedef  void* BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/ * ADDR_TO_PDE (void*) ; 
 int /*<<< orphan*/ * ADDR_TO_PTE (void*) ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disasm (void**,int*) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 void* FALSE ; 
 TYPE_1__* FindEmptySwBpSlot () ; 
 TYPE_1__* FindSwBp (void*) ; 
 scalar_t__ IsAddressValid (void*) ; 
 void* IsAddressWriteable (void*) ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  SetAddressWriteable (void*,void*) ; 
 void* TRUE ; 
 int /*<<< orphan*/  tempBp ; 

BOOLEAN InstallSWBreakpoint(ULONG ulAddress,BOOLEAN bPermanent,void (*SWBreakpointCallback)(void))
{
    PSW_BP p;
    BOOLEAN bResult = FALSE;

    ENTER_FUNC();
    DPRINT((0,"InstallSWBreakpoint()\n"));

    // check if page is present
    // TODO: must also check if it's a writable page
    if(IsAddressValid(ulAddress) )
    {
        DPRINT((0,"InstallSWBreakpoint(): %.8X is valid, writable? %d\n",ulAddress,IsAddressWriteable(ulAddress)));
		DPRINT((0,"pde: %x, pte: %x\n", *(ADDR_TO_PDE(ulAddress)), *(ADDR_TO_PTE(ulAddress))));
        if((p = FindSwBp(ulAddress))==NULL)
        {
            DPRINT((0,"InstallSWBreakpoint(): %.8X is free\n",ulAddress));
            if( (p=FindEmptySwBpSlot()) )
            {
				BOOLEAN isWriteable;
                DPRINT((0,"InstallSWBreakpoint(): found empty slot\n"));
				DPRINT((0,"InstallSWBreakpoint(): %x value: %x", ulAddress, *(PUCHAR)ulAddress));
                p->ucOriginalOpcode = *(PUCHAR)ulAddress;
				//allow writing to page
				if( !( isWriteable = IsAddressWriteable(ulAddress) ) )
					SetAddressWriteable(ulAddress,TRUE);
			    DPRINT((0,"writing breakpoint\n"));
				*(PUCHAR)ulAddress = 0xCC;
				DPRINT((0,"restoring page access\n"));
				if( !isWriteable )
					SetAddressWriteable(ulAddress,FALSE);
				p->bUsed = TRUE;
                p->bInstalled = TRUE;
                // find next address
                p->ulAddress = ulAddress;
                Disasm(&ulAddress,(PUCHAR)&tempBp);
                p->ulNextInstr = ulAddress;
                p->bPermanent = bPermanent;
                if(bPermanent)
                    p->Callback = SWBreakpointCallback;
				else
					p->Callback = NULL;
                bResult = TRUE;
            }
        }
        else
        {
            DPRINT((0,"InstallSWBreakpoint(): %.8X is already used\n",ulAddress));
            if(p->bPermanent)
            {
                DPRINT((0,"InstallSWBreakpoint(): %.8X is a permanent breakpoint\n",ulAddress));
            }
        }
    }

    LEAVE_FUNC();

    return bResult;
}