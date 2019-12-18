#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ bUseLog; TYPE_3__* pLogWriter; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_10__ {int iOff; int nBuf; int /*<<< orphan*/  cksum1; int /*<<< orphan*/  cksum0; int /*<<< orphan*/  aBuf; } ;
struct TYPE_7__ {int n; int /*<<< orphan*/  z; } ;
struct TYPE_9__ {int iOff; int iCksumBuf; int iRegion1End; int iRegion2Start; int /*<<< orphan*/  cksum1; int /*<<< orphan*/  cksum0; TYPE_1__ buf; } ;
typedef  TYPE_3__ LogWriter ;
typedef  TYPE_4__ LogMark ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void lsmLogSeek(
  lsm_db *pDb,                    /* Database handle */
  LogMark *pMark                  /* Object containing log offset to seek to */
){
  LogWriter *pLog;

  if( pDb->bUseLog==0 ) return;
  pLog = pDb->pLogWriter;

  assert( pMark->iOff<=pLog->iOff+pLog->buf.n );
  if( (pMark->iOff & 0xFFFFFFF8)>=pLog->iOff ){
    pLog->buf.n = (int)(pMark->iOff - pLog->iOff);
    pLog->iCksumBuf = (pLog->buf.n & 0xFFFFFFF8);
  }else{
    pLog->buf.n = pMark->nBuf;
    memcpy(pLog->buf.z, pMark->aBuf, pMark->nBuf);
    pLog->iCksumBuf = 0;
    pLog->iOff = pMark->iOff - pMark->nBuf;
  }
  pLog->cksum0 = pMark->cksum0;
  pLog->cksum1 = pMark->cksum1;

  if( pMark->iOff > pLog->iRegion1End ) pLog->iRegion1End = 0;
  if( pMark->iOff > pLog->iRegion2Start ) pLog->iRegion2Start = 0;
}