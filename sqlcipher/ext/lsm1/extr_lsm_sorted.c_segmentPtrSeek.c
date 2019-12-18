#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_17__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_env ;
struct TYPE_25__ {int eType; int /*<<< orphan*/  flags; int /*<<< orphan*/  val; int /*<<< orphan*/  key; TYPE_1__* pDb; } ;
struct TYPE_24__ {scalar_t__ iPtr; int nCell; int eType; scalar_t__ iPgPtr; scalar_t__ pPg; int /*<<< orphan*/  nVal; int /*<<< orphan*/  pVal; int /*<<< orphan*/  nKey; int /*<<< orphan*/  pKey; TYPE_17__* pSeg; } ;
struct TYPE_23__ {int (* xCmp ) (void*,int,void*,int) ;int /*<<< orphan*/ * pEnv; } ;
struct TYPE_22__ {int nSize; } ;
typedef  TYPE_2__ SegmentPtr ;
typedef  TYPE_3__ MultiCursor ;
typedef  scalar_t__ LsmPgno ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_SEEK_EQ ; 
 int LSM_END_DELETE ; 
 int LSM_INSERT ; 
 int LSM_MAX (int,int) ; 
 int LSM_OK ; 
 int LSM_POINT_DELETE ; 
#define  LSM_SEEK_EQ 130 
#define  LSM_SEEK_GE 129 
#define  LSM_SEEK_LE 128 
 int /*<<< orphan*/  LSM_SEGMENTPTR_FREE_THRESHOLD ; 
 int LSM_START_DELETE ; 
 int /*<<< orphan*/  assert (int) ; 
 int assertKeyLocation (TYPE_3__*,TYPE_2__*,void*,int) ; 
 scalar_t__ assertSeekResult (TYPE_3__*,TYPE_2__*,int,void*,int,int) ; 
 scalar_t__ lsmFsDbPageIsLast (TYPE_17__*,scalar_t__) ; 
 scalar_t__ rtIsSeparator (int) ; 
 int rtTopic (int) ; 
 int segmentPtrAdvance (TYPE_3__*,TYPE_2__*,int) ; 
 int segmentPtrFwdPointer (TYPE_3__*,TYPE_2__*,scalar_t__*) ; 
 scalar_t__ segmentPtrIgnoreSeparators (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  segmentPtrKey (TYPE_2__*,void**,int*) ; 
 int segmentPtrLoadCell (TYPE_2__*,int) ; 
 int /*<<< orphan*/  segmentPtrReset (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int segmentPtrSearchOversized (TYPE_3__*,TYPE_2__*,int,void*,int) ; 
 int sortedBlobSet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sortedKeyCompare (int (*) (void*,int,void*,int),int,void*,int,int,void*,int) ; 

__attribute__((used)) static int segmentPtrSeek(
  MultiCursor *pCsr,              /* Cursor context */
  SegmentPtr *pPtr,               /* Pointer to seek */
  int iTopic,                     /* Key topic to seek to */
  void *pKey, int nKey,           /* Key to seek to */
  int eSeek,                      /* Search bias - see above */
  int *piPtr,                     /* OUT: FC pointer */
  int *pbStop
){
  int (*xCmp)(void *, int, void *, int) = pCsr->pDb->xCmp;
  int res = 0;                        /* Result of comparison operation */
  int rc = LSM_OK;
  int iMin;
  int iMax;
  LsmPgno iPtrOut = 0;

  /* If the current page contains an oversized entry, then there are no
  ** pointers to one or more of the subsequent pages in the sorted run.
  ** The following call ensures that the segment-ptr points to the correct 
  ** page in this case.  */
  rc = segmentPtrSearchOversized(pCsr, pPtr, iTopic, pKey, nKey);
  iPtrOut = pPtr->iPtr;

  /* Assert that this page is the right page of this segment for the key
  ** that we are searching for. Do this by loading page (iPg-1) and testing
  ** that pKey/nKey is greater than all keys on that page, and then by 
  ** loading (iPg+1) and testing that pKey/nKey is smaller than all
  ** the keys it houses.  
  **
  ** TODO: With range-deletes in the tree, the test described above may fail.
  */
#if 0
  assert( assertKeyLocation(pCsr, pPtr, pKey, nKey) );
#endif

  assert( pPtr->nCell>0 
       || pPtr->pSeg->nSize==1 
       || lsmFsDbPageIsLast(pPtr->pSeg, pPtr->pPg)
  );
  if( pPtr->nCell==0 ){
    segmentPtrReset(pPtr, LSM_SEGMENTPTR_FREE_THRESHOLD);
  }else{
    iMin = 0;
    iMax = pPtr->nCell-1;

    while( 1 ){
      int iTry = (iMin+iMax)/2;
      void *pKeyT; int nKeyT;       /* Key for cell iTry */
      int iTopicT;

      assert( iTry<iMax || iMin==iMax );

      rc = segmentPtrLoadCell(pPtr, iTry);
      if( rc!=LSM_OK ) break;

      segmentPtrKey(pPtr, &pKeyT, &nKeyT);
      iTopicT = rtTopic(pPtr->eType);

      res = sortedKeyCompare(xCmp, iTopicT, pKeyT, nKeyT, iTopic, pKey, nKey);
      if( res<=0 ){
        iPtrOut = pPtr->iPtr + pPtr->iPgPtr;
      }

      if( res==0 || iMin==iMax ){
        break;
      }else if( res>0 ){
        iMax = LSM_MAX(iTry-1, iMin);
      }else{
        iMin = iTry+1;
      }
    }

    if( rc==LSM_OK ){
      assert( res==0 || (iMin==iMax && iMin>=0 && iMin<pPtr->nCell) );
      if( res ){
        rc = segmentPtrLoadCell(pPtr, iMin);
      }
      assert( rc!=LSM_OK || res>0 || iPtrOut==(pPtr->iPtr + pPtr->iPgPtr) );

      if( rc==LSM_OK ){
        switch( eSeek ){
          case LSM_SEEK_EQ: {
            int eType = pPtr->eType;
            if( (res<0 && (eType & LSM_START_DELETE))
             || (res>0 && (eType & LSM_END_DELETE))
             || (res==0 && (eType & LSM_POINT_DELETE))
            ){
              *pbStop = 1;
            }else if( res==0 && (eType & LSM_INSERT) ){
              lsm_env *pEnv = pCsr->pDb->pEnv;
              *pbStop = 1;
              pCsr->eType = pPtr->eType;
              rc = sortedBlobSet(pEnv, &pCsr->key, pPtr->pKey, pPtr->nKey);
              if( rc==LSM_OK ){
                rc = sortedBlobSet(pEnv, &pCsr->val, pPtr->pVal, pPtr->nVal);
              }
              pCsr->flags |= CURSOR_SEEK_EQ;
            }
            segmentPtrReset(pPtr, LSM_SEGMENTPTR_FREE_THRESHOLD);
            break;
          }
          case LSM_SEEK_LE:
            if( res>0 ) rc = segmentPtrAdvance(pCsr, pPtr, 1);
            break;
          case LSM_SEEK_GE: {
            /* Figure out if we need to 'skip' the pointer forward or not */
            if( (res<=0 && (pPtr->eType & LSM_START_DELETE)) 
             || (res>0  && (pPtr->eType & LSM_END_DELETE)) 
            ){
              rc = segmentPtrFwdPointer(pCsr, pPtr, &iPtrOut);
            }
            if( res<0 && rc==LSM_OK ){
              rc = segmentPtrAdvance(pCsr, pPtr, 0);
            }
            break;
          }
        }
      }
    }

    /* If the cursor seek has found a separator key, and this cursor is
    ** supposed to ignore separators keys, advance to the next entry.  */
    if( rc==LSM_OK && pPtr->pPg
     && segmentPtrIgnoreSeparators(pCsr, pPtr) 
     && rtIsSeparator(pPtr->eType)
    ){
      assert( eSeek!=LSM_SEEK_EQ );
      rc = segmentPtrAdvance(pCsr, pPtr, eSeek==LSM_SEEK_LE);
    }
  }

  assert( rc!=LSM_OK || assertSeekResult(pCsr,pPtr,iTopic,pKey,nKey,eSeek) );
  *piPtr = (int)iPtrOut;
  return rc;
}