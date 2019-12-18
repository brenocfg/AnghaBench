#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int nRight; void* pSplitKey; int nSplitKey; int /*<<< orphan*/  iSplitTopic; } ;
struct TYPE_14__ {TYPE_1__* pDb; } ;
struct TYPE_13__ {scalar_t__ pPg; int eType; void* pKey; int nKey; scalar_t__ nVal; scalar_t__ pVal; TYPE_4__* pLevel; } ;
struct TYPE_12__ {int /*<<< orphan*/  xCmp; } ;
typedef  TYPE_2__ SegmentPtr ;
typedef  TYPE_3__ MultiCursor ;
typedef  int LsmPgno ;
typedef  TYPE_4__ Level ;

/* Variables and functions */
 int LSM_INSERT ; 
 int LSM_OK ; 
 int LSM_SEEK_EQ ; 
 int LSM_SEEK_GE ; 
 int LSM_SEEK_LE ; 
 int /*<<< orphan*/  LSM_SEGMENTPTR_FREE_THRESHOLD ; 
 int LSM_START_DELETE ; 
 int /*<<< orphan*/  assert (int) ; 
 int rtTopic (int) ; 
 int seekInSegment (TYPE_3__*,TYPE_2__*,int,void*,int,int,int,int*,int*) ; 
 int segmentPtrEnd (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  segmentPtrReset (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int sortedKeyCompare (int /*<<< orphan*/ ,int,void*,int,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int seekInLevel(
  MultiCursor *pCsr,              /* Sorted cursor object to seek */
  SegmentPtr *aPtr,               /* Pointer to array of (nRhs+1) SPs */
  int eSeek,                      /* Search bias - see above */
  int iTopic,                     /* Key topic to search for */
  void *pKey, int nKey,           /* Key to search for */
  LsmPgno *piPgno,                /* IN/OUT: fraction cascade pointer (or 0) */
  int *pbStop                     /* OUT: See above */
){
  Level *pLvl = aPtr[0].pLevel;   /* Level to seek within */
  int rc = LSM_OK;                /* Return code */
  int iOut = 0;                   /* Pointer to return to caller */
  int res = -1;                   /* Result of xCmp(pKey, split) */
  int nRhs = pLvl->nRight;        /* Number of right-hand-side segments */
  int bStop = 0;

  /* If this is a composite level (one currently undergoing an incremental
  ** merge), figure out if the search key is larger or smaller than the
  ** levels split-key.  */
  if( nRhs ){
    res = sortedKeyCompare(pCsr->pDb->xCmp, iTopic, pKey, nKey, 
        pLvl->iSplitTopic, pLvl->pSplitKey, pLvl->nSplitKey
    );
  }

  /* If (res<0), then key pKey/nKey is smaller than the split-key (or this
  ** is not a composite level and there is no split-key). Search the 
  ** left-hand-side of the level in this case.  */
  if( res<0 ){
    int i;
    int iPtr = 0;
    if( nRhs==0 ) iPtr = (int)*piPgno;

    rc = seekInSegment(
        pCsr, &aPtr[0], iTopic, pKey, nKey, iPtr, eSeek, &iOut, &bStop
    );
    if( rc==LSM_OK && nRhs>0 && eSeek==LSM_SEEK_GE && aPtr[0].pPg==0 ){
      res = 0;
    }
    for(i=1; i<=nRhs; i++){
      segmentPtrReset(&aPtr[i], LSM_SEGMENTPTR_FREE_THRESHOLD);
    }
  }
  
  if( res>=0 ){
    int bHit = 0;                 /* True if at least one rhs is not EOF */
    int iPtr = (int)*piPgno;
    int i;
    segmentPtrReset(&aPtr[0], LSM_SEGMENTPTR_FREE_THRESHOLD);
    for(i=1; rc==LSM_OK && i<=nRhs && bStop==0; i++){
      SegmentPtr *pPtr = &aPtr[i];
      iOut = 0;
      rc = seekInSegment(
          pCsr, pPtr, iTopic, pKey, nKey, iPtr, eSeek, &iOut, &bStop
      );
      iPtr = iOut;

      /* If the segment-pointer has settled on a key that is smaller than
      ** the splitkey, invalidate the segment-pointer.  */
      if( pPtr->pPg ){
        res = sortedKeyCompare(pCsr->pDb->xCmp, 
            rtTopic(pPtr->eType), pPtr->pKey, pPtr->nKey, 
            pLvl->iSplitTopic, pLvl->pSplitKey, pLvl->nSplitKey
        );
        if( res<0 ){
          if( pPtr->eType & LSM_START_DELETE ){
            pPtr->eType &= ~LSM_INSERT;
            pPtr->pKey = pLvl->pSplitKey;
            pPtr->nKey = pLvl->nSplitKey;
            pPtr->pVal = 0;
            pPtr->nVal = 0;
          }else{
            segmentPtrReset(pPtr, LSM_SEGMENTPTR_FREE_THRESHOLD);
          }
        }
      }

      if( aPtr[i].pKey ) bHit = 1;
    }

    if( rc==LSM_OK && eSeek==LSM_SEEK_LE && bHit==0 ){
      rc = segmentPtrEnd(pCsr, &aPtr[0], 1);
    }
  }

  assert( eSeek==LSM_SEEK_EQ || bStop==0 );
  *piPgno = iOut;
  *pbStop = bStop;
  return rc;
}