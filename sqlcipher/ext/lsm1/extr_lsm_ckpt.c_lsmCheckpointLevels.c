#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {int /*<<< orphan*/  pEnv; int /*<<< orphan*/  pWorker; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_12__ {scalar_t__ aCkpt; int /*<<< orphan*/  pEnv; } ;
struct TYPE_11__ {struct TYPE_11__* pNext; } ;
typedef  TYPE_2__ Level ;
typedef  TYPE_3__ CkptBuffer ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ckptChangeEndianness (scalar_t__,int) ; 
 int /*<<< orphan*/  ckptExportLevel (TYPE_2__*,TYPE_3__*,int*,int*) ; 
 int /*<<< orphan*/  ckptSetValue (TYPE_3__*,int /*<<< orphan*/ ,int,int*) ; 
 TYPE_2__* lsmDbSnapshotLevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

int lsmCheckpointLevels(
  lsm_db *pDb,                    /* Database handle */
  int nLevel,                     /* Number of levels to write to blob */
  void **paVal,                   /* OUT: Pointer to LEVELS blob */
  int *pnVal                      /* OUT: Size of LEVELS blob in bytes */
){
  Level *p;                       /* Used to iterate through levels */
  int nAll= 0;
  int rc;
  int i;
  int iOut;
  CkptBuffer ckpt;
  assert( nLevel>0 );

  for(p=lsmDbSnapshotLevel(pDb->pWorker); p; p=p->pNext) nAll++;

  assert( nAll>nLevel );
  nAll -= nLevel;
  for(p=lsmDbSnapshotLevel(pDb->pWorker); p && nAll>0; p=p->pNext) nAll--;

  memset(&ckpt, 0, sizeof(CkptBuffer));
  ckpt.pEnv = pDb->pEnv;

  ckptSetValue(&ckpt, 0, nLevel, &rc);
  iOut = 1;
  for(i=0; rc==LSM_OK && i<nLevel; i++){
    ckptExportLevel(p, &ckpt, &iOut, &rc);
    p = p->pNext;
  }
  assert( rc!=LSM_OK || p==0 );

  if( rc==LSM_OK ){
    ckptChangeEndianness(ckpt.aCkpt, iOut);
    *paVal = (void *)ckpt.aCkpt;
    *pnVal = iOut * sizeof(u32);
  }else{
    *pnVal = 0;
    *paVal = 0;
  }

  return rc;
}