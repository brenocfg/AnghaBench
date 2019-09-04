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
typedef  char* PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int KdbNumSingleSteps ; 
 int /*<<< orphan*/  KdbSingleStepOver ; 
 int /*<<< orphan*/  KdbpPrint (char*,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN
KdbpCmdStep(
    ULONG Argc,
    PCHAR Argv[])
{
    ULONG Count = 1;

    if (Argc > 1)
    {
        Count = strtoul(Argv[1], NULL, 0);
        if (Count == 0)
        {
            KdbpPrint("%s: Integer argument required\n", Argv[0]);
            return TRUE;
        }
    }

    if (Argv[0][0] == 'n')
        KdbSingleStepOver = TRUE;
    else
        KdbSingleStepOver = FALSE;

    /* Set the number of single steps and return to the interrupted code. */
    KdbNumSingleSteps = Count;

    return FALSE;
}