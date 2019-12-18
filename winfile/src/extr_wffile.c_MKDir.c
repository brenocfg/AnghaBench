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
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ChangeFileSystem (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateDirectory (scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateDirectoryEx (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FSC_MKDIR ; 
 int /*<<< orphan*/  GetLastError () ; 

DWORD MKDir(
    LPTSTR pName,
    LPTSTR pSrc)
{
   DWORD dwErr = ERROR_SUCCESS;

   if ((pSrc && *pSrc) ?
         CreateDirectoryEx(pSrc, pName, NULL) :
         CreateDirectory(pName, NULL))
   {
      ChangeFileSystem(FSC_MKDIR, pName, NULL);
   }
   else
   {
      dwErr = GetLastError();
   }

   return (dwErr);
}