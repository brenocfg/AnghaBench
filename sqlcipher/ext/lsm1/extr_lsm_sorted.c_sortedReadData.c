#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int nData; void* pData; } ;
typedef  int /*<<< orphan*/  Segment ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_1__ LsmBlob ;

/* Variables and functions */
 int LSM_CORRUPT_BKPT ; 
 int LSM_MIN (int,int) ; 
 int LSM_OK ; 
 int SEGMENT_BTREE_FLAG ; 
 int SEGMENT_EOF (int,int) ; 
 size_t SEGMENT_FLAGS_OFFSET (int) ; 
 size_t SEGMENT_NRECORD_OFFSET (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fsPageData (int /*<<< orphan*/ *,int*) ; 
 int lsmFsDbPageNext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lsmFsPageRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmFsPageRelease (int /*<<< orphan*/ *) ; 
 int lsmGetU16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmPageEnv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int sortedBlobGrow (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static int sortedReadData(
  Segment *pSeg,
  Page *pPg,
  int iOff,
  int nByte,
  void **ppData,
  LsmBlob *pBlob
){
  int rc = LSM_OK;
  int iEnd;
  int nData;
  int nCell;
  u8 *aData;

  aData = fsPageData(pPg, &nData);
  nCell = lsmGetU16(&aData[SEGMENT_NRECORD_OFFSET(nData)]);
  iEnd = SEGMENT_EOF(nData, nCell);
  assert( iEnd>0 && iEnd<nData );

  if( iOff+nByte<=iEnd ){
    *ppData = (void *)&aData[iOff];
  }else{
    int nRem = nByte;
    int i = iOff;
    u8 *aDest;

    /* Make sure the blob is big enough to store the value being loaded. */
    rc = sortedBlobGrow(lsmPageEnv(pPg), pBlob, nByte);
    if( rc!=LSM_OK ) return rc;
    pBlob->nData = nByte;
    aDest = (u8 *)pBlob->pData;
    *ppData = pBlob->pData;

    /* Increment the pointer pages ref-count. */
    lsmFsPageRef(pPg);

    while( rc==LSM_OK ){
      Page *pNext;
      int flags;

      /* Copy data from pPg into the output buffer. */
      int nCopy = LSM_MIN(nRem, iEnd-i);
      if( nCopy>0 ){
        memcpy(&aDest[nByte-nRem], &aData[i], nCopy);
        nRem -= nCopy;
        i += nCopy;
        assert( nRem==0 || i==iEnd );
      }
      assert( nRem>=0 );
      if( nRem==0 ) break;
      i -= iEnd;

      /* Grab the next page in the segment */

      do {
        rc = lsmFsDbPageNext(pSeg, pPg, 1, &pNext);
        if( rc==LSM_OK && pNext==0 ){
          rc = LSM_CORRUPT_BKPT;
        }
        if( rc ) break;
        lsmFsPageRelease(pPg);
        pPg = pNext;
        aData = fsPageData(pPg, &nData);
        flags = lsmGetU16(&aData[SEGMENT_FLAGS_OFFSET(nData)]);
      }while( flags&SEGMENT_BTREE_FLAG );

      iEnd = SEGMENT_EOF(nData, lsmGetU16(&aData[nData-2]));
      assert( iEnd>0 && iEnd<nData );
    }

    lsmFsPageRelease(pPg);
  }

  return rc;
}