#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  nMerge; } ;
typedef  TYPE_1__ lsm_db ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  TREE_BOTH ; 
 int lsmBeginWork (TYPE_1__*) ; 
 int /*<<< orphan*/  lsmFinishWork (TYPE_1__*,int,int*) ; 
 scalar_t__ sortedDbIsFull (TYPE_1__*) ; 
 int sortedNewToplevel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sortedWork (TYPE_1__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int lsmFlushTreeToDisk(lsm_db *pDb){
  int rc;

  rc = lsmBeginWork(pDb);
  while( rc==LSM_OK && sortedDbIsFull(pDb) ){
    rc = sortedWork(pDb, 256, pDb->nMerge, 1, 0);
  }

  if( rc==LSM_OK ){
    rc = sortedNewToplevel(pDb, TREE_BOTH, 0);
  }

  lsmFinishWork(pDb, 1, &rc);
  return rc;
}