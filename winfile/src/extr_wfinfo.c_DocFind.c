#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  szExt; struct TYPE_6__* next; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__** PPDOCBUCKET ;
typedef  TYPE_1__* PDOCBUCKET ;
typedef  int /*<<< orphan*/  LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CharLower (int /*<<< orphan*/ *) ; 
 size_t DOCHASHFUNC (int /*<<< orphan*/ *) ; 
 int EXTSIZ ; 
 TYPE_1__* FALSE ; 
 int /*<<< orphan*/  RemoveEndQuote (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lstrlen (int /*<<< orphan*/ ) ; 

PDOCBUCKET
DocFind(PPDOCBUCKET ppDocBucket, LPTSTR lpszExt)
{
   PDOCBUCKET pDocBucket;
   TCHAR szExt[EXTSIZ];

   //
   // Disallow long exts; if invalid ppDocBucket, fail
   //
   if (lstrlen(lpszExt) >= EXTSIZ || !ppDocBucket)
      return FALSE;

   lstrcpy(szExt, lpszExt);

   CharLower(szExt);
   RemoveEndQuote(szExt);

   for (pDocBucket=ppDocBucket[DOCHASHFUNC(szExt)]; pDocBucket; pDocBucket = pDocBucket->next) {

      if (!lstrcmp(pDocBucket->szExt, szExt)) {

         return pDocBucket;
      }
   }

   return NULL;
}