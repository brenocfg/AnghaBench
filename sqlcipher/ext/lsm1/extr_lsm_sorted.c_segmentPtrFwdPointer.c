#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ iRoot; } ;
struct TYPE_10__ {int nRight; TYPE_7__* aRhs; TYPE_7__ lhs; struct TYPE_10__* pNext; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pPg; TYPE_7__* pSeg; int /*<<< orphan*/  iCell; TYPE_2__* pLevel; } ;
typedef  TYPE_1__ SegmentPtr ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  MultiCursor ;
typedef  int /*<<< orphan*/  LsmPgno ;
typedef  TYPE_2__ Level ;

/* Variables and functions */
 int LSM_CORRUPT_BKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  lsmFsPageRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int ptrFwdPointer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  segmentPtrReset (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sortedRhsFirst (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int segmentPtrFwdPointer(
  MultiCursor *pCsr,              /* Multi-cursor pPtr belongs to */
  SegmentPtr *pPtr,               /* Segment-pointer to extract FC ptr from */
  LsmPgno *piPtr                  /* OUT: FC pointer value */
){
  Level *pLvl = pPtr->pLevel;
  Level *pNext = pLvl->pNext;
  Page *pPg = pPtr->pPg;
  int rc;
  int bFound;
  LsmPgno iOut = 0;

  if( pPtr->pSeg==&pLvl->lhs || pPtr->pSeg==&pLvl->aRhs[pLvl->nRight-1] ){
    if( pNext==0 
        || (pNext->nRight==0 && pNext->lhs.iRoot)
        || (pNext->nRight!=0 && pNext->aRhs[0].iRoot)
      ){
      /* Do nothing. The pointer will not be used anyway. */
      return LSM_OK;
    }
  }else{
    if( pPtr[1].pSeg->iRoot ){
      return LSM_OK;
    }
  }

  /* Search for a pointer within the current segment. */
  lsmFsPageRef(pPg);
  rc = ptrFwdPointer(pPg, pPtr->iCell, pPtr->pSeg, &iOut, &bFound);

  if( rc==LSM_OK && bFound==0 ){
    /* This case happens when pPtr points to the left-hand-side of a segment
    ** currently undergoing an incremental merge. In this case, jump to the
    ** oldest segment in the right-hand-side of the same level and continue
    ** searching. But - do not consider any keys smaller than the levels
    ** split-key. */
    SegmentPtr ptr;

    if( pPtr->pLevel->nRight==0 || pPtr->pSeg!=&pPtr->pLevel->lhs ){
      return LSM_CORRUPT_BKPT;
    }

    memset(&ptr, 0, sizeof(SegmentPtr));
    ptr.pLevel = pPtr->pLevel;
    ptr.pSeg = &ptr.pLevel->aRhs[ptr.pLevel->nRight-1];
    rc = sortedRhsFirst(pCsr, ptr.pLevel, &ptr);
    if( rc==LSM_OK ){
      rc = ptrFwdPointer(ptr.pPg, ptr.iCell, ptr.pSeg, &iOut, &bFound);
      ptr.pPg = 0;
    }
    segmentPtrReset(&ptr, 0);
  }

  *piPtr = iOut;
  return rc;
}