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
typedef  int /*<<< orphan*/ * PBOOL ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ChangeFileSystem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FSC_RENAME ; 
 int /*<<< orphan*/  FileMove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

DWORD
WFMove(LPTSTR pszFrom, LPTSTR pszTo, PBOOL pbErrorOnDest, BOOL bSilent)
{
   DWORD dwRet;

   *pbErrorOnDest = FALSE;
   dwRet = FileMove(pszFrom,pszTo, pbErrorOnDest, bSilent);

   if (!dwRet)
      ChangeFileSystem(FSC_RENAME,pszFrom,pszTo);

   return dwRet;
}