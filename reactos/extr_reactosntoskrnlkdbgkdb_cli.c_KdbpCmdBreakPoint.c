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
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONGLONG ;
typedef  int ULONG ;
typedef  int UCHAR ;
typedef  char* PCHAR ;
typedef  size_t LONG ;
typedef  int /*<<< orphan*/  KDB_BREAKPOINT_TYPE ;
typedef  scalar_t__ KDB_ACCESS_TYPE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ KdbAccessExec ; 
 scalar_t__ KdbAccessRead ; 
 scalar_t__ KdbAccessReadWrite ; 
 scalar_t__ KdbAccessWrite ; 
 int /*<<< orphan*/  KdbBreakPointHardware ; 
 int /*<<< orphan*/  KdbBreakPointSoftware ; 
 int /*<<< orphan*/  KdbpEvaluateExpression (char*,int,scalar_t__*) ; 
 int /*<<< orphan*/  KdbpInsertBreakPoint (scalar_t__,int /*<<< orphan*/ ,int,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KdbpPrint (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _stricmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static BOOLEAN
KdbpCmdBreakPoint(ULONG Argc, PCHAR Argv[])
{
    ULONGLONG Result = 0;
    ULONG_PTR Address;
    KDB_BREAKPOINT_TYPE Type;
    UCHAR Size = 0;
    KDB_ACCESS_TYPE AccessType = 0;
    ULONG AddressArgIndex, i;
    LONG ConditionArgIndex;
    BOOLEAN Global = TRUE;

    if (Argv[0][2] == 'x') /* software breakpoint */
    {
        if (Argc < 2)
        {
            KdbpPrint("bpx: Address argument required.\n");
            return TRUE;
        }

        AddressArgIndex = 1;
        Type = KdbBreakPointSoftware;
    }
    else /* memory breakpoint */
    {
        ASSERT(Argv[0][2] == 'm');

        if (Argc < 2)
        {
            KdbpPrint("bpm: Access type argument required (one of r, w, rw, x)\n");
            return TRUE;
        }

        if (_stricmp(Argv[1], "x") == 0)
            AccessType = KdbAccessExec;
        else if (_stricmp(Argv[1], "r") == 0)
            AccessType = KdbAccessRead;
        else if (_stricmp(Argv[1], "w") == 0)
            AccessType = KdbAccessWrite;
        else if (_stricmp(Argv[1], "rw") == 0)
            AccessType = KdbAccessReadWrite;
        else
        {
            KdbpPrint("bpm: Unknown access type '%s'\n", Argv[1]);
            return TRUE;
        }

        if (Argc < 3)
        {
            KdbpPrint("bpm: %s argument required.\n", AccessType == KdbAccessExec ? "Address" : "Memory size");
            return TRUE;
        }

        AddressArgIndex = 3;
        if (_stricmp(Argv[2], "byte") == 0)
            Size = 1;
        else if (_stricmp(Argv[2], "word") == 0)
            Size = 2;
        else if (_stricmp(Argv[2], "dword") == 0)
            Size = 4;
        else if (AccessType == KdbAccessExec)
        {
            Size = 1;
            AddressArgIndex--;
        }
        else
        {
            KdbpPrint("bpm: Unknown memory size '%s'\n", Argv[2]);
            return TRUE;
        }

        if (Argc <= AddressArgIndex)
        {
            KdbpPrint("bpm: Address argument required.\n");
            return TRUE;
        }

        Type = KdbBreakPointHardware;
    }

    /* Put the arguments back together */
    ConditionArgIndex = -1;
    for (i = AddressArgIndex; i < (Argc-1); i++)
    {
        if (strcmp(Argv[i+1], "IF") == 0) /* IF found */
        {
            ConditionArgIndex = i + 2;
            if ((ULONG)ConditionArgIndex >= Argc)
            {
                KdbpPrint("%s: IF requires condition expression.\n", Argv[0]);
                return TRUE;
            }

            for (i = ConditionArgIndex; i < (Argc-1); i++)
                Argv[i][strlen(Argv[i])] = ' ';

            break;
        }

        Argv[i][strlen(Argv[i])] = ' ';
    }

    /* Evaluate the address expression */
    if (!KdbpEvaluateExpression(Argv[AddressArgIndex],
                                sizeof("kdb:> ")-1 + (Argv[AddressArgIndex]-Argv[0]),
                                &Result))
    {
        return TRUE;
    }

    if (Result > (ULONGLONG)(~((ULONG_PTR)0)))
        KdbpPrint("%s: Warning: Address %I64x is beeing truncated\n", Argv[0],Result);

    Address = (ULONG_PTR)Result;

    KdbpInsertBreakPoint(Address, Type, Size, AccessType,
                         (ConditionArgIndex < 0) ? NULL : Argv[ConditionArgIndex],
                         Global, NULL);

    return TRUE;
}