#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  aCksum; } ;
struct TYPE_7__ {int /*<<< orphan*/  rollback; int /*<<< orphan*/  pEnv; TYPE_3__ treehdr; TYPE_2__* pShmhdr; } ;
typedef  TYPE_1__ lsm_db ;
typedef  int /*<<< orphan*/  TreeHeader ;
struct TYPE_8__ {scalar_t__ bWriter; int /*<<< orphan*/  hdr1; int /*<<< orphan*/  hdr2; } ;
typedef  TYPE_2__ ShmHeader ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  intArrayFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmShmBarrier (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  treeHeaderChecksum (TYPE_3__*,int /*<<< orphan*/ ) ; 

int lsmTreeEndTransaction(lsm_db *pDb, int bCommit){
  ShmHeader *pShm = pDb->pShmhdr;

  treeHeaderChecksum(&pDb->treehdr, pDb->treehdr.aCksum);
  memcpy(&pShm->hdr2, &pDb->treehdr, sizeof(TreeHeader));
  lsmShmBarrier(pDb);
  memcpy(&pShm->hdr1, &pDb->treehdr, sizeof(TreeHeader));
  pShm->bWriter = 0;
  intArrayFree(pDb->pEnv, &pDb->rollback);

  return LSM_OK;
}