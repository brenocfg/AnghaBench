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
typedef  scalar_t__* PUCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgPrint (char*) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  NONPAGEDPOOL ; 
 int /*<<< orphan*/  OF_READ ; 
 int /*<<< orphan*/  OUTPUT_WINDOW ; 
 int /*<<< orphan*/  PICE_close (scalar_t__) ; 
 size_t PICE_len (scalar_t__) ; 
 scalar_t__ PICE_malloc (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ PICE_open (char*,int /*<<< orphan*/ ) ; 
 size_t PICE_read (scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  PICE_sprintf (char*,char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  Print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ pExports ; 
 char* tempSym ; 
 size_t ulExportLen ; 

BOOLEAN LoadExports(void)
{
	HANDLE hf;
    BOOLEAN bResult = TRUE;

	ENTER_FUNC();

    Print(OUTPUT_WINDOW,"pICE: loading exports...\n");
	hf = PICE_open(L"\\SystemRoot\\symbols\\ntoskrnl.map",OF_READ);
	/*
	if(hf)
    {
        Print(OUTPUT_WINDOW,"pICE: no System.map in /boot\n");
	    hf = PICE_open("/System.map",OF_READ);
    }
	*/

    if(hf)
	{
		//mm_segment_t oldfs;
		size_t len;

		len = PICE_len(hf);
        if(len)
        {
		    DPRINT((0,"file len = %d\n",len));

		    pExports = PICE_malloc(len+1,NONPAGEDPOOL);  // maybe make pool setting an option

		    DPRINT((0,"pExports = %x\n",pExports));

            if(pExports)
		    {
        		//oldfs = get_fs(); set_fs(KERNEL_DS);
                ulExportLen = len;
			    ((PUCHAR)pExports)[len]=0;
			    if(len == PICE_read(hf,pExports,len))
			    {
				    DPRINT((0,"success reading system map!\n"));
            		PICE_sprintf(tempSym,"pICE: ntoskrnl.sym @ %x (size %x)\n",pExports,len);
		    		Print(OUTPUT_WINDOW,tempSym);
				}
				else
					DbgPrint("error reading ntoskrnl map!\n");
    		    //set_fs(oldfs);
		    }
        }
		PICE_close(hf);
	}
    else
    {
        Print(OUTPUT_WINDOW,"pICE: no ntoskrnl.sys \n");
        Print(OUTPUT_WINDOW,"pICE: could not load exports...\n");
        bResult = FALSE;
    }

    LEAVE_FUNC();

    return bResult;
}