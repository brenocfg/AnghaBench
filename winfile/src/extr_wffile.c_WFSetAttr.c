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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ATTR_COMPRESSED ; 
 int ATTR_ENCRYPTED ; 
 int /*<<< orphan*/  ChangeFileSystem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FSC_ATTRIBUTES ; 
 scalar_t__ SetFileAttributes (int /*<<< orphan*/ ,int) ; 

BOOL WFSetAttr(
    LPTSTR lpFile,
    DWORD dwAttr)
{
   BOOL bRet;

   //
   //  Compression attribute is handled separately -
   //  do not try to set it here.
   //
   dwAttr = dwAttr & ~(ATTR_COMPRESSED | ATTR_ENCRYPTED);

   bRet = SetFileAttributes(lpFile, dwAttr);

   if (bRet)
   {
      ChangeFileSystem(FSC_ATTRIBUTES, lpFile, NULL);
   }

   return ( (BOOL)!bRet );
}