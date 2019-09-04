#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG_PTR ;
typedef  scalar_t__ ULONGLONG ;
typedef  int ULONG ;
struct TYPE_5__ {int Ebp; int Eip; } ;
struct TYPE_6__ {TYPE_1__ Tf; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  char* PCHAR ;
typedef  TYPE_1__ KTRAP_FRAME ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 TYPE_4__* KdbCurrentTrapFrame ; 
 scalar_t__ KdbOutputAborted ; 
 int /*<<< orphan*/  KdbSymPrintAddress (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  KdbpEvaluateExpression (char*,int,scalar_t__*) ; 
 scalar_t__ KdbpInNmiOrDoubleFaultHandler (int) ; 
 int /*<<< orphan*/  KdbpPrint (char*,...) ; 
 int /*<<< orphan*/  KdbpSafeReadMemory (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ KdbpTrapFrameFromPrevTss (TYPE_1__*) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN
KdbpCmdBackTrace(
    ULONG Argc,
    PCHAR Argv[])
{
    ULONG ul;
    ULONGLONG Result = 0;
    ULONG_PTR Frame = KdbCurrentTrapFrame->Tf.Ebp;
    ULONG_PTR Address;
    KTRAP_FRAME TrapFrame;

    if (Argc >= 2)
    {
        /* Check for [L count] part */
        ul = 0;

        if (strcmp(Argv[Argc-2], "L") == 0)
        {
            ul = strtoul(Argv[Argc-1], NULL, 0);
            if (ul > 0)
            {
                Argc -= 2;
            }
        }
        else if (Argv[Argc-1][0] == 'L')
        {
            ul = strtoul(Argv[Argc-1] + 1, NULL, 0);
            if (ul > 0)
            {
                Argc--;
            }
        }

        /* Put the remaining arguments back together */
        Argc--;
        for (ul = 1; ul < Argc; ul++)
        {
            Argv[ul][strlen(Argv[ul])] = ' ';
        }
        Argc++;
    }

    /* Check if frame addr or thread id is given. */
    if (Argc > 1)
    {
        if (Argv[1][0] == '*')
        {
            Argv[1]++;

            /* Evaluate the expression */
            if (!KdbpEvaluateExpression(Argv[1], sizeof("kdb:> ")-1 + (Argv[1]-Argv[0]), &Result))
                return TRUE;

            if (Result > (ULONGLONG)(~((ULONG_PTR)0)))
                KdbpPrint("Warning: Address %I64x is beeing truncated\n",Result);

            Frame = (ULONG_PTR)Result;
        }
        else
        {
            KdbpPrint("Thread backtrace not supported yet!\n");
            return TRUE;
        }
    }
    else
    {
        KdbpPrint("Eip:\n");

        /* Try printing the function at EIP */
        if (!KdbSymPrintAddress((PVOID)KdbCurrentTrapFrame->Tf.Eip, &KdbCurrentTrapFrame->Tf))
            KdbpPrint("<%08x>\n", KdbCurrentTrapFrame->Tf.Eip);
        else
            KdbpPrint("\n");
    }

    TrapFrame = KdbCurrentTrapFrame->Tf;
    KdbpPrint("Frames:\n");

    for (;;)
    {
        BOOLEAN GotNextFrame;

        if (Frame == 0)
            break;

        if (!NT_SUCCESS(KdbpSafeReadMemory(&Address, (PVOID)(Frame + sizeof(ULONG_PTR)), sizeof (ULONG_PTR))))
        {
            KdbpPrint("Couldn't access memory at 0x%p!\n", Frame + sizeof(ULONG_PTR));
            break;
        }

        if ((GotNextFrame = NT_SUCCESS(KdbpSafeReadMemory(&Frame, (PVOID)Frame, sizeof (ULONG_PTR)))))
            TrapFrame.Ebp = Frame;

        /* Print the location of the call instruction */
        if (!KdbSymPrintAddress((PVOID)(Address - 5), &TrapFrame))
            KdbpPrint("<%08x>\n", Address);
        else
            KdbpPrint("\n");

        if (KdbOutputAborted) break;

        if (Address == 0)
            break;

        if (KdbpInNmiOrDoubleFaultHandler(Address))
        {
            if ((GotNextFrame = KdbpTrapFrameFromPrevTss(&TrapFrame)))
            {
                Address = TrapFrame.Eip;
                Frame = TrapFrame.Ebp;

                if (!KdbSymPrintAddress((PVOID)Address, &TrapFrame))
                    KdbpPrint("<%08x>\n", Address);
                else
                    KdbpPrint("\n");
            }
        }

        if (!GotNextFrame)
        {
            KdbpPrint("Couldn't access memory at 0x%p!\n", Frame);
            break;
        }
    }

    return TRUE;
}