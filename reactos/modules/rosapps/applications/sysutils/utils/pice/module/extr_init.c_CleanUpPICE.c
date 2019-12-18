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

/* Variables and functions */
 int /*<<< orphan*/  ConsoleShutdown () ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeInstallDblFltHook () ; 
 int /*<<< orphan*/  DeInstallGPFaultHook () ; 
 int /*<<< orphan*/  DeInstallGlobalKeyboardHook () ; 
 int /*<<< orphan*/  DeInstallInt3Hook () ; 
 int /*<<< orphan*/  DeInstallIntEHook () ; 
 int /*<<< orphan*/  DeInstallPrintkHook () ; 
 int /*<<< orphan*/  DeInstallSyscallHook () ; 
 int /*<<< orphan*/  DeInstallTraceHook () ; 
 int /*<<< orphan*/  OUTPUT_WINDOW ; 
 int /*<<< orphan*/  Print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RemovePiceRunningTimer () ; 
 int /*<<< orphan*/  RestoreIdt () ; 
 int /*<<< orphan*/  RestoreKeyboardDriver () ; 
 int /*<<< orphan*/  UnloadExports () ; 
 int /*<<< orphan*/  UnloadSymbols () ; 

void CleanUpPICE(void)
{
    DPRINT((0,"CleanUpPICE(): trace step 1\n"));
	RemovePiceRunningTimer();

    DPRINT((0,"CleanUpPICE(): trace step 2\n"));
    // de-install all hooks
    DeInstallGlobalKeyboardHook();
    DeInstallSyscallHook();
    DeInstallInt3Hook();
    DeInstallPrintkHook();
    DeInstallDblFltHook();
    DeInstallGPFaultHook();
    DeInstallIntEHook();
    DeInstallTraceHook();

    DPRINT((0,"CleanUpPICE(): trace step 3\n"));
    RestoreIdt();

    DPRINT((0,"CleanUpPICE(): trace step 4\n"));
    UnloadExports(); // don't use ScanExports() after this
    UnloadSymbols();

    DPRINT((0,"CleanUpPICE(): trace step 5\n"));
    // restore patch of keyboard driver
    RestoreKeyboardDriver();

    DPRINT((0,"CleanUpPICE(): trace step 6\n"));
    Print(OUTPUT_WINDOW,"pICE: shutting down...\n");

    DPRINT((0,"CleanUpPICE(): trace step 7\n"));
    // cleanup the console
	ConsoleShutdown();
}