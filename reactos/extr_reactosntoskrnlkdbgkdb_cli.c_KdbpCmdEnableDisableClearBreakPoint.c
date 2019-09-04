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
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KdbpDeleteBreakPoint (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KdbpDisableBreakPoint (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KdbpEnableBreakPoint (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KdbpPrint (char*,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN
KdbpCmdEnableDisableClearBreakPoint(
    ULONG Argc,
    PCHAR Argv[])
{
    PCHAR pend;
    ULONG BreakPointNr;

    if (Argc < 2)
    {
        KdbpPrint("%s: argument required\n", Argv[0]);
        return TRUE;
    }

    pend = Argv[1];
    BreakPointNr = strtoul(Argv[1], &pend, 0);
    if (pend == Argv[1] || *pend != '\0')
    {
        KdbpPrint("%s: integer argument required\n", Argv[0]);
        return TRUE;
    }

    if (Argv[0][1] == 'e') /* enable */
    {
        KdbpEnableBreakPoint(BreakPointNr, NULL);
    }
    else if (Argv [0][1] == 'd') /* disable */
    {
        KdbpDisableBreakPoint(BreakPointNr, NULL);
    }
    else /* clear */
    {
        ASSERT(Argv[0][1] == 'c');
        KdbpDeleteBreakPoint(BreakPointNr, NULL);
    }

    return TRUE;
}