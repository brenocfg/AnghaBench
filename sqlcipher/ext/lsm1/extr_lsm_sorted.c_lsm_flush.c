#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ nTransOpen; scalar_t__ pCsr; } ;
typedef  TYPE_1__ lsm_db ;

/* Variables and functions */
 int LSM_MISUSE_BKPT ; 
 int LSM_OK ; 
 int lsmBeginWriteTrans (TYPE_1__*) ; 
 int /*<<< orphan*/  lsmFinishReadTrans (TYPE_1__*) ; 
 int lsmFinishWriteTrans (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lsmFlushTreeToDisk (TYPE_1__*) ; 
 int /*<<< orphan*/  lsmTreeDiscardOld (TYPE_1__*) ; 
 int /*<<< orphan*/  lsmTreeMakeOld (TYPE_1__*) ; 

int lsm_flush(lsm_db *db){
  int rc;

  if( db->nTransOpen>0 || db->pCsr ){
    rc = LSM_MISUSE_BKPT;
  }else{
    rc = lsmBeginWriteTrans(db);
    if( rc==LSM_OK ){
      lsmFlushTreeToDisk(db);
      lsmTreeDiscardOld(db);
      lsmTreeMakeOld(db);
      lsmTreeDiscardOld(db);
    }

    if( rc==LSM_OK ){
      rc = lsmFinishWriteTrans(db, 1);
    }else{
      lsmFinishWriteTrans(db, 0);
    }
    lsmFinishReadTrans(db);
  }

  return rc;
}