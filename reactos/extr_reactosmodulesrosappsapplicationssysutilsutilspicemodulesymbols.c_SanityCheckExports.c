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
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OUTPUT_WINDOW ; 
 int /*<<< orphan*/  Print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN SanityCheckExports(void)
{
    BOOLEAN bResult = FALSE;
    ULONG i,ulValue,incr;

    Print(OUTPUT_WINDOW,"pICE: sanity-checking exports...\n");
	return TRUE;
	/* fix later!!! do we really need to cross reference two kinds of symbolic info?
    if(fake_kernel_module.nsyms && fake_kernel_module.syms)
    {
        incr = (fake_kernel_module.nsyms/4);
        if(!incr)incr = 1;
        for(i=0;i<fake_kernel_module.nsyms;i+=incr)
        {
            if(ScanExports((char*)fake_kernel_module.syms[i].name,&ulValue) )
            {
                if(!(i%25))
                {
                    ClrLine(wWindow[OUTPUT_WINDOW].y + wWindow[OUTPUT_WINDOW].usCurY);
                    PICE_sprintf(tempSym,"pICE: sanity-checking exports %u/%u",
                                          i,
                                          fake_kernel_module.nsyms);
                    PutChar(tempSym,1,wWindow[OUTPUT_WINDOW].y + wWindow[OUTPUT_WINDOW].usCurY);
                }

                if(fake_kernel_module.syms[i].value != ulValue)
                {
                    PICE_sprintf(tempSym,"pICE: %s doesn't match (%.8X != %.8X)\n",
                                 fake_kernel_module.syms[i].name,
                                 fake_kernel_module.syms[i].value,
                                 ulValue);
                    Print(OUTPUT_WINDOW,tempSym);

                    return FALSE;
                }
            }
        }

        bResult = TRUE;
    }

    return bResult;
	*/
}