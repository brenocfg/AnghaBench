#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_13__ {scalar_t__ nChunk; scalar_t__ iFirst; scalar_t__ iNextShmid; } ;
struct TYPE_14__ {int /*<<< orphan*/  pEnv; TYPE_1__ treehdr; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_16__ {scalar_t__ iShmid; int iNext; } ;
struct TYPE_15__ {int iLoc; TYPE_4__* pShm; } ;
typedef  TYPE_3__ ShmChunkLoc ;
typedef  TYPE_4__ ShmChunk ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* lsmMallocZeroRc (int /*<<< orphan*/ ,int,int*) ; 
 int shm_sequence_ge (scalar_t__,scalar_t__) ; 
 int treeCheckLinkedList (TYPE_2__*) ; 
 TYPE_4__* treeShmChunk (TYPE_2__*,int) ; 
 TYPE_4__* treeShmChunkRc (TYPE_2__*,int,int*) ; 

__attribute__((used)) static int treeRepairList(lsm_db *db){
  int rc = LSM_OK;
  int i;
  ShmChunk *p;
  ShmChunk *pMin = 0;
  u32 iMin = 0;

  /* Iterate through all shm chunks. Find the smallest shm-id present in
  ** the shared-memory region. */
  for(i=1; rc==LSM_OK && (u32)i<db->treehdr.nChunk; i++){
    p = treeShmChunkRc(db, i, &rc);
    if( p && (pMin==0 || shm_sequence_ge(pMin->iShmid, p->iShmid)) ){
      pMin = p;
      iMin = i;
    }
  }

  /* Fix the shm-id values on any chunks with a shm-id greater than or 
  ** equal to treehdr.iNextShmid. Then do a merge-sort of all chunks to 
  ** fix the ShmChunk.iNext pointers.
  */
  if( rc==LSM_OK ){
    int nSort;
    int nByte;
    u32 iPrevShmid;
    ShmChunkLoc *aSort;

    /* Allocate space for a merge sort. */
    nSort = 1;
    while( (u32)nSort < (db->treehdr.nChunk-1) ) nSort = nSort * 2;
    nByte = sizeof(ShmChunkLoc) * nSort * 2;
    aSort = lsmMallocZeroRc(db->pEnv, nByte, &rc);
    iPrevShmid = pMin->iShmid;

    /* Fix all shm-ids, if required. */
    if( rc==LSM_OK ){
      iPrevShmid = pMin->iShmid-1;
      for(i=1; (u32)i<db->treehdr.nChunk; i++){
        p = treeShmChunk(db, i);
        aSort[i-1].pShm = p;
        aSort[i-1].iLoc = i;
        if( (u32)i!=db->treehdr.iFirst ){
          if( shm_sequence_ge(p->iShmid, db->treehdr.iNextShmid) ){
            p->iShmid = iPrevShmid--;
          }
        }
      }
      if( iMin!=db->treehdr.iFirst ){
        p = treeShmChunk(db, db->treehdr.iFirst);
        p->iShmid = iPrevShmid;
      }
    }

    if( rc==LSM_OK ){
      ShmChunkLoc *aSpace = &aSort[nSort];
      for(i=0; i<nSort; i++){
        if( aSort[i].pShm ){
          assert( shm_sequence_ge(aSort[i].pShm->iShmid, iPrevShmid) );
          assert( aSpace[aSort[i].pShm->iShmid - iPrevShmid].pShm==0 );
          aSpace[aSort[i].pShm->iShmid - iPrevShmid] = aSort[i];
        }
      }

      if( aSpace[nSort-1].pShm ) aSpace[nSort-1].pShm->iNext = 0;
      for(i=0; i<nSort-1; i++){
        if( aSpace[i].pShm ){
          aSpace[i].pShm->iNext = aSpace[i+1].iLoc;
        }
      }

      rc = treeCheckLinkedList(db);
      lsmFree(db->pEnv, aSort);
    }
  }

  return rc;
}