#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int dwFileAttributes; int /*<<< orphan*/ * cAlternateFileName; int /*<<< orphan*/ * cFileName; } ;
struct TYPE_4__ {int dwAttrFilter; scalar_t__ nSpaceLeft; scalar_t__ err; TYPE_3__ fd; int /*<<< orphan*/  hFindFile; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* LPLFNDTA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ATTR_USED ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FindNextFile (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Wow64DisableWow64FsRedirection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Wow64RevertWow64FsRedirection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ lstrlen (int /*<<< orphan*/ *) ; 

BOOL
WFFindNext(LPLFNDTA lpFind)
{
	PVOID oldValue;
	Wow64DisableWow64FsRedirection(&oldValue);
	
   while (FindNextFile(lpFind->hFindFile, &lpFind->fd)) {

	  lpFind->fd.dwFileAttributes &= ATTR_USED;
   
      //
      // only pick files that fit attr filter
      //
      if ((lpFind->fd.dwFileAttributes & ~lpFind->dwAttrFilter) != 0)
         continue;

      //
      // Don't allow viewage of files > MAXPATHLEN
      //
      if (lstrlen(lpFind->fd.cFileName) > lpFind->nSpaceLeft) {

         if (!lpFind->fd.cAlternateFileName[0] ||
            lstrlen(lpFind->fd.cAlternateFileName) > lpFind->nSpaceLeft) {

            continue;
         }

         //
         // Force longname to be same as shortname
         //
         lstrcpy(lpFind->fd.cFileName, lpFind->fd.cAlternateFileName);
      }

	  Wow64RevertWow64FsRedirection(oldValue);
      lpFind->err = 0;
      return TRUE;
   }

   lpFind->err = GetLastError();

   Wow64RevertWow64FsRedirection(oldValue);
   return(FALSE);
}