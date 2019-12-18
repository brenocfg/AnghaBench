#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int iTransId; } ;
struct TYPE_11__ {int iFirst; int nChunk; int iNextShmid; int iUsedShmid; scalar_t__ iWrite; TYPE_1__ root; } ;
struct TYPE_9__ {TYPE_6__ treehdr; } ;
typedef  TYPE_2__ lsm_db ;
typedef  int /*<<< orphan*/  TreeHeader ;
struct TYPE_10__ {int iShmid; scalar_t__ iNext; } ;
typedef  TYPE_3__ ShmChunk ;

/* Variables and functions */
 int LSM_OK ; 
 scalar_t__ LSM_SHM_CHUNK_HDR ; 
 scalar_t__ LSM_SHM_CHUNK_SIZE ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* treeShmChunkRc (TYPE_2__*,int,int*) ; 

int lsmTreeInit(lsm_db *pDb){
  ShmChunk *pOne;
  int rc = LSM_OK;

  memset(&pDb->treehdr, 0, sizeof(TreeHeader));
  pDb->treehdr.root.iTransId = 1;
  pDb->treehdr.iFirst = 1;
  pDb->treehdr.nChunk = 2;
  pDb->treehdr.iWrite = LSM_SHM_CHUNK_SIZE + LSM_SHM_CHUNK_HDR;
  pDb->treehdr.iNextShmid = 2;
  pDb->treehdr.iUsedShmid = 1;

  pOne = treeShmChunkRc(pDb, 1, &rc);
  if( pOne ){
    pOne->iNext = 0;
    pOne->iShmid = 1;
  }
  return rc;
}