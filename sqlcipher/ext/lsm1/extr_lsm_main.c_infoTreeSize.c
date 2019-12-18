#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_5__* pShmhdr; } ;
typedef  TYPE_3__ lsm_db ;
struct TYPE_8__ {scalar_t__ nByte; } ;
struct TYPE_7__ {scalar_t__ nByte; } ;
struct TYPE_10__ {scalar_t__ iOldLog; TYPE_2__ oldroot; scalar_t__ iOldShmid; TYPE_1__ root; } ;
typedef  TYPE_4__ TreeHeader ;
struct TYPE_11__ {int /*<<< orphan*/  aSnap1; TYPE_4__ hdr1; } ;
typedef  TYPE_5__ ShmHeader ;

/* Variables and functions */
 int LSM_OK ; 
 scalar_t__ lsmCheckpointLogOffset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int infoTreeSize(lsm_db *db, int *pnOldKB, int *pnNewKB){
  ShmHeader *pShm = db->pShmhdr;
  TreeHeader *p = &pShm->hdr1;

  /* The following code suffers from two race conditions, as it accesses and
  ** trusts the contents of shared memory without verifying checksums:
  **
  **   * The two values read - TreeHeader.root.nByte and oldroot.nByte - are 
  **     32-bit fields. It is assumed that reading from one of these
  **     is atomic - that it is not possible to read a partially written
  **     garbage value. However the two values may be mutually inconsistent. 
  **
  **   * TreeHeader.iLogOff is a 64-bit value. And lsmCheckpointLogOffset()
  **     reads a 64-bit value from a snapshot stored in shared memory. It
  **     is assumed that in each case it is possible to read a partially
  **     written garbage value. If this occurs, then the value returned
  **     for the size of the "old" tree may reflect the size of an "old"
  **     tree that was recently flushed to disk.
  **
  ** Given the context in which this function is called (as a result of an
  ** lsm_info(LSM_INFO_TREE_SIZE) request), neither of these are considered to
  ** be problems.
  */
  *pnNewKB = ((int)p->root.nByte + 1023) / 1024;
  if( p->iOldShmid ){
    if( p->iOldLog==lsmCheckpointLogOffset(pShm->aSnap1) ){
      *pnOldKB = 0;
    }else{
      *pnOldKB = ((int)p->oldroot.nByte + 1023) / 1024;
    }
  }else{
    *pnOldKB = 0;
  }

  return LSM_OK;
}