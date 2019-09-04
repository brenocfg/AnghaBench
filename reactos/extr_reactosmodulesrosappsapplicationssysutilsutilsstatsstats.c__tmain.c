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
typedef  int /*<<< orphan*/  _TCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* BeSilent ; 
 int /*<<< orphan*/  Cleanup () ; 
 int /*<<< orphan*/  Execute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Initialize () ; 
 void* IsOptionSet (int /*<<< orphan*/ ) ; 
 int MAX_OPTIONS ; 
 int /*<<< orphan*/ ** Options ; 
 void* SkipEmptyLines ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ) ; 

int _tmain(int argc, _TCHAR * argv[])
{
  int a;

  _tprintf (_T("ReactOS Project Statistics\n"));
  _tprintf (_T("==========================\n\n"));

  if (argc < 2 || argc > 2 + MAX_OPTIONS)
  {
    _tprintf(_T("Usage: stats [-e] [-s] directory\n"));
    _tprintf(_T("  -e: don't count empty lines\n"));
    _tprintf(_T("  -s: be silent, don't print directories while processing\n"));
    return 1;
  }

  Initialize();
  AddExtension (_T("c\0\0"), _T("Ansi C Source files"));
  AddExtension (_T("cpp\0cxx\0\0"), _T("C++ Source files"));
  AddExtension (_T("h\0\0"), _T("Header files"));

  for(a = 1; a < argc - 1; a++)
  {
    Options[a - 1] = argv[a];
  }

  SkipEmptyLines = IsOptionSet(_T("-e"));
  BeSilent = IsOptionSet(_T("-s"));

  Execute (argv[argc - 1]);
  Cleanup();

  return 0;
}