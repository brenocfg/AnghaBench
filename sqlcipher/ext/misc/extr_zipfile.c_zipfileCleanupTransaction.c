#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ szOrig; scalar_t__ szCurrent; scalar_t__ pLastEntry; TYPE_2__* pFirstEntry; scalar_t__ pWriteFd; } ;
typedef  TYPE_1__ ZipfileTab ;
struct TYPE_6__ {struct TYPE_6__* pNext; } ;
typedef  TYPE_2__ ZipfileEntry ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  zipfileEntryFree (TYPE_2__*) ; 

__attribute__((used)) static void zipfileCleanupTransaction(ZipfileTab *pTab){
  ZipfileEntry *pEntry;
  ZipfileEntry *pNext;

  if( pTab->pWriteFd ){
    fclose(pTab->pWriteFd);
    pTab->pWriteFd = 0;
  }
  for(pEntry=pTab->pFirstEntry; pEntry; pEntry=pNext){
    pNext = pEntry->pNext;
    zipfileEntryFree(pEntry);
  }
  pTab->pFirstEntry = 0;
  pTab->pLastEntry = 0;
  pTab->szCurrent = 0;
  pTab->szOrig = 0;
}