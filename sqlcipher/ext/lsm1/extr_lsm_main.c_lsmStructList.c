#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_14__ {int nRight; int /*<<< orphan*/ * aRhs; int /*<<< orphan*/  lhs; scalar_t__ iAge; struct TYPE_14__* pNext; } ;
struct TYPE_13__ {scalar_t__ n; char* z; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  TYPE_2__ LsmString ;
typedef  TYPE_3__ Level ;

/* Variables and functions */
 int LSM_NOMEM ; 
 int LSM_OK ; 
 int /*<<< orphan*/  infoFreeWorker (TYPE_1__*,int) ; 
 int infoGetWorker (TYPE_1__*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  lsmAppendSegmentList (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 TYPE_3__* lsmDbSnapshotLevel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmStringAppend (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  lsmStringAppendf (TYPE_2__*,char*,char*,int) ; 
 int /*<<< orphan*/  lsmStringInit (TYPE_2__*,int /*<<< orphan*/ ) ; 

int lsmStructList(
  lsm_db *pDb,                    /* Database handle */
  char **pzOut                    /* OUT: Nul-terminated string (tcl list) */
){
  Level *pTopLevel = 0;           /* Top level of snapshot to report on */
  int rc = LSM_OK;
  Level *p;
  LsmString s;
  Snapshot *pWorker;              /* Worker snapshot */
  int bUnlock = 0;

  /* Obtain the worker snapshot */
  rc = infoGetWorker(pDb, &pWorker, &bUnlock);
  if( rc!=LSM_OK ) return rc;

  /* Format the contents of the snapshot as text */
  pTopLevel = lsmDbSnapshotLevel(pWorker);
  lsmStringInit(&s, pDb->pEnv);
  for(p=pTopLevel; rc==LSM_OK && p; p=p->pNext){
    int i;
    lsmStringAppendf(&s, "%s{%d", (s.n ? " " : ""), (int)p->iAge);
    lsmAppendSegmentList(&s, " ", &p->lhs);
    for(i=0; rc==LSM_OK && i<p->nRight; i++){
      lsmAppendSegmentList(&s, " ", &p->aRhs[i]);
    }
    lsmStringAppend(&s, "}", 1);
  }
  rc = s.n>=0 ? LSM_OK : LSM_NOMEM;

  /* Release the snapshot and return */
  infoFreeWorker(pDb, bUnlock);
  *pzOut = s.z;
  return rc;
}