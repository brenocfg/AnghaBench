#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dwFileAttributes; int /*<<< orphan*/  cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATA ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BeSilent ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 int /*<<< orphan*/  FindExInfoStandard ; 
 int /*<<< orphan*/  FindExSearchLimitToDirectories ; 
 scalar_t__ FindFirstFileEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FindNextFile (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ProcessFiles (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcscat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ _tcscmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

BOOL
ProcessDirectories(LPTSTR Path)
{
  WIN32_FIND_DATA FindFile;
  TCHAR SearchPath[MAX_PATH];
  HANDLE SearchHandle;
  BOOL More;

  if(!BeSilent)
  {
    _tprintf (_T("Processing %s ...\n"), Path);
  }

  _tcscpy (SearchPath, Path);
  _tcscat (SearchPath, _T("\\*.*"));

  SearchHandle = FindFirstFileEx (SearchPath,
    FindExInfoStandard,
    &FindFile,
    FindExSearchLimitToDirectories,
    NULL,
    0);
  if (SearchHandle != INVALID_HANDLE_VALUE)
  {
    More = TRUE;
    while (More)
    {
	    if ((FindFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      && (_tcscmp (FindFile.cFileName, _T(".")) != 0)
      && (_tcscmp (FindFile.cFileName, _T("..")) != 0)
      && (_tcscmp (FindFile.cFileName, _T("CVS")) != 0)
      && (_tcscmp (FindFile.cFileName, _T(".svn")) != 0))
			{
			  _tcscpy (SearchPath, Path);
			  _tcscat (SearchPath, _T("\\"));
			  _tcscat (SearchPath, FindFile.cFileName);
	      if (!ProcessDirectories (SearchPath))
          return FALSE;
	      if (!ProcessFiles (SearchPath))
          return FALSE;
			}
      More = FindNextFile (SearchHandle, &FindFile);
    }
    FindClose (SearchHandle);
  }
  return TRUE;
}