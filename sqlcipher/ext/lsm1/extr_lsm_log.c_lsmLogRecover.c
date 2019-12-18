#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_36__ {int /*<<< orphan*/  cksum1; int /*<<< orphan*/  cksum0; TYPE_1__* aRegion; } ;
struct TYPE_31__ {TYPE_7__ log; } ;
struct TYPE_33__ {scalar_t__ bRoTrans; int /*<<< orphan*/  pEnv; TYPE_3__* pShmhdr; TYPE_2__ treehdr; } ;
typedef  TYPE_4__ lsm_db ;
struct TYPE_34__ {int n; scalar_t__ z; } ;
struct TYPE_35__ {int iOff; int iBuf; TYPE_5__ buf; int /*<<< orphan*/  cksum1; int /*<<< orphan*/  cksum0; } ;
struct TYPE_32__ {int /*<<< orphan*/  aSnap2; } ;
struct TYPE_30__ {scalar_t__ iStart; int iEnd; } ;
typedef  TYPE_5__ LsmString ;
typedef  TYPE_6__ LogReader ;
typedef  TYPE_7__ DbLog ;

/* Variables and functions */
#define  LSM_LOG_COMMIT 137 
#define  LSM_LOG_DELETE 136 
#define  LSM_LOG_DELETE_CKSUM 135 
#define  LSM_LOG_DRANGE 134 
#define  LSM_LOG_DRANGE_CKSUM 133 
#define  LSM_LOG_JUMP 132 
#define  LSM_LOG_PAD1 131 
#define  LSM_LOG_PAD2 130 
#define  LSM_LOG_WRITE 129 
#define  LSM_LOG_WRITE_CKSUM 128 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  logReaderBlob (TYPE_6__*,TYPE_5__*,int,int**,int*) ; 
 int /*<<< orphan*/  logReaderByte (TYPE_6__*,int*,int*) ; 
 int /*<<< orphan*/  logReaderCksum (TYPE_6__*,TYPE_5__*,int*,int*) ; 
 int /*<<< orphan*/  logReaderInit (TYPE_4__*,TYPE_7__*,int,TYPE_6__*) ; 
 int /*<<< orphan*/  logReaderVarint (TYPE_6__*,TYPE_5__*,int*,int*) ; 
 int logRequireCksum (TYPE_6__*,int) ; 
 int /*<<< orphan*/  lsmCheckpointLogoffset (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  lsmCheckpointZeroLogoffset (TYPE_4__*) ; 
 int lsmFinishRecovery (TYPE_4__*) ; 
 int /*<<< orphan*/  lsmFsCloseLog (TYPE_4__*) ; 
 int lsmFsOpenLog (TYPE_4__*,int*) ; 
 int /*<<< orphan*/  lsmStringClear (TYPE_5__*) ; 
 int /*<<< orphan*/  lsmStringInit (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int lsmTreeDelete (TYPE_4__*,int*,int,int*,int) ; 
 int lsmTreeInit (TYPE_4__*) ; 
 int lsmTreeInsert (TYPE_4__*,int*,int,int*,int) ; 

int lsmLogRecover(lsm_db *pDb){
  LsmString buf1;                 /* Key buffer */
  LsmString buf2;                 /* Value buffer */
  LogReader reader;               /* Log reader object */
  int rc = LSM_OK;                /* Return code */
  int nCommit = 0;                /* Number of transactions to recover */
  int iPass;
  int nJump = 0;                  /* Number of LSM_LOG_JUMP records in pass 0 */
  DbLog *pLog;
  int bOpen;

  rc = lsmFsOpenLog(pDb, &bOpen);
  if( rc!=LSM_OK ) return rc;

  rc = lsmTreeInit(pDb);
  if( rc!=LSM_OK ) return rc;

  pLog = &pDb->treehdr.log;
  lsmCheckpointLogoffset(pDb->pShmhdr->aSnap2, pLog);

  logReaderInit(pDb, pLog, 1, &reader);
  lsmStringInit(&buf1, pDb->pEnv);
  lsmStringInit(&buf2, pDb->pEnv);

  /* The outer for() loop runs at most twice. The first iteration is to 
  ** count the number of committed transactions in the log. The second 
  ** iterates through those transactions and updates the in-memory tree 
  ** structure with their contents.  */
  if( bOpen ){
    for(iPass=0; iPass<2 && rc==LSM_OK; iPass++){
      int bEof = 0;

      while( rc==LSM_OK && !bEof ){
        u8 eType = 0;
        logReaderByte(&reader, &eType, &rc);

        switch( eType ){
          case LSM_LOG_PAD1:
            break;

          case LSM_LOG_PAD2: {
            int nPad;
            logReaderVarint(&reader, &buf1, &nPad, &rc);
            logReaderBlob(&reader, &buf1, nPad, 0, &rc);
            break;
          }

          case LSM_LOG_DRANGE:
          case LSM_LOG_DRANGE_CKSUM:
          case LSM_LOG_WRITE:
          case LSM_LOG_WRITE_CKSUM: {
            int nKey;
            int nVal;
            u8 *aVal;
            logReaderVarint(&reader, &buf1, &nKey, &rc);
            logReaderVarint(&reader, &buf2, &nVal, &rc);

            if( eType==LSM_LOG_WRITE_CKSUM || eType==LSM_LOG_DRANGE_CKSUM ){
              logReaderCksum(&reader, &buf1, &bEof, &rc);
            }else{
              bEof = logRequireCksum(&reader, nKey+nVal);
            }
            if( bEof ) break;

            logReaderBlob(&reader, &buf1, nKey, 0, &rc);
            logReaderBlob(&reader, &buf2, nVal, &aVal, &rc);
            if( iPass==1 && rc==LSM_OK ){ 
              if( eType==LSM_LOG_WRITE || eType==LSM_LOG_WRITE_CKSUM ){
                rc = lsmTreeInsert(pDb, (u8 *)buf1.z, nKey, aVal, nVal);
              }else{
                rc = lsmTreeDelete(pDb, (u8 *)buf1.z, nKey, aVal, nVal);
              }
            }
            break;
          }

          case LSM_LOG_DELETE:
          case LSM_LOG_DELETE_CKSUM: {
            int nKey; u8 *aKey;
            logReaderVarint(&reader, &buf1, &nKey, &rc);

            if( eType==LSM_LOG_DELETE_CKSUM ){
              logReaderCksum(&reader, &buf1, &bEof, &rc);
            }else{
              bEof = logRequireCksum(&reader, nKey);
            }
            if( bEof ) break;

            logReaderBlob(&reader, &buf1, nKey, &aKey, &rc);
            if( iPass==1 && rc==LSM_OK ){ 
              rc = lsmTreeInsert(pDb, aKey, nKey, NULL, -1);
            }
            break;
          }

          case LSM_LOG_COMMIT:
            logReaderCksum(&reader, &buf1, &bEof, &rc);
            if( bEof==0 ){
              nCommit++;
              assert( nCommit>0 || iPass==1 );
              if( nCommit==0 ) bEof = 1;
            }
            break;

          case LSM_LOG_JUMP: {
            int iOff = 0;
            logReaderVarint(&reader, &buf1, &iOff, &rc);
            if( rc==LSM_OK ){
              if( iPass==1 ){
                if( pLog->aRegion[2].iStart==0 ){
                  assert( pLog->aRegion[1].iStart==0 );
                  pLog->aRegion[1].iEnd = reader.iOff;
                }else{
                  assert( pLog->aRegion[0].iStart==0 );
                  pLog->aRegion[0].iStart = pLog->aRegion[2].iStart;
                  pLog->aRegion[0].iEnd = reader.iOff-reader.buf.n+reader.iBuf;
                }
                pLog->aRegion[2].iStart = iOff;
              }else{
                if( (nJump++)==2 ){
                  bEof = 1;
                }
              }

              reader.iOff = iOff;
              reader.buf.n = reader.iBuf;
            }
            break;
          }

          default:
            /* Including LSM_LOG_EOF */
            bEof = 1;
            break;
        }
      }

      if( rc==LSM_OK && iPass==0 ){
        if( nCommit==0 ){
          if( pLog->aRegion[2].iStart==0 ){
            iPass = 1;
          }else{
            pLog->aRegion[2].iStart = 0;
            iPass = -1;
            lsmCheckpointZeroLogoffset(pDb);
          }
        }
        logReaderInit(pDb, pLog, 0, &reader);
        nCommit = nCommit * -1;
      }
    }
  }

  /* Initialize DbLog object */
  if( rc==LSM_OK ){
    pLog->aRegion[2].iEnd = reader.iOff - reader.buf.n + reader.iBuf;
    pLog->cksum0 = reader.cksum0;
    pLog->cksum1 = reader.cksum1;
  }

  if( rc==LSM_OK ){
    rc = lsmFinishRecovery(pDb);
  }else{
    lsmFinishRecovery(pDb);
  }

  if( pDb->bRoTrans ){
    lsmFsCloseLog(pDb);
  }

  lsmStringClear(&buf1);
  lsmStringClear(&buf2);
  lsmStringClear(&reader.buf);
  return rc;
}