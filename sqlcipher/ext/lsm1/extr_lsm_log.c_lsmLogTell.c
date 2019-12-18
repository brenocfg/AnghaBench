#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ bUseLog; TYPE_3__* pLogWriter; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_11__ {int nBuf; int /*<<< orphan*/  cksum1; int /*<<< orphan*/  cksum0; scalar_t__ iOff; int /*<<< orphan*/  aBuf; } ;
struct TYPE_8__ {int n; int /*<<< orphan*/ * z; } ;
struct TYPE_10__ {int iCksumBuf; int /*<<< orphan*/  cksum1; int /*<<< orphan*/  cksum0; TYPE_1__ buf; scalar_t__ iOff; } ;
typedef  TYPE_3__ LogWriter ;
typedef  TYPE_4__ LogMark ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  logUpdateCksum (TYPE_3__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void lsmLogTell(
  lsm_db *pDb,                    /* Database handle */
  LogMark *pMark                  /* Populate this object with current offset */
){
  LogWriter *pLog;
  int nCksum;

  if( pDb->bUseLog==0 ) return;
  pLog = pDb->pLogWriter;
  nCksum = pLog->buf.n & 0xFFFFFFF8;
  logUpdateCksum(pLog, nCksum);
  assert( pLog->iCksumBuf==nCksum );
  pMark->nBuf = pLog->buf.n - nCksum;
  memcpy(pMark->aBuf, &pLog->buf.z[nCksum], pMark->nBuf);

  pMark->iOff = pLog->iOff + pLog->buf.n;
  pMark->cksum0 = pLog->cksum0;
  pMark->cksum1 = pLog->cksum1;
}