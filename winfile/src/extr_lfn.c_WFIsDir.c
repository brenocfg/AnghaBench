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
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ATTR_DIR ; 
 int /*<<< orphan*/  FALSE ; 
 int GetFileAttributes (int /*<<< orphan*/ ) ; 
 int INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
WFIsDir(LPTSTR lpDir)
{
   DWORD attr = GetFileAttributes(lpDir);

   if (attr == INVALID_FILE_ATTRIBUTES)
      return FALSE;

   if (attr & ATTR_DIR)
      return TRUE;

   return FALSE;
}