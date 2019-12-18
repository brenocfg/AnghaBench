#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_8__ {scalar_t__ bUseLog; TYPE_2__* pLogWriter; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_10__ {int n; int nAlloc; int /*<<< orphan*/ * z; } ;
struct TYPE_9__ {TYPE_3__ buf; } ;
typedef  TYPE_2__ LogWriter ;

/* Variables and functions */
 int LSM_CKSUM_MAXDATA ; 
 int LSM_DELETE ; 
 int LSM_DRANGE ; 
 int LSM_LOG_DELETE ; 
 int LSM_LOG_DELETE_CKSUM ; 
 int LSM_LOG_DRANGE ; 
 int LSM_LOG_DRANGE_CKSUM ; 
 int LSM_LOG_WRITE ; 
 int LSM_LOG_WRITE_CKSUM ; 
 int LSM_OK ; 
 int LSM_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int jumpIfRequired (TYPE_1__*,TYPE_2__*,int,int*) ; 
 int logCksumAndFlush (TYPE_1__*) ; 
 int lsmStringExtend (TYPE_3__*,int) ; 
 int lsmVarintLen32 (int) ; 
 int /*<<< orphan*/  lsmVarintPut32 (int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,void*,int) ; 

int lsmLogWrite(
  lsm_db *pDb,                    /* Database handle */
  int eType,
  void *pKey, int nKey,           /* Database key to write to log */
  void *pVal, int nVal            /* Database value (or nVal<0) to write */
){
  int rc = LSM_OK;
  LogWriter *pLog;                /* Log object to write to */
  int nReq;                       /* Bytes of space required in log */
  int bCksum = 0;                 /* True to embed a checksum in this record */

  assert( eType==LSM_WRITE || eType==LSM_DELETE || eType==LSM_DRANGE );
  assert( LSM_LOG_WRITE==LSM_WRITE );
  assert( LSM_LOG_DELETE==LSM_DELETE );
  assert( LSM_LOG_DRANGE==LSM_DRANGE );
  assert( (eType==LSM_LOG_DELETE)==(nVal<0) );

  if( pDb->bUseLog==0 ) return LSM_OK;
  pLog = pDb->pLogWriter;

  /* Determine how many bytes of space are required, assuming that a checksum
  ** will be embedded in this record (even though it may not be).  */
  nReq = 1 + lsmVarintLen32(nKey) + 8 + nKey;
  if( eType!=LSM_LOG_DELETE ) nReq += lsmVarintLen32(nVal) + nVal;

  /* Jump over the jump region if required. Set bCksum to true to tell the
  ** code below to include a checksum in the record if either (a) writing
  ** this record would mean that more than LSM_CKSUM_MAXDATA bytes of data
  ** have been written to the log since the last checksum, or (b) the jump
  ** is taken.  */
  rc = jumpIfRequired(pDb, pLog, nReq, &bCksum);
  if( (pLog->buf.n+nReq) > LSM_CKSUM_MAXDATA ) bCksum = 1;

  if( rc==LSM_OK ){
    rc = lsmStringExtend(&pLog->buf, nReq);
  }
  if( rc==LSM_OK ){
    u8 *a = (u8 *)&pLog->buf.z[pLog->buf.n];
    
    /* Write the record header - the type byte followed by either 1 (for
    ** DELETE) or 2 (for WRITE) varints.  */
    assert( LSM_LOG_WRITE_CKSUM == (LSM_LOG_WRITE | 0x0001) );
    assert( LSM_LOG_DELETE_CKSUM == (LSM_LOG_DELETE | 0x0001) );
    assert( LSM_LOG_DRANGE_CKSUM == (LSM_LOG_DRANGE | 0x0001) );
    *(a++) = (u8)eType | (u8)bCksum;
    a += lsmVarintPut32(a, nKey);
    if( eType!=LSM_LOG_DELETE ) a += lsmVarintPut32(a, nVal);

    if( bCksum ){
      pLog->buf.n = (a - (u8 *)pLog->buf.z);
      rc = logCksumAndFlush(pDb);
      a = (u8 *)&pLog->buf.z[pLog->buf.n];
    }

    memcpy(a, pKey, nKey);
    a += nKey;
    if( eType!=LSM_LOG_DELETE ){
      memcpy(a, pVal, nVal);
      a += nVal;
    }
    pLog->buf.n = a - (u8 *)pLog->buf.z;
    assert( pLog->buf.n<=pLog->buf.nAlloc );
  }

  return rc;
}