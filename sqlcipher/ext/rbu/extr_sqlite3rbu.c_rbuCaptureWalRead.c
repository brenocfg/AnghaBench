#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ const mLock; int pgsz; size_t nFrame; size_t nFrameAlloc; scalar_t__ iMaxFrame; TYPE_2__* aFrame; int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  int i64 ;
struct TYPE_6__ {scalar_t__ iDbPage; scalar_t__ iWalFrame; } ;
typedef  TYPE_2__ RbuFrame ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_BUSY ; 
 int SQLITE_INTERNAL ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int WAL_LOCK_CKPT ; 
 int WAL_LOCK_READ0 ; 
 int WAL_LOCK_WRITE ; 
 scalar_t__ sqlite3_realloc64 (TYPE_2__*,int) ; 

__attribute__((used)) static int rbuCaptureWalRead(sqlite3rbu *pRbu, i64 iOff, int iAmt){
  const u32 mReq = (1<<WAL_LOCK_WRITE)|(1<<WAL_LOCK_CKPT)|(1<<WAL_LOCK_READ0);
  u32 iFrame;

  if( pRbu->mLock!=mReq ){
    pRbu->rc = SQLITE_BUSY;
    return SQLITE_INTERNAL;
  }

  pRbu->pgsz = iAmt;
  if( pRbu->nFrame==pRbu->nFrameAlloc ){
    int nNew = (pRbu->nFrameAlloc ? pRbu->nFrameAlloc : 64) * 2;
    RbuFrame *aNew;
    aNew = (RbuFrame*)sqlite3_realloc64(pRbu->aFrame, nNew * sizeof(RbuFrame));
    if( aNew==0 ) return SQLITE_NOMEM;
    pRbu->aFrame = aNew;
    pRbu->nFrameAlloc = nNew;
  }

  iFrame = (u32)((iOff-32) / (i64)(iAmt+24)) + 1;
  if( pRbu->iMaxFrame<iFrame ) pRbu->iMaxFrame = iFrame;
  pRbu->aFrame[pRbu->nFrame].iWalFrame = iFrame;
  pRbu->aFrame[pRbu->nFrame].iDbPage = 0;
  pRbu->nFrame++;
  return SQLITE_OK;
}