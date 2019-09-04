#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XDTALINK ;
typedef  int /*<<< orphan*/  XDTA ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_7__ {int dwSize; int cchFileNameOffset; } ;
struct TYPE_6__ {int dwNextFree; struct TYPE_6__* next; } ;
typedef  int PBYTE ;
typedef  TYPE_1__* LPXDTALINK ;
typedef  TYPE_2__* LPXDTA ;

/* Variables and functions */
 void* ALIGNBLOCK (int) ; 
 int BLOCK_SIZE_GRANULARITY ; 
 int /*<<< orphan*/  LMEM_FIXED ; 
 TYPE_1__* LocalAlloc (int /*<<< orphan*/ ,int) ; 

LPXDTA
MemAdd(
   LPXDTALINK* plpLast,
   UINT cchFileName,
   UINT cchAlternateFileName)
{
   LPXDTA lpxdta;
   UINT cbSpace;
   LPXDTALINK lpLast = *plpLast;
#ifdef MEMDOUBLE
   DWORD dwNewSize;
#endif

   cbSpace = ALIGNBLOCK((cchFileName+
                         cchAlternateFileName+2)*sizeof(WCHAR)+
                         sizeof(XDTA));

#ifdef MEMDOUBLE
   if (cbSpace + lpLast->dwNextFree > lpLast->dwSize) {

      //
      // Must allocate a new block
      //
      dwNewSize = lpLast->dwSize*2;

      if (dwNewSize < lpLast->dwSize)
         dwNewSize = lpLast->dwSize;

      lpLast->next = LocalAlloc(LMEM_FIXED, dwNewSize);

      if (!lpLast->next)
         return NULL;

      lpLast = *plpLast = lpLast->next;

      lpLast->dwSize = dwNewSize;
#else
   if (cbSpace + lpLast->dwNextFree > BLOCK_SIZE_GRANULARITY) {

      //
      // Must allocate a new block
      //
      lpLast->next = LocalAlloc(LMEM_FIXED, BLOCK_SIZE_GRANULARITY);

      if (!lpLast->next)
         return NULL;

      lpLast = *plpLast = lpLast->next;
#endif

      lpLast->next = NULL;
      lpLast->dwNextFree = ALIGNBLOCK(sizeof(XDTALINK));
   }

   //
   // We have enough space in this link now
   // Update everything
   //

   lpxdta = (LPXDTA)((PBYTE)lpLast+lpLast->dwNextFree);

   lpLast->dwNextFree += cbSpace;
   lpxdta->dwSize = cbSpace;
   lpxdta->cchFileNameOffset = cchFileName+1;

   return lpxdta;
}