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
typedef  scalar_t__ u8 ;
struct TYPE_6__ {struct TYPE_6__* pScanNext; } ;
typedef  TYPE_1__ Fts5HashEntry ;

/* Variables and functions */
 char* fts5EntryKey (TYPE_1__*) ; 

__attribute__((used)) static Fts5HashEntry *fts5HashEntryMerge(
  Fts5HashEntry *pLeft,
  Fts5HashEntry *pRight
){
  Fts5HashEntry *p1 = pLeft;
  Fts5HashEntry *p2 = pRight;
  Fts5HashEntry *pRet = 0;
  Fts5HashEntry **ppOut = &pRet;

  while( p1 || p2 ){
    if( p1==0 ){
      *ppOut = p2;
      p2 = 0;
    }else if( p2==0 ){
      *ppOut = p1;
      p1 = 0;
    }else{
      int i = 0;
      char *zKey1 = fts5EntryKey(p1);
      char *zKey2 = fts5EntryKey(p2);
      while( zKey1[i]==zKey2[i] ) i++;

      if( ((u8)zKey1[i])>((u8)zKey2[i]) ){
        /* p2 is smaller */
        *ppOut = p2;
        ppOut = &p2->pScanNext;
        p2 = p2->pScanNext;
      }else{
        /* p1 is smaller */
        *ppOut = p1;
        ppOut = &p1->pScanNext;
        p1 = p1->pScanNext;
      }
      *ppOut = 0;
    }
  }

  return pRet;
}