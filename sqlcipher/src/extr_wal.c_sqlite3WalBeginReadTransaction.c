#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ mxFrame; struct TYPE_16__* aSalt; } ;
typedef  TYPE_1__ WalIndexHdr ;
struct TYPE_17__ {scalar_t__* aReadMark; scalar_t__ nBackfillAttempted; } ;
typedef  TYPE_2__ WalCkptInfo ;
struct TYPE_15__ {scalar_t__ mxFrame; struct TYPE_15__* aSalt; } ;
struct TYPE_18__ {size_t readLock; int minFrame; TYPE_11__ hdr; TYPE_1__* pSnapshot; } ;
typedef  TYPE_3__ Wal ;

/* Variables and functions */
 int SQLITE_BUSY ; 
 int SQLITE_ERROR_SNAPSHOT ; 
 int SQLITE_IOERR ; 
 int SQLITE_OK ; 
 int SQLITE_PROTOCOL ; 
 int /*<<< orphan*/  WAL_CKPT_LOCK ; 
 int WAL_RETRY ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (TYPE_1__*,TYPE_11__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_11__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  sqlite3WalEndReadTransaction (TYPE_3__*) ; 
 int /*<<< orphan*/  testcase (int) ; 
 TYPE_2__* walCkptInfo (TYPE_3__*) ; 
 int walLockShared (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int walTryBeginRead (TYPE_3__*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  walUnlockShared (TYPE_3__*,int /*<<< orphan*/ ) ; 

int sqlite3WalBeginReadTransaction(Wal *pWal, int *pChanged){
  int rc;                         /* Return code */
  int cnt = 0;                    /* Number of TryBeginRead attempts */

#ifdef SQLITE_ENABLE_SNAPSHOT
  int bChanged = 0;
  WalIndexHdr *pSnapshot = pWal->pSnapshot;
  if( pSnapshot && memcmp(pSnapshot, &pWal->hdr, sizeof(WalIndexHdr))!=0 ){
    bChanged = 1;
  }
#endif

  do{
    rc = walTryBeginRead(pWal, pChanged, 0, ++cnt);
  }while( rc==WAL_RETRY );
  testcase( (rc&0xff)==SQLITE_BUSY );
  testcase( (rc&0xff)==SQLITE_IOERR );
  testcase( rc==SQLITE_PROTOCOL );
  testcase( rc==SQLITE_OK );

#ifdef SQLITE_ENABLE_SNAPSHOT
  if( rc==SQLITE_OK ){
    if( pSnapshot && memcmp(pSnapshot, &pWal->hdr, sizeof(WalIndexHdr))!=0 ){
      /* At this point the client has a lock on an aReadMark[] slot holding
      ** a value equal to or smaller than pSnapshot->mxFrame, but pWal->hdr
      ** is populated with the wal-index header corresponding to the head
      ** of the wal file. Verify that pSnapshot is still valid before
      ** continuing.  Reasons why pSnapshot might no longer be valid:
      **
      **    (1)  The WAL file has been reset since the snapshot was taken.
      **         In this case, the salt will have changed.
      **
      **    (2)  A checkpoint as been attempted that wrote frames past
      **         pSnapshot->mxFrame into the database file.  Note that the
      **         checkpoint need not have completed for this to cause problems.
      */
      volatile WalCkptInfo *pInfo = walCkptInfo(pWal);

      assert( pWal->readLock>0 || pWal->hdr.mxFrame==0 );
      assert( pInfo->aReadMark[pWal->readLock]<=pSnapshot->mxFrame );

      /* It is possible that there is a checkpointer thread running 
      ** concurrent with this code. If this is the case, it may be that the
      ** checkpointer has already determined that it will checkpoint 
      ** snapshot X, where X is later in the wal file than pSnapshot, but 
      ** has not yet set the pInfo->nBackfillAttempted variable to indicate 
      ** its intent. To avoid the race condition this leads to, ensure that
      ** there is no checkpointer process by taking a shared CKPT lock 
      ** before checking pInfo->nBackfillAttempted.  
      **
      ** TODO: Does the aReadMark[] lock prevent a checkpointer from doing
      **       this already?
      */
      rc = walLockShared(pWal, WAL_CKPT_LOCK);

      if( rc==SQLITE_OK ){
        /* Check that the wal file has not been wrapped. Assuming that it has
        ** not, also check that no checkpointer has attempted to checkpoint any
        ** frames beyond pSnapshot->mxFrame. If either of these conditions are
        ** true, return SQLITE_ERROR_SNAPSHOT. Otherwise, overwrite pWal->hdr
        ** with *pSnapshot and set *pChanged as appropriate for opening the
        ** snapshot.  */
        if( !memcmp(pSnapshot->aSalt, pWal->hdr.aSalt, sizeof(pWal->hdr.aSalt))
         && pSnapshot->mxFrame>=pInfo->nBackfillAttempted
        ){
          assert( pWal->readLock>0 );
          memcpy(&pWal->hdr, pSnapshot, sizeof(WalIndexHdr));
          *pChanged = bChanged;
        }else{
          rc = SQLITE_ERROR_SNAPSHOT;
        }

        /* Release the shared CKPT lock obtained above. */
        walUnlockShared(pWal, WAL_CKPT_LOCK);
        pWal->minFrame = 1;
      }


      if( rc!=SQLITE_OK ){
        sqlite3WalEndReadTransaction(pWal);
      }
    }
  }
#endif
  return rc;
}