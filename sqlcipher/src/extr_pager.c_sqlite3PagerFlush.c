#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int errCode; int /*<<< orphan*/  pPCache; } ;
struct TYPE_7__ {scalar_t__ nRef; struct TYPE_7__* pDirty; } ;
typedef  TYPE_1__ PgHdr ;
typedef  TYPE_2__ Pager ;

/* Variables and functions */
 int /*<<< orphan*/  MEMDB ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_pager_state (TYPE_2__*) ; 
 int pagerStress (void*,TYPE_1__*) ; 
 TYPE_1__* sqlite3PcacheDirtyList (int /*<<< orphan*/ ) ; 

int sqlite3PagerFlush(Pager *pPager){
  int rc = pPager->errCode;
  if( !MEMDB ){
    PgHdr *pList = sqlite3PcacheDirtyList(pPager->pPCache);
    assert( assert_pager_state(pPager) );
    while( rc==SQLITE_OK && pList ){
      PgHdr *pNext = pList->pDirty;
      if( pList->nRef==0 ){
        rc = pagerStress((void*)pPager, pList);
      }
      pList = pNext;
    }
  }

  return rc;
}