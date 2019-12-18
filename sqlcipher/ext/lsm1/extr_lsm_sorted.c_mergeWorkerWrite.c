#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_19__ {int iOutputOff; scalar_t__ nSkip; } ;
struct TYPE_18__ {TYPE_4__* pDb; TYPE_3__* aSave; int /*<<< orphan*/ * pPage; TYPE_2__* pCsr; TYPE_1__* pLevel; } ;
struct TYPE_17__ {scalar_t__ iFirst; } ;
struct TYPE_16__ {int /*<<< orphan*/  pFS; } ;
struct TYPE_15__ {int bStore; } ;
struct TYPE_14__ {scalar_t__* pPrevMergePtr; } ;
struct TYPE_13__ {TYPE_5__ lhs; TYPE_7__* pMerge; } ;
typedef  TYPE_5__ Segment ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_6__ MergeWorker ;
typedef  TYPE_7__ Merge ;

/* Variables and functions */
 int LSM_OK ; 
 int PGFTR_SKIP_NEXT_FLAG ; 
 int PGFTR_SKIP_THIS_FLAG ; 
 size_t SEGMENT_CELLPTR_OFFSET (int,int) ; 
 int SEGMENT_EOF (int,int) ; 
 size_t SEGMENT_FLAGS_OFFSET (int) ; 
 size_t SEGMENT_NRECORD_OFFSET (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__* fsPageData (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ keyszToSkip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lsmPutU16 (scalar_t__*,int /*<<< orphan*/ ) ; 
 int lsmVarintLen32 (int) ; 
 scalar_t__ lsmVarintPut32 (scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int mergeWorkerData (TYPE_6__*,int /*<<< orphan*/ ,int,void*,int) ; 
 int mergeWorkerFirstPage (TYPE_6__*) ; 
 int mergeWorkerNextPage (TYPE_6__*,int) ; 
 int mergeWorkerPushHierarchy (TYPE_6__*,int /*<<< orphan*/ ,void*,int) ; 
 int pageGetNRec (scalar_t__*,int) ; 
 int pageGetPtr (scalar_t__*,int) ; 
 scalar_t__ rtIsWrite (int) ; 
 int /*<<< orphan*/  rtTopic (int) ; 

__attribute__((used)) static int mergeWorkerWrite(
  MergeWorker *pMW,               /* Merge worker object to write into */
  int eType,                      /* One of SORTED_SEPARATOR, WRITE or DELETE */
  void *pKey, int nKey,           /* Key value */
  void *pVal, int nVal,           /* Value value */
  int iPtr                        /* Absolute value of page pointer, or 0 */
){
  int rc = LSM_OK;                /* Return code */
  Merge *pMerge;                  /* Persistent part of level merge state */
  int nHdr;                       /* Space required for this record header */
  Page *pPg;                      /* Page to write to */
  u8 *aData;                      /* Data buffer for page pWriter->pPage */
  int nData = 0;                  /* Size of buffer aData[] in bytes */
  int nRec = 0;                   /* Number of records on page pPg */
  int iFPtr = 0;                  /* Value of pointer in footer of pPg */
  int iRPtr = 0;                  /* Value of pointer written into record */
  int iOff = 0;                   /* Current write offset within page pPg */
  Segment *pSeg;                  /* Segment being written */
  int flags = 0;                  /* If != 0, flags value for page footer */
  int bFirst = 0;                 /* True for first key of output run */

  pMerge = pMW->pLevel->pMerge;    
  pSeg = &pMW->pLevel->lhs;

  if( pSeg->iFirst==0 && pMW->pPage==0 ){
    rc = mergeWorkerFirstPage(pMW);
    bFirst = 1;
  }
  pPg = pMW->pPage;
  if( pPg ){
    aData = fsPageData(pPg, &nData);
    nRec = pageGetNRec(aData, nData);
    iFPtr = (int)pageGetPtr(aData, nData);
    iRPtr = iPtr - iFPtr;
  }
     
  /* Figure out how much space is required by the new record. The space
  ** required is divided into two sections: the header and the body. The
  ** header consists of the intial varint fields. The body are the blobs 
  ** of data that correspond to the key and value data. The entire header 
  ** must be stored on the page. The body may overflow onto the next and
  ** subsequent pages.
  **
  ** The header space is:
  **
  **     1) record type - 1 byte.
  **     2) Page-pointer-offset - 1 varint
  **     3) Key size - 1 varint
  **     4) Value size - 1 varint (only if LSM_INSERT flag is set)
  */
  if( rc==LSM_OK ){
    nHdr = 1 + lsmVarintLen32(iRPtr) + lsmVarintLen32(nKey);
    if( rtIsWrite(eType) ) nHdr += lsmVarintLen32(nVal);

    /* If the entire header will not fit on page pPg, or if page pPg is 
    ** marked read-only, advance to the next page of the output run. */
    iOff = pMerge->iOutputOff;
    if( iOff<0 || pPg==0 || iOff+nHdr > SEGMENT_EOF(nData, nRec+1) ){
      if( iOff>=0 && pPg ){
        /* Zero any free space on the page */
        assert( aData );
        memset(&aData[iOff], 0, SEGMENT_EOF(nData, nRec)-iOff);
      }
      iFPtr = (int)*pMW->pCsr->pPrevMergePtr;
      iRPtr = iPtr - iFPtr;
      iOff = 0;
      nRec = 0;
      rc = mergeWorkerNextPage(pMW, iFPtr);
      pPg = pMW->pPage;
    }
  }

  /* If this record header will be the first on the page, and the page is 
  ** not the very first in the entire run, add a copy of the key to the
  ** b-tree hierarchy.
  */
  if( rc==LSM_OK && nRec==0 && bFirst==0 ){
    assert( pMerge->nSkip>=0 );

    if( pMerge->nSkip==0 ){
      rc = mergeWorkerPushHierarchy(pMW, rtTopic(eType), pKey, nKey);
      assert( pMW->aSave[0].bStore==0 );
      pMW->aSave[0].bStore = 1;
      pMerge->nSkip = keyszToSkip(pMW->pDb->pFS, nKey);
    }else{
      pMerge->nSkip--;
      flags = PGFTR_SKIP_THIS_FLAG;
    }

    if( pMerge->nSkip ) flags |= PGFTR_SKIP_NEXT_FLAG;
  }

  /* Update the output segment */
  if( rc==LSM_OK ){
    aData = fsPageData(pPg, &nData);

    /* Update the page footer. */
    lsmPutU16(&aData[SEGMENT_NRECORD_OFFSET(nData)], (u16)(nRec+1));
    lsmPutU16(&aData[SEGMENT_CELLPTR_OFFSET(nData, nRec)], (u16)iOff);
    if( flags ) lsmPutU16(&aData[SEGMENT_FLAGS_OFFSET(nData)], (u16)flags);

    /* Write the entry header into the current page. */
    aData[iOff++] = (u8)eType;                                           /* 1 */
    iOff += lsmVarintPut32(&aData[iOff], iRPtr);                         /* 2 */
    iOff += lsmVarintPut32(&aData[iOff], nKey);                          /* 3 */
    if( rtIsWrite(eType) ) iOff += lsmVarintPut32(&aData[iOff], nVal);   /* 4 */
    pMerge->iOutputOff = iOff;

    /* Write the key and data into the segment. */
    assert( iFPtr==pageGetPtr(aData, nData) );
    rc = mergeWorkerData(pMW, 0, iFPtr+iRPtr, pKey, nKey);
    if( rc==LSM_OK && rtIsWrite(eType) ){
      if( rc==LSM_OK ){
        rc = mergeWorkerData(pMW, 0, iFPtr+iRPtr, pVal, nVal);
      }
    }
  }

  return rc;
}