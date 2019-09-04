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
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SYMOPT_ALLOW_ABSOLUTE_SYMBOLS ; 
 int SYMOPT_DEFERRED_LOADS ; 
 int SymGetOptions () ; 
 int /*<<< orphan*/  SymInitialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SymSetOptions (int) ; 
 int /*<<< orphan*/  SymSetSearchPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL InitDbgHelp(HANDLE hProcess, LPSTR pszSymbolPath)
{
	if (!SymInitialize(hProcess, 0, FALSE))
		return FALSE;

	SymSetOptions(SymGetOptions() | SYMOPT_ALLOW_ABSOLUTE_SYMBOLS);
	SymSetOptions(SymGetOptions() & (~SYMOPT_DEFERRED_LOADS));
	SymSetSearchPath(hProcess, pszSymbolPath);
	return TRUE;
}