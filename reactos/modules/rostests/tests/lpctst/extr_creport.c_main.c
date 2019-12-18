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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/ * HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreatePort ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * LoadLibrary (char*) ; 
 int /*<<< orphan*/ * QueryObject ; 
 int /*<<< orphan*/  TryCreatePort (char*) ; 
 int /*<<< orphan*/ * YieldExecution ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

main( int argc, char * argv[] )
{
	HINSTANCE ntdll;

	if (argc != 2)
	{
		printf("WNT LPC Port Creator\n");
		printf("Usage: %s [port_name]\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("LoadLibrary(NTDLL)\n");
	ntdll = LoadLibrary("NTDLL");
	if (ntdll == NULL)
	{
		printf("Could not load NTDLL\n");
		return EXIT_FAILURE;
	}
	printf("GetProcAddress(NTDLL.NtCreatePort)\n");
	CreatePort = (VOID*) GetProcAddress(
					ntdll,
					"NtCreatePort"
					);
	if (CreatePort == NULL)
	{
		FreeLibrary(ntdll);
		printf("Could not find NTDLL.NtCreatePort\n");
		return EXIT_FAILURE;
	}
	printf("GetProcAddress(NTDLL.NtQueryObject)\n");
	QueryObject = (VOID*) GetProcAddress(
					ntdll,
					"NtQueryObject"
					);
	if (QueryObject == NULL)
	{
		FreeLibrary(ntdll);
		printf("Could not find NTDLL.NtQueryObject\n");
		return EXIT_FAILURE;
	}
	printf("GetProcAddress(NTDLL.NtYieldExecution)\n");
	YieldExecution = (VOID*) GetProcAddress(
					ntdll,
					"NtYieldExecution"
					);
	if (YieldExecution == NULL)
	{
		FreeLibrary(ntdll);
		printf("Could not find NTDLL.NtYieldExecution\n");
		return EXIT_FAILURE;
	}
	printf("TryCreatePort(%s)\n",argv[1]);
	TryCreatePort(argv[1]);
	printf("Done\n");
	return EXIT_SUCCESS;
}