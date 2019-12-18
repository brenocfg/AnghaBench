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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FindFileName (int /*<<< orphan*/ ) ; 
 scalar_t__ ISDOTDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ IsRootDirectory (int /*<<< orphan*/ ) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  QualifyPath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WFIsDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOL
IsDirectory(LPTSTR pPath)
{
  LPTSTR pT;
  TCHAR szTemp[MAXPATHLEN];

  if (IsRootDirectory(pPath))
      return TRUE;

  // check for "." and ".."
  pT = FindFileName(pPath);

  if (ISDOTDIR(pT)) {
     return TRUE;
  }

  lstrcpy(szTemp, pPath);

  //
  // QualifyPath
  //
  QualifyPath(szTemp);

  return WFIsDir(szTemp);
}