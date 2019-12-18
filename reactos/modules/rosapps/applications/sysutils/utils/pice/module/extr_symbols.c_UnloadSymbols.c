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
typedef  size_t ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  PICE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** apSymbols ; 
 size_t ulNumSymbolsLoaded ; 

void UnloadSymbols()
{
    ULONG i;

	ENTER_FUNC();

    if(ulNumSymbolsLoaded)
	{
        for(i=0;i<ulNumSymbolsLoaded;i++)
        {
    		DPRINT((0,"freeing [%u] %x\n",i,apSymbols[i]));
	    	PICE_free(apSymbols[i]);
            apSymbols[i] = NULL;
        }
        ulNumSymbolsLoaded = 0;
	}
    LEAVE_FUNC();
}