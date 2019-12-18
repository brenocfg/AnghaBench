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
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ChangeFileSystem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FSC_RMDIR ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ RemoveDirectory (int /*<<< orphan*/ ) ; 

DWORD RMDir(
    LPTSTR pName)
{
   DWORD dwErr = 0;

   if (RemoveDirectory(pName))
   {
      ChangeFileSystem(FSC_RMDIR, pName, NULL);
   }
   else
   {
      dwErr = (WORD)GetLastError();
   }

   return (dwErr);
}