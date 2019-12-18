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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ChangeFileSystem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FSC_DELETE ; 
 int /*<<< orphan*/  FileRemove (int /*<<< orphan*/ ) ; 

DWORD
WFRemove(LPTSTR pszFile)
{
   DWORD dwRet;

   dwRet = FileRemove(pszFile);
   if (!dwRet)
      ChangeFileSystem(FSC_DELETE,pszFile,NULL);

   return dwRet;
}