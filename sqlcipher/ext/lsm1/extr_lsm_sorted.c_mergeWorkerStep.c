#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int (* xCmp ) (scalar_t__,int /*<<< orphan*/ ,void*,int) ;int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_19__ {void* pData; } ;
struct TYPE_18__ {int eType; scalar_t__ iPtr; int /*<<< orphan*/  nKey; scalar_t__ pKey; } ;
struct TYPE_17__ {TYPE_3__* pCsr; int /*<<< orphan*/ * aGobble; TYPE_1__* pDb; } ;
struct TYPE_16__ {int eType; int nPtr; int* aTree; TYPE_6__ val; TYPE_2__* aPtr; TYPE_5__* pBtCsr; scalar_t__* pPrevMergePtr; } ;
struct TYPE_15__ {int flags; scalar_t__ pPg; scalar_t__ iPgPtr; scalar_t__ iPtr; int /*<<< orphan*/  nKey; scalar_t__ pKey; } ;
typedef  TYPE_2__ SegmentPtr ;
typedef  TYPE_3__ MultiCursor ;
typedef  TYPE_4__ MergeWorker ;
typedef  scalar_t__ LsmPgno ;
typedef  TYPE_5__ BtreeCursor ;

/* Variables and functions */
 int CURSOR_DATA_SEGMENT ; 
 int LSM_OK ; 
 int PGFTR_SKIP_THIS_FLAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lsmFsPageNumber (scalar_t__) ; 
 int /*<<< orphan*/  lsmMCursorKey (TYPE_3__*,void**,int*) ; 
 int lsmMCursorNext (TYPE_3__*) ; 
 int lsmMCursorValid (TYPE_3__*) ; 
 int /*<<< orphan*/  mergeRangeDeletes (TYPE_3__*,int*,int*) ; 
 int mergeWorkerWrite (TYPE_4__*,int,void*,int,void*,int,int) ; 
 int multiCursorGetVal (TYPE_3__*,int,void**,int*) ; 
 scalar_t__ rtIsSeparator (int) ; 
 int rtTopic (int) ; 
 int sortedBlobSet (int /*<<< orphan*/ ,TYPE_6__*,void*,int) ; 
 int stub1 (scalar_t__,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ stub2 (scalar_t__,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int mergeWorkerStep(MergeWorker *pMW){
  lsm_db *pDb = pMW->pDb;       /* Database handle */
  MultiCursor *pCsr;            /* Cursor to read input data from */
  int rc = LSM_OK;              /* Return code */
  int eType;                    /* SORTED_SEPARATOR, WRITE or DELETE */
  void *pKey; int nKey;         /* Key */
  LsmPgno iPtr;
  int iVal;

  pCsr = pMW->pCsr;

  /* Pull the next record out of the source cursor. */
  lsmMCursorKey(pCsr, &pKey, &nKey);
  eType = pCsr->eType;

  /* Figure out if the output record may have a different pointer value
  ** than the previous. This is the case if the current key is identical to
  ** a key that appears in the lowest level run being merged. If so, set 
  ** iPtr to the absolute pointer value. If not, leave iPtr set to zero, 
  ** indicating that the output pointer value should be a copy of the pointer 
  ** value written with the previous key.  */
  iPtr = (pCsr->pPrevMergePtr ? *pCsr->pPrevMergePtr : 0);
  if( pCsr->pBtCsr ){
    BtreeCursor *pBtCsr = pCsr->pBtCsr;
    if( pBtCsr->pKey ){
      int res = rtTopic(pBtCsr->eType) - rtTopic(eType);
      if( res==0 ) res = pDb->xCmp(pBtCsr->pKey, pBtCsr->nKey, pKey, nKey);
      if( 0==res ) iPtr = pBtCsr->iPtr;
      assert( res>=0 );
    }
  }else if( pCsr->nPtr ){
    SegmentPtr *pPtr = &pCsr->aPtr[pCsr->nPtr-1];
    if( pPtr->pPg
     && 0==pDb->xCmp(pPtr->pKey, pPtr->nKey, pKey, nKey)
    ){
      iPtr = pPtr->iPtr+pPtr->iPgPtr;
    }
  }

  iVal = pCsr->aTree[1];
  mergeRangeDeletes(pCsr, &iVal, &eType);

  if( eType!=0 ){
    if( pMW->aGobble ){
      int iGobble = pCsr->aTree[1] - CURSOR_DATA_SEGMENT;
      if( iGobble<pCsr->nPtr && iGobble>=0 ){
        SegmentPtr *pGobble = &pCsr->aPtr[iGobble];
        if( (pGobble->flags & PGFTR_SKIP_THIS_FLAG)==0 ){
          pMW->aGobble[iGobble] = lsmFsPageNumber(pGobble->pPg);
        }
      }
    }

    /* If this is a separator key and we know that the output pointer has not
    ** changed, there is no point in writing an output record. Otherwise,
    ** proceed. */
    if( rc==LSM_OK && (rtIsSeparator(eType)==0 || iPtr!=0) ){
      /* Write the record into the main run. */
      void *pVal; int nVal;
      rc = multiCursorGetVal(pCsr, iVal, &pVal, &nVal);
      if( pVal && rc==LSM_OK ){
        assert( nVal>=0 );
        rc = sortedBlobSet(pDb->pEnv, &pCsr->val, pVal, nVal);
        pVal = pCsr->val.pData;
      }
      if( rc==LSM_OK ){
        rc = mergeWorkerWrite(pMW, eType, pKey, nKey, pVal, nVal, (int)iPtr);
      }
    }
  }

  /* Advance the cursor to the next input record (assuming one exists). */
  assert( lsmMCursorValid(pMW->pCsr) );
  if( rc==LSM_OK ) rc = lsmMCursorNext(pMW->pCsr);

  return rc;
}