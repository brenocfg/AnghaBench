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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int* PULONG ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int* ADDR_TO_PDE (int /*<<< orphan*/ ) ; 
 int* ADDR_TO_PTE (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FLUSH_TLB ; 
 scalar_t__ TRUE ; 
 int _PAGE_4M ; 
 int _PAGE_PRESENT ; 
 int _PAGE_PSE ; 
 int _PAGE_RW ; 

BOOLEAN SetAddressWriteable(ULONG address,BOOLEAN bSet)
{
	PULONG pPGD;
	PULONG pPTE;

	//address &= (~(_PAGE_SIZE-1));

	pPGD = ADDR_TO_PDE(address);
    if(pPGD && ((*pPGD)&_PAGE_PRESENT))
    {
        // not large page
        if(!((*pPGD)&_PAGE_4M))
		{
			pPTE = ADDR_TO_PTE(address);
			if(pPTE)
			{
				if( (*pPTE)&(_PAGE_PRESENT | _PAGE_PSE) )
				{
                    if( bSet ){
						*pPTE |= _PAGE_RW;
					}
                    else{
						*pPTE &= ~_PAGE_RW;
					}
					FLUSH_TLB;
					return TRUE;
                }
			}
		}
		// large page
		else
		{
            if( bSet )
                *pPGD |= _PAGE_RW;
            else
                *pPGD &= ~_PAGE_RW;
			FLUSH_TLB;
            return TRUE;
		}
	}
	return FALSE;
}