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
typedef  int BOOLEAN ;

/* Variables and functions */
 int* ADDR_TO_PDE (int) ; 
 int* ADDR_TO_PTE (int) ; 
 int FALSE ; 
 int TRUE ; 
 int _PAGE_4M ; 
 int _PAGE_PRESENT ; 
 int _PAGE_PSE ; 
 int _PAGE_SIZE ; 

BOOLEAN IsAddressValid(ULONG address)
{
	PULONG pPGD;
	PULONG pPTE;
	BOOLEAN bResult = FALSE;

	address &= (~(_PAGE_SIZE-1));

	pPGD = ADDR_TO_PDE(address);
    if(pPGD && ((*pPGD)&_PAGE_PRESENT))
    {
        // not large page
        if(!((*pPGD)&_PAGE_4M))
		{
			pPTE = ADDR_TO_PTE(address);
			if(pPTE)
			{
				bResult = (*pPTE)&(_PAGE_PRESENT | _PAGE_PSE);
			}
		}
		// large page
		else
		{
			bResult = TRUE;
		}
	}

	return bResult;
}