#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int nTransOpen; int nTransAlloc; TYPE_2__* aTrans; int /*<<< orphan*/  pEnv; scalar_t__ bReadonly; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_11__ {int /*<<< orphan*/  log; int /*<<< orphan*/  tree; } ;
typedef  TYPE_2__ TransMark ;

/* Variables and functions */
 int LSM_NOMEM ; 
 int LSM_OK ; 
 int LSM_READONLY ; 
 int /*<<< orphan*/  assert_db_state (TYPE_1__*) ; 
 int lsmBeginWriteTrans (TYPE_1__*) ; 
 int /*<<< orphan*/  lsmLogTell (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ lsmRealloc (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  lsmTreeMark (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int lsm_begin(lsm_db *pDb, int iLevel){
  int rc;

  assert_db_state( pDb );
  rc = (pDb->bReadonly ? LSM_READONLY : LSM_OK);

  /* A value less than zero means open one more transaction. */
  if( iLevel<0 ) iLevel = pDb->nTransOpen + 1;
  if( iLevel>pDb->nTransOpen ){
    int i;

    /* Extend the pDb->aTrans[] array if required. */
    if( rc==LSM_OK && pDb->nTransAlloc<iLevel ){
      TransMark *aNew;            /* New allocation */
      int nByte = sizeof(TransMark) * (iLevel+1);
      aNew = (TransMark *)lsmRealloc(pDb->pEnv, pDb->aTrans, nByte);
      if( !aNew ){
        rc = LSM_NOMEM;
      }else{
        nByte = sizeof(TransMark) * (iLevel+1 - pDb->nTransAlloc);
        memset(&aNew[pDb->nTransAlloc], 0, nByte);
        pDb->nTransAlloc = iLevel+1;
        pDb->aTrans = aNew;
      }
    }

    if( rc==LSM_OK && pDb->nTransOpen==0 ){
      rc = lsmBeginWriteTrans(pDb);
    }

    if( rc==LSM_OK ){
      for(i=pDb->nTransOpen; i<iLevel; i++){
        lsmTreeMark(pDb, &pDb->aTrans[i].tree);
        lsmLogTell(pDb, &pDb->aTrans[i].log);
      }
      pDb->nTransOpen = iLevel;
    }
  }

  return rc;
}