#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const u8 ;
typedef  int /*<<< orphan*/  aPtr ;
struct TYPE_11__ {int pCompress; int nBlocksize; int /*<<< orphan*/  fdDb; int /*<<< orphan*/  pEnv; int /*<<< orphan*/  pDb; } ;
struct TYPE_10__ {int iLastPg; int iFirst; scalar_t__ pRedirect; } ;
typedef  TYPE_1__ Segment ;
typedef  int LsmPgno ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int LSM_MIN (int,int) ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int findAppendPoint (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int fsBlockNext (TYPE_2__*,int /*<<< orphan*/ ,int,int*) ; 
 int fsFirstPageOnBlock (TYPE_2__*,int) ; 
 int fsLastPageOnPagesBlock (TYPE_2__*,int) ; 
 int fsPageToBlock (TYPE_2__*,int) ; 
 int lsmBlockAllocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int lsmEnvWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  lsmPutU32 (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static LsmPgno fsAppendData(
  FileSystem *pFS,                /* File-system handle */
  Segment *pSeg,                  /* Segment to append to */
  const u8 *aData,                /* Buffer containing data to write */
  int nData,                      /* Size of buffer aData[] in bytes */
  int *pRc                        /* IN/OUT: Error code */
){
  LsmPgno iRet = 0;
  int rc = *pRc;
  assert( pFS->pCompress );
  if( rc==LSM_OK ){
    int nRem = 0;
    int nWrite = 0;
    LsmPgno iLastOnBlock;
    LsmPgno iApp = pSeg->iLastPg+1;

    /* If this is the first data written into the segment, find an append-point
    ** or allocate a new block.  */
    if( iApp==1 ){
      pSeg->iFirst = iApp = findAppendPoint(pFS, 0);
      if( iApp==0 ){
        int iBlk;
        rc = lsmBlockAllocate(pFS->pDb, 0, &iBlk);
        pSeg->iFirst = iApp = fsFirstPageOnBlock(pFS, iBlk);
      }
    }
    iRet = iApp;

    /* Write as much data as is possible at iApp (usually all of it). */
    iLastOnBlock = fsLastPageOnPagesBlock(pFS, iApp);
    if( rc==LSM_OK ){
      int nSpace = (int)(iLastOnBlock - iApp + 1);
      nWrite = LSM_MIN(nData, nSpace);
      nRem = nData - nWrite;
      assert( nWrite>=0 );
      if( nWrite!=0 ){
        rc = lsmEnvWrite(pFS->pEnv, pFS->fdDb, iApp, aData, nWrite);
      }
      iApp += nWrite;
    }

    /* If required, allocate a new block and write the rest of the data
    ** into it. Set the next and previous block pointers to link the new
    ** block to the old.  */
    assert( nRem<=0 || (iApp-1)==iLastOnBlock );
    if( rc==LSM_OK && (iApp-1)==iLastOnBlock ){
      u8 aPtr[4];                 /* Space to serialize a u32 */
      int iBlk;                   /* New block number */

      if( nWrite>0 ){
        /* Allocate a new block. */
        rc = lsmBlockAllocate(pFS->pDb, 0, &iBlk);

        /* Set the "next" pointer on the old block */
        if( rc==LSM_OK ){
          assert( iApp==(fsPageToBlock(pFS, iApp)*pFS->nBlocksize)-4 );
          lsmPutU32(aPtr, iBlk);
          rc = lsmEnvWrite(pFS->pEnv, pFS->fdDb, iApp, aPtr, sizeof(aPtr));
        }

        /* Set the "prev" pointer on the new block */
        if( rc==LSM_OK ){
          LsmPgno iWrite;
          lsmPutU32(aPtr, fsPageToBlock(pFS, iApp));
          iWrite = fsFirstPageOnBlock(pFS, iBlk);
          rc = lsmEnvWrite(pFS->pEnv, pFS->fdDb, iWrite-4, aPtr, sizeof(aPtr));
          if( nRem>0 ) iApp = iWrite;
        }
      }else{
        /* The next block is already allocated. */
        assert( nRem>0 );
        assert( pSeg->pRedirect==0 );
        rc = fsBlockNext(pFS, 0, fsPageToBlock(pFS, iApp), &iBlk);
        iRet = iApp = fsFirstPageOnBlock(pFS, iBlk);
      }

      /* Write the remaining data into the new block */
      if( rc==LSM_OK && nRem>0 ){
        rc = lsmEnvWrite(pFS->pEnv, pFS->fdDb, iApp, &aData[nWrite], nRem);
        iApp += nRem;
      }
    }

    pSeg->iLastPg = iApp-1;
    *pRc = rc;
  }

  return iRet;
}