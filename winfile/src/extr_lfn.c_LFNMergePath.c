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
typedef  scalar_t__ TCHAR ;
typedef  scalar_t__* LPTSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddBackslash (scalar_t__*) ; 
 scalar_t__ CHAR_BACKSLASH ; 
 scalar_t__ CHAR_DOT ; 
 scalar_t__ CHAR_NULL ; 
 scalar_t__ COUNTOF (scalar_t__*) ; 
 int /*<<< orphan*/  FindFileName (scalar_t__*) ; 
 int /*<<< orphan*/  I_LFNEditName (scalar_t__*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  RemoveLast (scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcpy (scalar_t__*,scalar_t__*) ; 
 int lstrlen (scalar_t__*) ; 

BOOL
LFNMergePath(LPTSTR lpMask, LPTSTR lpFile)
{
   TCHAR szT[MAXPATHLEN*2];
   INT iResStrlen;

   //
   // Get the directory portion (from root to parent) of the destination.
   // (  a:\joe\martha\wilcox.*  ->  a:\joe\martha\ )
   //
   lstrcpy( szT, lpMask );
   RemoveLast( szT );

   //
   // Add a blackslash if there isn't one already.
   //
   AddBackslash(szT);

   // hack fix: Normally, I_LFNEditName will return a:\xxxx\\. when lpFile
   // is "\\" (C-style string, so the first \ is an escape char).
   // Only do the file masking if lpFile is NOT the root directory.
   // If it is, the return value is a:\xxxx\ which is what is expected
   // when a root is merged.

   if (!( CHAR_BACKSLASH == lpFile[0] && CHAR_NULL == lpFile[1] )) {

      iResStrlen = lstrlen( szT );

      I_LFNEditName(lpFile,                  // jack.bat
         FindFileName( lpMask ),             // *.*
         szT + iResStrlen,                   // right after "a:\more\beer\"
         COUNTOF(szT) - iResStrlen);

      // If there is a trailing '.', always but always kill it.

      iResStrlen = lstrlen( szT );
      if ((iResStrlen != 0) && CHAR_DOT == szT[iResStrlen - 1])
         szT[ iResStrlen-1 ] = CHAR_NULL;
   }

   lstrcpy(lpMask, szT);
   return TRUE;
}