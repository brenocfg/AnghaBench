#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  pEnv; int /*<<< orphan*/  pWorker; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_12__ {scalar_t__ iRoot; } ;
struct TYPE_14__ {scalar_t__ nRight; int flags; scalar_t__ pMerge; TYPE_2__ lhs; struct TYPE_14__* pNext; TYPE_2__* aRhs; scalar_t__ iAge; } ;
struct TYPE_13__ {int nInput; int /*<<< orphan*/ * aInput; } ;
typedef  TYPE_2__ Segment ;
typedef  int /*<<< orphan*/  MergeInput ;
typedef  TYPE_3__ Merge ;
typedef  TYPE_4__ Level ;

/* Variables and functions */
 int LEVEL_FREELIST_ONLY ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* lsmDbSnapshotLevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmDbSnapshotSetLevel (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ lsmMallocZeroRc (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  sortedFreeLevel (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static int sortedMergeSetup(
  lsm_db *pDb,                    /* Database handle */
  Level *pLevel,                  /* First level to merge */
  int nMerge,                     /* Merge this many levels together */
  Level **ppNew                   /* New, merged, level */
){
  int rc = LSM_OK;                /* Return Code */
  Level *pNew;                    /* New Level object */
  int bUseNext = 0;               /* True to link in next separators */
  Merge *pMerge;                  /* New Merge object */
  int nByte;                      /* Bytes of space allocated at pMerge */

#ifdef LSM_DEBUG
  int iLevel;
  Level *pX = pLevel;
  for(iLevel=0; iLevel<nMerge; iLevel++){
    assert( pX->nRight==0 );
    pX = pX->pNext;
  }
#endif

  /* Allocate the new Level object */
  pNew = (Level *)lsmMallocZeroRc(pDb->pEnv, sizeof(Level), &rc);
  if( pNew ){
    pNew->aRhs = (Segment *)lsmMallocZeroRc(pDb->pEnv, 
                                        nMerge * sizeof(Segment), &rc);
  }

  /* Populate the new Level object */
  if( rc==LSM_OK ){
    Level *pNext = 0;             /* Level following pNew */
    int i;
    int bFreeOnly = 1;
    Level *pTopLevel;
    Level *p = pLevel;
    Level **pp;
    pNew->nRight = nMerge;
    pNew->iAge = pLevel->iAge+1;
    for(i=0; i<nMerge; i++){
      assert( p->nRight==0 );
      pNext = p->pNext;
      pNew->aRhs[i] = p->lhs;
      if( (p->flags & LEVEL_FREELIST_ONLY)==0 ) bFreeOnly = 0;
      sortedFreeLevel(pDb->pEnv, p);
      p = pNext;
    }

    if( bFreeOnly ) pNew->flags |= LEVEL_FREELIST_ONLY;

    /* Replace the old levels with the new. */
    pTopLevel = lsmDbSnapshotLevel(pDb->pWorker);
    pNew->pNext = p;
    for(pp=&pTopLevel; *pp!=pLevel; pp=&((*pp)->pNext));
    *pp = pNew;
    lsmDbSnapshotSetLevel(pDb->pWorker, pTopLevel);

    /* Determine whether or not the next separators will be linked in */
    if( pNext && pNext->pMerge==0 && pNext->lhs.iRoot && pNext 
     && (bFreeOnly==0 || (pNext->flags & LEVEL_FREELIST_ONLY))
    ){
      bUseNext = 1;
    }
  }

  /* Allocate the merge object */
  nByte = sizeof(Merge) + sizeof(MergeInput) * (nMerge + bUseNext);
  pMerge = (Merge *)lsmMallocZeroRc(pDb->pEnv, nByte, &rc);
  if( pMerge ){
    pMerge->aInput = (MergeInput *)&pMerge[1];
    pMerge->nInput = nMerge + bUseNext;
    pNew->pMerge = pMerge;
  }

  *ppNew = pNew;
  return rc;
}