#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/  pFS; TYPE_2__* pLogWriter; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_8__ {size_t n; int /*<<< orphan*/ * z; } ;
struct TYPE_7__ {int iOff; int iCksumBuf; TYPE_3__ buf; int /*<<< orphan*/  cksum1; int /*<<< orphan*/  cksum0; } ;
typedef  TYPE_2__ LogWriter ;

/* Variables and functions */
 int /*<<< orphan*/  logUpdateCksum (TYPE_2__*,size_t) ; 
 int lsmFsWriteLog (int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  lsmPutU32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int logCksumAndFlush(lsm_db *pDb){
  int rc;                         /* Return code */
  LogWriter *pLog = pDb->pLogWriter;

  /* Calculate the checksum value. Append it to the buffer. */
  logUpdateCksum(pLog, pLog->buf.n);
  lsmPutU32((u8 *)&pLog->buf.z[pLog->buf.n], pLog->cksum0);
  pLog->buf.n += 4;
  lsmPutU32((u8 *)&pLog->buf.z[pLog->buf.n], pLog->cksum1);
  pLog->buf.n += 4;

  /* Write the contents of the buffer to disk. */
  rc = lsmFsWriteLog(pDb->pFS, pLog->iOff, &pLog->buf);
  pLog->iOff += pLog->buf.n;
  pLog->iCksumBuf = pLog->buf.n = 0;

  return rc;
}