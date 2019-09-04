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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int UCHAR ;
struct TYPE_3__ {scalar_t__ UniqueProcessId; } ;
typedef  TYPE_1__* PEPROCESS ;
typedef  char* PCHAR ;
typedef  scalar_t__ LONG ;
typedef  scalar_t__ KDB_BREAKPOINT_TYPE ;
typedef  int /*<<< orphan*/  KDB_ACCESS_TYPE ;
typedef  char CHAR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  KDB_ACCESS_TYPE_TO_STRING (int /*<<< orphan*/ ) ; 
 scalar_t__ KdbBreakPointHardware ; 
 scalar_t__ KdbBreakPointSoftware ; 
 scalar_t__ KdbBreakPointTemporary ; 
 scalar_t__ KdbLastBreakPointNr ; 
 int /*<<< orphan*/  KdbpGetBreakPointInfo (scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int*,int /*<<< orphan*/ *,int*,scalar_t__*,scalar_t__*,TYPE_1__**,char**) ; 
 scalar_t__ KdbpGetNextBreakPointNr (scalar_t__) ; 
 int /*<<< orphan*/  KdbpPrint (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN
KdbpCmdBreakPointList(
    ULONG Argc,
    PCHAR Argv[])
{
    LONG l;
    ULONG_PTR Address = 0;
    KDB_BREAKPOINT_TYPE Type = 0;
    KDB_ACCESS_TYPE AccessType = 0;
    UCHAR Size = 0;
    UCHAR DebugReg = 0;
    BOOLEAN Enabled = FALSE;
    BOOLEAN Global = FALSE;
    PEPROCESS Process = NULL;
    PCHAR str1, str2, ConditionExpr, GlobalOrLocal;
    CHAR Buffer[20];

    l = KdbpGetNextBreakPointNr(0);
    if (l < 0)
    {
        KdbpPrint("No breakpoints.\n");
        return TRUE;
    }

    KdbpPrint("Breakpoints:\n");
    do
    {
        if (!KdbpGetBreakPointInfo(l, &Address, &Type, &Size, &AccessType, &DebugReg,
                                   &Enabled, &Global, &Process, &ConditionExpr))
        {
            continue;
        }

        if (l == KdbLastBreakPointNr)
        {
            str1 = "\x1b[1m*";
            str2 = "\x1b[0m";
        }
        else
        {
            str1 = " ";
            str2 = "";
        }

        if (Global)
        {
            GlobalOrLocal = "  global";
        }
        else
        {
            GlobalOrLocal = Buffer;
            sprintf(Buffer, "  PID 0x%08lx",
                    (ULONG)(Process ? Process->UniqueProcessId : INVALID_HANDLE_VALUE));
        }

        if (Type == KdbBreakPointSoftware || Type == KdbBreakPointTemporary)
        {
            KdbpPrint(" %s%03d  BPX  0x%08x%s%s%s%s%s\n",
                      str1, l, Address,
                      Enabled ? "" : "  disabled",
                      GlobalOrLocal,
                      ConditionExpr ? "  IF " : "",
                      ConditionExpr ? ConditionExpr : "",
                      str2);
        }
        else if (Type == KdbBreakPointHardware)
        {
            if (!Enabled)
            {
                KdbpPrint(" %s%03d  BPM  0x%08x  %-5s %-5s  disabled%s%s%s%s\n", str1, l, Address,
                          KDB_ACCESS_TYPE_TO_STRING(AccessType),
                          Size == 1 ? "byte" : (Size == 2 ? "word" : "dword"),
                          GlobalOrLocal,
                          ConditionExpr ? "  IF " : "",
                          ConditionExpr ? ConditionExpr : "",
                          str2);
            }
            else
            {
                KdbpPrint(" %s%03d  BPM  0x%08x  %-5s %-5s  DR%d%s%s%s%s\n", str1, l, Address,
                          KDB_ACCESS_TYPE_TO_STRING(AccessType),
                          Size == 1 ? "byte" : (Size == 2 ? "word" : "dword"),
                          DebugReg,
                          GlobalOrLocal,
                          ConditionExpr ? "  IF " : "",
                          ConditionExpr ? ConditionExpr : "",
                          str2);
            }
        }
    }
    while ((l = KdbpGetNextBreakPointNr(l+1)) >= 0);

    return TRUE;
}