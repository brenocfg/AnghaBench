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
struct TYPE_9__ {scalar_t__ iOldLog; } ;
struct TYPE_10__ {TYPE_1__ treehdr; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_12__ {int /*<<< orphan*/ * apTreeCsr; TYPE_2__* pDb; } ;
struct TYPE_11__ {scalar_t__ iLogOff; } ;
typedef  TYPE_3__ Snapshot ;
typedef  TYPE_4__ MultiCursor ;

/* Variables and functions */
 int LSM_OK ; 
 int TREE_BOTH ; 
 int TREE_NONE ; 
 int lsmTreeCursorNew (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ lsmTreeHasOld (TYPE_2__*) ; 

__attribute__((used)) static int multiCursorAddTree(MultiCursor *pCsr, Snapshot *pSnap, int eTree){
  int rc = LSM_OK;
  lsm_db *db = pCsr->pDb;

  /* Add a tree cursor on the 'old' tree, if it exists. */
  if( eTree!=TREE_NONE 
   && lsmTreeHasOld(db) 
   && db->treehdr.iOldLog!=pSnap->iLogOff 
  ){
    rc = lsmTreeCursorNew(db, 1, &pCsr->apTreeCsr[1]);
  }

  /* Add a tree cursor on the 'current' tree, if required. */
  if( rc==LSM_OK && eTree==TREE_BOTH ){
    rc = lsmTreeCursorNew(db, 0, &pCsr->apTreeCsr[0]);
  }

  return rc;
}