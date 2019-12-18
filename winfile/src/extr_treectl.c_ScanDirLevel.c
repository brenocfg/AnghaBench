#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {int dwFileAttributes; int /*<<< orphan*/  cFileName; } ;
struct TYPE_10__ {TYPE_1__ fd; } ;
struct TYPE_9__ {int /*<<< orphan*/  wFlags; } ;
typedef  TYPE_2__* PDNODE ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  TYPE_3__ LFNDTA ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ATTR_DIR ; 
 int /*<<< orphan*/  AddBackslash (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  ISDOTDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_HASCHILDREN ; 
 int /*<<< orphan*/  WFFindClose (TYPE_3__*) ; 
 scalar_t__ WFFindFirst (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ WFFindNext (TYPE_3__*) ; 
 int /*<<< orphan*/  lstrcat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szMessage ; 
 int /*<<< orphan*/  szStarDotStar ; 

VOID
ScanDirLevel(PDNODE pParentNode, LPTSTR szPath, DWORD view)
{
  BOOL bFound;
  LFNDTA lfndta;

  /* Add '*.*' to the current path. */
  lstrcpy(szMessage, szPath);
  AddBackslash(szMessage);
  lstrcat(szMessage, szStarDotStar);

  /* Search for the first subdirectory on this level. */

  bFound = WFFindFirst(&lfndta, szMessage, ATTR_DIR | view);

  while (bFound)
    {
      /* Is this not a '.' or '..' directory? */
      if (!ISDOTDIR(lfndta.fd.cFileName) &&
         (lfndta.fd.dwFileAttributes & ATTR_DIR)) {

         pParentNode->wFlags |= TF_HASCHILDREN;
         bFound = FALSE;
      } else
         /* Search for the next subdirectory. */
         bFound = WFFindNext(&lfndta);
    }

  WFFindClose(&lfndta);
}