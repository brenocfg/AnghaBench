#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int /*<<< orphan*/  pWorker; int /*<<< orphan*/  pFS; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_7__ {int nHier; int /*<<< orphan*/ ** apHier; } ;
struct TYPE_6__ {int /*<<< orphan*/  pLevel; TYPE_1__* pDb; TYPE_3__ hier; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_2__ MergeWorker ;
typedef  scalar_t__ LsmPgno ;
typedef  TYPE_3__ Hierarchy ;

/* Variables and functions */
 int LSM_NOMEM_BKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  SEGMENT_BTREE_FLAG ; 
 size_t SEGMENT_CELLPTR_OFFSET (int,int) ; 
 int SEGMENT_EOF (int,int) ; 
 size_t SEGMENT_FLAGS_OFFSET (int) ; 
 size_t SEGMENT_NRECORD_OFFSET (int) ; 
 size_t SEGMENT_POINTER_OFFSET (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int* fsPageData (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ lsmFsPageNumber (int /*<<< orphan*/ *) ; 
 int lsmFsPagePersist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmFsPageRelease (int /*<<< orphan*/ *) ; 
 int lsmFsPageWritable (int /*<<< orphan*/ *) ; 
 int lsmFsSortedAppend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lsmPutU16 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmPutU64 (int*,scalar_t__) ; 
 scalar_t__ lsmRealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int lsmVarintLen32 (int) ; 
 scalar_t__ lsmVarintPut32 (int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,void*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int mergeWorkerPageOffset (int*,int) ; 
 int pageGetNRec (int*,int) ; 

__attribute__((used)) static int mergeWorkerBtreeWrite(
  MergeWorker *pMW,
  u8 eType,
  LsmPgno iPtr,
  LsmPgno iKeyPg,
  void *pKey,
  int nKey
){
  Hierarchy *p = &pMW->hier;
  lsm_db *pDb = pMW->pDb;         /* Database handle */
  int rc = LSM_OK;                /* Return Code */
  int iLevel;                     /* Level of b-tree hierachy to write to */
  int nData;                      /* Size of aData[] in bytes */
  u8 *aData;                      /* Page data for level iLevel */
  int iOff;                       /* Offset on b-tree page to write record to */
  int nRec;                       /* Initial number of records on b-tree page */

  /* iKeyPg should be zero for an ordinary b-tree key, or non-zero for an
  ** indirect key. The flags byte for an indirect key is 0x00.  */
  assert( (eType==0)==(iKeyPg!=0) );

  /* The MergeWorker.apHier[] array contains the right-most leaf of the b-tree
  ** hierarchy, the root node, and all nodes that lie on the path between.
  ** apHier[0] is the right-most leaf and apHier[pMW->nHier-1] is the current
  ** root page.
  **
  ** This loop searches for a node with enough space to store the key on,
  ** starting with the leaf and iterating up towards the root. When the loop
  ** exits, the key may be written to apHier[iLevel].  */
  for(iLevel=0; iLevel<=p->nHier; iLevel++){
    int nByte;                    /* Number of free bytes required */

    if( iLevel==p->nHier ){
      /* Extend the array and allocate a new root page. */
      Page **aNew;
      aNew = (Page **)lsmRealloc(
          pMW->pDb->pEnv, p->apHier, sizeof(Page *)*(p->nHier+1)
      );
      if( !aNew ){
        return LSM_NOMEM_BKPT;
      }
      p->apHier = aNew;
    }else{
      Page *pOld;
      int nFree;

      /* If the key will fit on this page, break out of the loop here.
      ** The new entry will be written to page apHier[iLevel]. */
      pOld = p->apHier[iLevel];
      assert( lsmFsPageWritable(pOld) );
      aData = fsPageData(pOld, &nData);
      if( eType==0 ){
        nByte = 2 + 1 + lsmVarintLen32((int)iPtr) + lsmVarintLen32((int)iKeyPg);
      }else{
        nByte = 2 + 1 + lsmVarintLen32((int)iPtr) + lsmVarintLen32(nKey) + nKey;
      }
      nRec = pageGetNRec(aData, nData);
      nFree = SEGMENT_EOF(nData, nRec) - mergeWorkerPageOffset(aData, nData);
      if( nByte<=nFree ) break;

      /* Otherwise, this page is full. Set the right-hand-child pointer
      ** to iPtr and release it.  */
      lsmPutU64(&aData[SEGMENT_POINTER_OFFSET(nData)], iPtr);
      assert( lsmFsPageNumber(pOld)==0 );
      rc = lsmFsPagePersist(pOld);
      if( rc==LSM_OK ){
        iPtr = lsmFsPageNumber(pOld);
        lsmFsPageRelease(pOld);
      }
    }

    /* Allocate a new page for apHier[iLevel]. */
    p->apHier[iLevel] = 0;
    if( rc==LSM_OK ){
      rc = lsmFsSortedAppend(
          pDb->pFS, pDb->pWorker, pMW->pLevel, 1, &p->apHier[iLevel]
      );
    }
    if( rc!=LSM_OK ) return rc;

    aData = fsPageData(p->apHier[iLevel], &nData);
    memset(aData, 0, nData);
    lsmPutU16(&aData[SEGMENT_FLAGS_OFFSET(nData)], SEGMENT_BTREE_FLAG);
    lsmPutU16(&aData[SEGMENT_NRECORD_OFFSET(nData)], 0);

    if( iLevel==p->nHier ){
      p->nHier++;
      break;
    }
  }

  /* Write the key into page apHier[iLevel]. */
  aData = fsPageData(p->apHier[iLevel], &nData);
  iOff = mergeWorkerPageOffset(aData, nData);
  nRec = pageGetNRec(aData, nData);
  lsmPutU16(&aData[SEGMENT_CELLPTR_OFFSET(nData, nRec)], (u16)iOff);
  lsmPutU16(&aData[SEGMENT_NRECORD_OFFSET(nData)], (u16)(nRec+1));
  if( eType==0 ){
    aData[iOff++] = 0x00;
    iOff += lsmVarintPut32(&aData[iOff], (int)iPtr);
    iOff += lsmVarintPut32(&aData[iOff], (int)iKeyPg);
  }else{
    aData[iOff++] = eType;
    iOff += lsmVarintPut32(&aData[iOff], (int)iPtr);
    iOff += lsmVarintPut32(&aData[iOff], nKey);
    memcpy(&aData[iOff], pKey, nKey);
  }

  return rc;
}