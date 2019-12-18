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
typedef  int UINT ;
typedef  char TCHAR ;
typedef  scalar_t__ HINSTANCE ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DisplayEntryPoint (scalar_t__,char*) ; 
 int /*<<< orphan*/  DisplayVersion (scalar_t__,char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetModuleFileName (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ LoadLibraryA (char*) ; 
 int /*<<< orphan*/  PrintWin32Error (char*,int) ; 
 int _MAX_PATH ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

int
main(
	int	argc,
	char *	argv []
	)
{
	HINSTANCE	dll;
	TCHAR		ModuleName [_MAX_PATH];

	if (argc < 2)
	{
		fprintf(
			stderr,
			"\
ReactOS System Tools\n\
Check a Dynamic Link Library (DLL) for loading\n\
Copyright (c) 1998, 1999 Emanuele Aliberti\n\n\
usage: %s module [symbol [, ...]]\n",
			argv[0]
			);
		exit(EXIT_FAILURE);
	}
	dll = LoadLibraryA(argv[1]);
	if (!dll)
	{
		UINT    LastError;

		LastError = GetLastError();
		PrintWin32Error(L"LoadLibrary",LastError);
		fprintf(
			stderr,
			"%s: loading %s failed (%d).\n",
			argv[0],
			argv[1],
			LastError
			);
		exit(EXIT_FAILURE);
	}
	GetModuleFileName(
		(HANDLE) dll,
		ModuleName,
		sizeof ModuleName
		);
	printf(
		"%s loaded.\n",
		ModuleName
		);
#ifdef DISPLAY_VERSION
	DisplayVersion(dll,ModuleName);
#endif
	if (argc > 2)
	{
		int	CurrentSymbol;

		for (	CurrentSymbol = 2;
			(CurrentSymbol < argc);
			++CurrentSymbol
			)
		{
			DisplayEntryPoint( dll, argv[CurrentSymbol] );
		}
	}
	FreeLibrary(dll);
	printf(
		"%s unloaded.\n",
		ModuleName
		);
	return EXIT_SUCCESS;
}