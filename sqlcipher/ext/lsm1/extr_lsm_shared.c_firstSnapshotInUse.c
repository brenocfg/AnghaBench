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
struct TYPE_6__ {TYPE_3__* pShmhdr; } ;
typedef  TYPE_1__ lsm_db ;
typedef  scalar_t__ i64 ;
struct TYPE_8__ {TYPE_2__* aReader; } ;
struct TYPE_7__ {scalar_t__ iLsmId; } ;
typedef  TYPE_2__ ShmReader ;
typedef  TYPE_3__ ShmHeader ;

/* Variables and functions */
 int LSM_BUSY ; 
 int /*<<< orphan*/  LSM_LOCK_EXCL ; 
 int LSM_LOCK_NREADER ; 
 int /*<<< orphan*/  LSM_LOCK_READER (int) ; 
 int /*<<< orphan*/  LSM_LOCK_UNLOCK ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int lsmShmLock (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int firstSnapshotInUse(
  lsm_db *db,                     /* Database handle */
  i64 *piInUse                    /* IN/OUT: Smallest snapshot id in use */
){
  ShmHeader *pShm = db->pShmhdr;
  i64 iInUse = *piInUse;
  int i;

  assert( iInUse>0 );
  for(i=0; i<LSM_LOCK_NREADER; i++){
    ShmReader *p = &pShm->aReader[i];
    if( p->iLsmId ){
      i64 iThis = p->iLsmId;
      if( iThis!=0 && iInUse>iThis ){
        int rc = lsmShmLock(db, LSM_LOCK_READER(i), LSM_LOCK_EXCL, 0);
        if( rc==LSM_OK ){
          p->iLsmId = 0;
          lsmShmLock(db, LSM_LOCK_READER(i), LSM_LOCK_UNLOCK, 0);
        }else if( rc==LSM_BUSY ){
          iInUse = iThis;
        }else{
          /* Some error other than LSM_BUSY. Return the error code to
          ** the caller in this case.  */
          return rc;
        }
      }
    }
  }

  *piInUse = iInUse;
  return LSM_OK;
}