#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_10__ {int /*<<< orphan*/  pFS; } ;
typedef  TYPE_2__ lsm_db ;
typedef  void* i64 ;
struct TYPE_12__ {int n; } ;
struct TYPE_9__ {scalar_t__ iStart; void* iEnd; } ;
struct TYPE_11__ {scalar_t__ iOff; scalar_t__ iRegion1End; int iCksumBuf; TYPE_4__ buf; void* iRegion2Start; TYPE_1__ jump; } ;
typedef  TYPE_3__ LogWriter ;

/* Variables and functions */
 scalar_t__ LSM_LOG_JUMP ; 
 scalar_t__ LSM_LOG_PAD1 ; 
 scalar_t__ LSM_LOG_PAD2 ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  logUpdateCksum (TYPE_3__*,int) ; 
 int lsmFsWriteLog (int /*<<< orphan*/ ,scalar_t__,TYPE_4__*) ; 
 int lsmStringBinAppend (TYPE_4__*,scalar_t__*,int) ; 
 int lsmVarintPut64 (scalar_t__*,void*) ; 

__attribute__((used)) static int jumpIfRequired(
  lsm_db *pDb,
  LogWriter *pLog,
  int nReq,
  int *pbJump
){
  /* Determine if it is necessary to add an LSM_LOG_JUMP to jump over the
  ** jump region before writing the LSM_LOG_WRITE or DELETE record. This
  ** is necessary if there is insufficient room between the current offset
  ** and the jump region to fit the new WRITE/DELETE record and the largest
  ** possible JUMP record with up to 7 bytes of padding (a total of 17 
  ** bytes).  */
  if( (pLog->jump.iStart > (pLog->iOff + pLog->buf.n))
   && (pLog->jump.iStart < (pLog->iOff + pLog->buf.n + (nReq + 17))) 
  ){
    int rc;                       /* Return code */
    i64 iJump;                    /* Offset to jump to */
    u8 aJump[10];                 /* Encoded jump record */
    int nJump;                    /* Valid bytes in aJump[] */
    int nPad;                     /* Bytes of padding required */

    /* Serialize the JUMP record */
    iJump = pLog->jump.iEnd+1;
    aJump[0] = LSM_LOG_JUMP;
    nJump = 1 + lsmVarintPut64(&aJump[1], iJump);

    /* Adding padding to the contents of the buffer so that it will be a 
    ** multiple of 8 bytes in size after the JUMP record is appended. This
    ** is not strictly required, it just makes the keeping the running 
    ** checksum up to date in this file a little simpler.  */
    nPad = (pLog->buf.n + nJump) % 8;
    if( nPad ){
      u8 aPad[7] = {0,0,0,0,0,0,0};
      nPad = 8-nPad;
      if( nPad==1 ){
        aPad[0] = LSM_LOG_PAD1;
      }else{
        aPad[0] = LSM_LOG_PAD2;
        aPad[1] = (u8)(nPad-2);
      }
      rc = lsmStringBinAppend(&pLog->buf, aPad, nPad);
      if( rc!=LSM_OK ) return rc;
    }

    /* Append the JUMP record to the buffer. Then flush the buffer to disk
    ** and update the checksums. The next write to the log file (assuming
    ** there is no transaction rollback) will be to offset iJump (just past
    ** the jump region).  */
    rc = lsmStringBinAppend(&pLog->buf, aJump, nJump);
    if( rc!=LSM_OK ) return rc;
    assert( (pLog->buf.n % 8)==0 );
    rc = lsmFsWriteLog(pDb->pFS, pLog->iOff, &pLog->buf);
    if( rc!=LSM_OK ) return rc;
    logUpdateCksum(pLog, pLog->buf.n);
    pLog->iRegion1End = (pLog->iOff + pLog->buf.n);
    pLog->iRegion2Start = iJump;
    pLog->iOff = iJump;
    pLog->iCksumBuf = pLog->buf.n = 0;
    if( pbJump ) *pbJump = 1;
  }

  return LSM_OK;
}