#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int flags; struct TYPE_12__* pNext; scalar_t__ nRight; } ;
struct TYPE_11__ {TYPE_1__* pDb; int /*<<< orphan*/  aPtr; } ;
struct TYPE_10__ {TYPE_4__* pLevel; } ;
struct TYPE_9__ {int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_2__ Snapshot ;
typedef  int /*<<< orphan*/  SegmentPtr ;
typedef  TYPE_3__ MultiCursor ;
typedef  TYPE_4__ Level ;

/* Variables and functions */
 int LEVEL_INCOMPLETE ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lsmMallocZeroRc (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  multiCursorAddOne (TYPE_3__*,TYPE_4__*,int*) ; 

__attribute__((used)) static int multiCursorAddAll(MultiCursor *pCsr, Snapshot *pSnap){
  Level *pLvl;
  int nPtr = 0;
  int rc = LSM_OK;

  for(pLvl=pSnap->pLevel; pLvl; pLvl=pLvl->pNext){
    /* If the LEVEL_INCOMPLETE flag is set, then this function is being
    ** called (indirectly) from within a sortedNewToplevel() call to
    ** construct pLvl. In this case ignore pLvl - this cursor is going to
    ** be used to retrieve a freelist entry from the LSM, and the partially
    ** complete level may confuse it.  */
    if( pLvl->flags & LEVEL_INCOMPLETE ) continue;
    nPtr += (1 + pLvl->nRight);
  }

  assert( pCsr->aPtr==0 );
  pCsr->aPtr = lsmMallocZeroRc(pCsr->pDb->pEnv, sizeof(SegmentPtr) * nPtr, &rc);

  for(pLvl=pSnap->pLevel; pLvl; pLvl=pLvl->pNext){
    if( (pLvl->flags & LEVEL_INCOMPLETE)==0 ){
      multiCursorAddOne(pCsr, pLvl, &rc);
    }
  }

  return rc;
}