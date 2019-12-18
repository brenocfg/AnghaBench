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
typedef  int LONG ;
typedef  int /*<<< orphan*/  KDB_ENTER_CONDITION ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int FALSE ; 
 int /*<<< orphan*/  KDB_ENTER_CONDITION_TO_STRING (int /*<<< orphan*/ ) ; 
 int KdbBreakOnModuleLoad ; 
 int /*<<< orphan*/  KdbDoNotEnter ; 
 int /*<<< orphan*/  KdbEnterAlways ; 
 int /*<<< orphan*/  KdbEnterFromKmode ; 
 int /*<<< orphan*/  KdbEnterFromUmode ; 
 int KdbUseIntelSyntax ; 
 int /*<<< orphan*/  KdbpGetEnterCondition (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KdbpPrint (char*,...) ; 
 int /*<<< orphan*/  KdbpSetEnterCondition (int,int,int /*<<< orphan*/ ) ; 
 int RTL_NUMBER_OF (char* const*) ; 
 int TRUE ; 
 scalar_t__ _stricmp (char* const,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN
KdbpCmdSet(
    ULONG Argc,
    PCHAR Argv[])
{
    LONG l;
    BOOLEAN First;
    PCHAR pend = 0;
    KDB_ENTER_CONDITION ConditionFirst = KdbDoNotEnter;
    KDB_ENTER_CONDITION ConditionLast = KdbDoNotEnter;

    static const PCHAR ExceptionNames[21] =
    {
        "ZERODEVIDE", "DEBUGTRAP", "NMI", "INT3", "OVERFLOW", "BOUND", "INVALIDOP",
        "NOMATHCOP", "DOUBLEFAULT", "RESERVED(9)", "INVALIDTSS", "SEGMENTNOTPRESENT",
        "STACKFAULT", "GPF", "PAGEFAULT", "RESERVED(15)", "MATHFAULT", "ALIGNMENTCHECK",
        "MACHINECHECK", "SIMDFAULT", "OTHERS"
    };

    if (Argc == 1)
    {
        KdbpPrint("Available settings:\n");
        KdbpPrint("  syntax [intel|at&t]\n");
        KdbpPrint("  condition [exception|*] [first|last] [never|always|kmode|umode]\n");
        KdbpPrint("  break_on_module_load [true|false]\n");
    }
    else if (strcmp(Argv[1], "syntax") == 0)
    {
        if (Argc == 2)
        {
            KdbpPrint("syntax = %s\n", KdbUseIntelSyntax ? "intel" : "at&t");
        }
        else if (Argc >= 3)
        {
            if (_stricmp(Argv[2], "intel") == 0)
                KdbUseIntelSyntax = TRUE;
            else if (_stricmp(Argv[2], "at&t") == 0)
                KdbUseIntelSyntax = FALSE;
            else
                KdbpPrint("Unknown syntax '%s'.\n", Argv[2]);
        }
    }
    else if (strcmp(Argv[1], "condition") == 0)
    {
        if (Argc == 2)
        {
            KdbpPrint("Conditions:                 (First)  (Last)\n");
            for (l = 0; l < RTL_NUMBER_OF(ExceptionNames) - 1; l++)
            {
                if (!ExceptionNames[l])
                    continue;

                if (!KdbpGetEnterCondition(l, TRUE, &ConditionFirst))
                    ASSERT(FALSE);

                if (!KdbpGetEnterCondition(l, FALSE, &ConditionLast))
                    ASSERT(FALSE);

                KdbpPrint("  #%02d  %-20s %-8s %-8s\n", l, ExceptionNames[l],
                          KDB_ENTER_CONDITION_TO_STRING(ConditionFirst),
                          KDB_ENTER_CONDITION_TO_STRING(ConditionLast));
            }

            ASSERT(l == (RTL_NUMBER_OF(ExceptionNames) - 1));
            KdbpPrint("       %-20s %-8s %-8s\n", ExceptionNames[l],
                      KDB_ENTER_CONDITION_TO_STRING(ConditionFirst),
                      KDB_ENTER_CONDITION_TO_STRING(ConditionLast));
        }
        else
        {
            if (Argc >= 5 && strcmp(Argv[2], "*") == 0) /* Allow * only when setting condition */
            {
                l = -1;
            }
            else
            {
                l = strtoul(Argv[2], &pend, 0);

                if (Argv[2] == pend)
                {
                    for (l = 0; l < RTL_NUMBER_OF(ExceptionNames); l++)
                    {
                        if (!ExceptionNames[l])
                            continue;

                        if (_stricmp(ExceptionNames[l], Argv[2]) == 0)
                            break;
                    }
                }

                if (l >= RTL_NUMBER_OF(ExceptionNames))
                {
                    KdbpPrint("Unknown exception '%s'.\n", Argv[2]);
                    return TRUE;
                }
            }

            if (Argc > 4)
            {
                if (_stricmp(Argv[3], "first") == 0)
                    First = TRUE;
                else if (_stricmp(Argv[3], "last") == 0)
                    First = FALSE;
                else
                {
                    KdbpPrint("set condition: second argument must be 'first' or 'last'\n");
                    return TRUE;
                }

                if (_stricmp(Argv[4], "never") == 0)
                    ConditionFirst = KdbDoNotEnter;
                else if (_stricmp(Argv[4], "always") == 0)
                    ConditionFirst = KdbEnterAlways;
                else if (_stricmp(Argv[4], "umode") == 0)
                    ConditionFirst = KdbEnterFromUmode;
                else if (_stricmp(Argv[4], "kmode") == 0)
                    ConditionFirst = KdbEnterFromKmode;
                else
                {
                    KdbpPrint("set condition: third argument must be 'never', 'always', 'umode' or 'kmode'\n");
                    return TRUE;
                }

                if (!KdbpSetEnterCondition(l, First, ConditionFirst))
                {
                    if (l >= 0)
                        KdbpPrint("Couldn't change condition for exception #%02d\n", l);
                    else
                        KdbpPrint("Couldn't change condition for all exceptions\n", l);
                }
            }
            else /* Argc >= 3 */
            {
                if (!KdbpGetEnterCondition(l, TRUE, &ConditionFirst))
                    ASSERT(FALSE);

                if (!KdbpGetEnterCondition(l, FALSE, &ConditionLast))
                    ASSERT(FALSE);

                if (l < (RTL_NUMBER_OF(ExceptionNames) - 1))
                {
                    KdbpPrint("Condition for exception #%02d (%s): FirstChance %s  LastChance %s\n",
                              l, ExceptionNames[l],
                              KDB_ENTER_CONDITION_TO_STRING(ConditionFirst),
                              KDB_ENTER_CONDITION_TO_STRING(ConditionLast));
                }
                else
                {
                    KdbpPrint("Condition for all other exceptions: FirstChance %s  LastChance %s\n",
                              KDB_ENTER_CONDITION_TO_STRING(ConditionFirst),
                              KDB_ENTER_CONDITION_TO_STRING(ConditionLast));
                }
            }
        }
    }
    else if (strcmp(Argv[1], "break_on_module_load") == 0)
    {
        if (Argc == 2)
            KdbpPrint("break_on_module_load = %s\n", KdbBreakOnModuleLoad ? "enabled" : "disabled");
        else if (Argc >= 3)
        {
            if (_stricmp(Argv[2], "enable") == 0 || _stricmp(Argv[2], "enabled") == 0 || _stricmp(Argv[2], "true") == 0)
                KdbBreakOnModuleLoad = TRUE;
            else if (_stricmp(Argv[2], "disable") == 0 || _stricmp(Argv[2], "disabled") == 0 || _stricmp(Argv[2], "false") == 0)
                KdbBreakOnModuleLoad = FALSE;
            else
                KdbpPrint("Unknown setting '%s'.\n", Argv[2]);
        }
    }
    else
    {
        KdbpPrint("Unknown setting '%s'.\n", Argv[1]);
    }

    return TRUE;
}