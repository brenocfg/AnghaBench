#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG_PTR ;
typedef  scalar_t__ ULONGLONG ;
typedef  int ULONG ;
struct TYPE_3__ {int DllBase; char BaseDllName; int /*<<< orphan*/  SizeOfImage; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PLDR_DATA_TABLE_ENTRY ;
typedef  char* PCHAR ;
typedef  int INT ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KdbpEvaluateExpression (char*,int,scalar_t__*) ; 
 int /*<<< orphan*/  KdbpPrint (char*,...) ; 
 int /*<<< orphan*/  KdbpSymFindModule (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__**) ; 
 scalar_t__ TRUE ; 
 size_t strlen (char*) ; 

__attribute__((used)) static BOOLEAN
KdbpCmdMod(
    ULONG Argc,
    PCHAR Argv[])
{
    ULONGLONG Result = 0;
    ULONG_PTR Address;
    PLDR_DATA_TABLE_ENTRY LdrEntry;
    BOOLEAN DisplayOnlyOneModule = FALSE;
    INT i = 0;

    if (Argc >= 2)
    {
        /* Put the arguments back together */
        Argc--;
        while (--Argc >= 1)
            Argv[Argc][strlen(Argv[Argc])] = ' ';

        /* Evaluate the expression */
        if (!KdbpEvaluateExpression(Argv[1], sizeof("kdb:> ")-1 + (Argv[1]-Argv[0]), &Result))
        {
            return TRUE;
        }

        if (Result > (ULONGLONG)(~((ULONG_PTR)0)))
            KdbpPrint("%s: Warning: Address %I64x is beeing truncated\n", Argv[0],Result);

        Address = (ULONG_PTR)Result;

        if (!KdbpSymFindModule((PVOID)Address, NULL, -1, &LdrEntry))
        {
            KdbpPrint("No module containing address 0x%p found!\n", Address);
            return TRUE;
        }

        DisplayOnlyOneModule = TRUE;
    }
    else
    {
        if (!KdbpSymFindModule(NULL, NULL, 0, &LdrEntry))
        {
            ULONG_PTR ntoskrnlBase = ((ULONG_PTR)KdbpCmdMod) & 0xfff00000;
            KdbpPrint("  Base      Size      Name\n");
            KdbpPrint("  %08x  %08x  %s\n", ntoskrnlBase, 0, "ntoskrnl.exe");
            return TRUE;
        }

        i = 1;
    }

    KdbpPrint("  Base      Size      Name\n");
    for (;;)
    {
        KdbpPrint("  %08x  %08x  %wZ\n", LdrEntry->DllBase, LdrEntry->SizeOfImage, &LdrEntry->BaseDllName);

        if(DisplayOnlyOneModule || !KdbpSymFindModule(NULL, NULL, i++, &LdrEntry))
            break;
    }

    return TRUE;
}