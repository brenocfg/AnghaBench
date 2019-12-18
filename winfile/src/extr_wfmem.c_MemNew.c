#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ LowPart; scalar_t__ HighPart; } ;
struct TYPE_10__ {scalar_t__ fdwStatus; int /*<<< orphan*/ * alpxdtaSorted; TYPE_1__ qTotalSize; scalar_t__ dwTotalCount; scalar_t__ dwEntries; } ;
struct TYPE_9__ {int /*<<< orphan*/  dwNextFree; int /*<<< orphan*/  dwSize; int /*<<< orphan*/ * next; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_2__* LPXDTALINK ;
typedef  TYPE_3__* LPXDTAHEAD ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_SIZE_GRANULARITY ; 
 int /*<<< orphan*/  LINKHEADSIZE ; 
 int /*<<< orphan*/  LMEM_FIXED ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* MemLinkToHead (TYPE_2__*) ; 
 int /*<<< orphan*/  OutputDebugString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsprintf (int /*<<< orphan*/ *,char*,TYPE_2__*) ; 

LPXDTALINK
MemNew()
{
   LPXDTALINK lpStart;
   LPXDTAHEAD lpHead;

   lpStart = (LPXDTALINK) LocalAlloc(LMEM_FIXED, BLOCK_SIZE_GRANULARITY);

   if (!lpStart)
      return NULL;

   //
   // Initialize the link structure
   //
   lpStart->next = NULL;
#ifdef MEMDOUBLE
   lpStart->dwSize = BLOCK_SIZE_GRANULARITY;
#endif
   lpStart->dwNextFree = LINKHEADSIZE;

   //
   // Create the XDTAHEAD block and initialize
   //
   lpHead = MemLinkToHead(lpStart);

   //
   // Initialize winfile specific data
   //
   lpHead->dwEntries = 0;
   lpHead->dwTotalCount = 0;
   lpHead->qTotalSize.HighPart = 0;
   lpHead->qTotalSize.LowPart = 0;
   lpHead->alpxdtaSorted = NULL;
   lpHead->fdwStatus = 0;

   //
   // lpHead->dwAlternateFileNameExtent = 0;
   // lpHead->iError = 0;
   //
#ifdef TESTING
// TESTING
   {TCHAR szT[100]; wsprintf(szT,
   L"MemNew %x\n", lpStart); OutputDebugString(szT);}
#endif

   return lpStart;
}