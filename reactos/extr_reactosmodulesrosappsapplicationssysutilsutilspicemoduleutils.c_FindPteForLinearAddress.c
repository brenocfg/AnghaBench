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
typedef  int ULONG ;
typedef  int* PULONG ;
typedef  scalar_t__ PEPROCESS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int* ADDR_TO_PDE (int) ; 
 int* ADDR_TO_PTE (int) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IoGetCurrentProcess () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int _PAGE_4M ; 
 int _PAGE_PRESENT ; 
 int _PAGE_SIZE ; 

PULONG FindPteForLinearAddress(ULONG address)
{
	PULONG pPGD;
	PULONG pPTE;
	BOOLEAN bResult = FALSE;
	PEPROCESS my_current = IoGetCurrentProcess();

    ENTER_FUNC();

	address &= (~(_PAGE_SIZE-1));

	if(my_current)
	{
		pPGD = ADDR_TO_PDE(address);
        if(pPGD && ((*pPGD)&_PAGE_PRESENT))
        {
            // not large page
            if(!((*pPGD)&_PAGE_4M))
			{
				pPTE = ADDR_TO_PTE(address);
				if(pPTE)
				{
                    LEAVE_FUNC();
					return pPTE;
				}
			}
			// large page
			else
			{
                LEAVE_FUNC();
				return NULL;
			}
		}
	}

    LEAVE_FUNC();
	return NULL;
}