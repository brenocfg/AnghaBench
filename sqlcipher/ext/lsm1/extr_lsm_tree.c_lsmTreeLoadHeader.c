#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  treehdr; TYPE_2__* pShmhdr; } ;
typedef  TYPE_1__ lsm_db ;
typedef  int /*<<< orphan*/  TreeHeader ;
struct TYPE_6__ {int /*<<< orphan*/  hdr2; int /*<<< orphan*/  hdr1; } ;
typedef  TYPE_2__ ShmHeader ;

/* Variables and functions */
 int LSM_ATTEMPTS_BEFORE_PROTOCOL ; 
 int LSM_OK ; 
 int LSM_PROTOCOL_BKPT ; 
 int /*<<< orphan*/  lsmShmBarrier (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ treeHeaderChecksumOk (int /*<<< orphan*/ *) ; 

int lsmTreeLoadHeader(lsm_db *pDb, int *piRead){
  int nRem = LSM_ATTEMPTS_BEFORE_PROTOCOL;
  while( (nRem--)>0 ){
    ShmHeader *pShm = pDb->pShmhdr;

    memcpy(&pDb->treehdr, &pShm->hdr1, sizeof(TreeHeader));
    if( treeHeaderChecksumOk(&pDb->treehdr) ){
      if( piRead ) *piRead = 1;
      return LSM_OK;
    }
    memcpy(&pDb->treehdr, &pShm->hdr2, sizeof(TreeHeader));
    if( treeHeaderChecksumOk(&pDb->treehdr) ){
      if( piRead ) *piRead = 2;
      return LSM_OK;
    }

    lsmShmBarrier(pDb);
  }
  return LSM_PROTOCOL_BKPT;
}