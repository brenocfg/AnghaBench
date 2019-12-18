#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  aSz ;
struct TYPE_10__ {int szSector; scalar_t__* aOBuffer; scalar_t__ pCompress; } ;
struct TYPE_9__ {int iLastPg; int nSize; scalar_t__ iFirst; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  TYPE_1__ Segment ;
typedef  int LsmPgno ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fsAppendData (TYPE_2__*,TYPE_1__*,scalar_t__*,int,int*) ; 
 int fsLastPageOnPagesBlock (TYPE_2__*,int) ; 
 scalar_t__ fsPageToBlock (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  putRecordSize (scalar_t__*,int,int) ; 

int lsmFsSortedPadding(
  FileSystem *pFS, 
  Snapshot *pSnapshot,
  Segment *pSeg
){
  int rc = LSM_OK;
  if( pFS->pCompress && pSeg->iFirst ){
    LsmPgno iLast2;
    LsmPgno iLast = pSeg->iLastPg;  /* Current last page of segment */
    int nPad;                       /* Bytes of padding required */
    u8 aSz[3];

    iLast2 = (1 + iLast/pFS->szSector) * pFS->szSector - 1;
    assert( fsPageToBlock(pFS, iLast)==fsPageToBlock(pFS, iLast2) );
    nPad = (int)(iLast2 - iLast);

    if( iLast2>fsLastPageOnPagesBlock(pFS, iLast) ){
      nPad -= 4;
    }
    assert( nPad>=0 );

    if( nPad>=6 ){
      pSeg->nSize += nPad;
      nPad -= 6;
      putRecordSize(aSz, nPad, 1);
      fsAppendData(pFS, pSeg, aSz, sizeof(aSz), &rc);
      memset(pFS->aOBuffer, 0, nPad);
      fsAppendData(pFS, pSeg, pFS->aOBuffer, nPad, &rc);
      fsAppendData(pFS, pSeg, aSz, sizeof(aSz), &rc);
    }else if( nPad>0 ){
      u8 aBuf[5] = {0,0,0,0,0};
      aBuf[0] = (u8)nPad;
      aBuf[nPad-1] = (u8)nPad;
      fsAppendData(pFS, pSeg, aBuf, nPad, &rc);
    }

    assert( rc!=LSM_OK 
        || pSeg->iLastPg==fsLastPageOnPagesBlock(pFS, pSeg->iLastPg)
        || ((pSeg->iLastPg + 1) % pFS->szSector)==0
    );
  }

  return rc;
}