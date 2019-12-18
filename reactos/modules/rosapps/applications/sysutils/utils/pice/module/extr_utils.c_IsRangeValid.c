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
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IsAddressValid (int) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  TRUE ; 
 int _PAGE_SIZE ; 

BOOLEAN IsRangeValid(ULONG Addr,ULONG Length)
{
ULONG i,NumPages,PageNum;

	// need to only touch one byte per page
	// calculate PICE_number of pages to touch
	NumPages=(Length+(_PAGE_SIZE-1))>>12;

	// calculate PICE_number of page
	PageNum=Addr>>PAGE_SHIFT;

	// touch all pages containing range
	for(i=0;i<NumPages;i++)
	{
		// if any one page is invalid range is invalid
		if(!IsAddressValid((ULONG)((PageNum+i)*_PAGE_SIZE)) )
			return FALSE;
	}

	return TRUE;
}