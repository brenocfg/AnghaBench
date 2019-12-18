#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lpszFI; int /*<<< orphan*/ * hIcon; int /*<<< orphan*/ * szExt; struct TYPE_5__* next; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__** PPDOCBUCKET ;
typedef  TYPE_1__* PDOCBUCKET ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  DOCBUCKET ;

/* Variables and functions */
 int ByteCountOf (int) ; 
 int /*<<< orphan*/  CharLower (int /*<<< orphan*/ *) ; 
 int DOCHASHFUNC (int /*<<< orphan*/ *) ; 
 scalar_t__ DocFind (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int EXTSIZ ; 
 int FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RemoveEndQuote (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lstrlen (int /*<<< orphan*/ *) ; 

INT
DocInsert(PPDOCBUCKET ppDocBucket,
         LPTSTR lpszExt,
         LPTSTR lpszFileIcon)
{
   PDOCBUCKET pDocBucket;
   INT iBucket;
   TCHAR szExt[EXTSIZ];


   //
   // Only allow certain lengths; if invalid ppDocBucket, fail
   //
   if (lstrlen(lpszExt) >= EXTSIZ || !ppDocBucket)
      return FALSE;

   //
   // Disallow duplicates
   //
   if (DocFind(ppDocBucket, lpszExt)) {
      return -1;
   }

   pDocBucket = (PDOCBUCKET) LocalAlloc(LPTR,sizeof(DOCBUCKET));

   if (!pDocBucket) {
      return 0;
   }

   iBucket = DOCHASHFUNC(lpszExt);

   //
   // Set up bucket; always char lower
   //
   pDocBucket->next = ppDocBucket[iBucket];

   CharLower(lpszExt);
   lstrcpy(szExt, lpszExt);
   RemoveEndQuote(szExt);
   lstrcpy(pDocBucket->szExt, szExt);

   pDocBucket->hIcon = NULL;
   pDocBucket->lpszFI = NULL;
   
   if (lpszFileIcon != NULL)
	   pDocBucket->lpszFI = (LPTSTR) LocalAlloc(LPTR, ByteCountOf(lstrlen(lpszFileIcon)+1));		
   if (pDocBucket->lpszFI != NULL)
	  lstrcpy(pDocBucket->lpszFI, lpszFileIcon);

   ppDocBucket[iBucket] = pDocBucket;

   return 1;
}