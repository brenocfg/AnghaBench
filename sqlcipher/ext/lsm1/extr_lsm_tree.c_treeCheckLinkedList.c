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
typedef  int u32 ;
struct TYPE_7__ {int iFirst; int nChunk; } ;
struct TYPE_8__ {TYPE_1__ treehdr; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_9__ {int iNext; scalar_t__ iShmid; } ;
typedef  TYPE_3__ ShmChunk ;

/* Variables and functions */
 int LSM_CORRUPT_BKPT ; 
 int LSM_OK ; 
 TYPE_3__* treeShmChunkRc (TYPE_2__*,int,int*) ; 

__attribute__((used)) static int treeCheckLinkedList(lsm_db *db){
  int rc = LSM_OK;
  int nVisit = 0;
  ShmChunk *p;

  p = treeShmChunkRc(db, db->treehdr.iFirst, &rc);
  while( rc==LSM_OK && p ){
    if( p->iNext ){
      if( p->iNext>=db->treehdr.nChunk ){
        rc = LSM_CORRUPT_BKPT;
      }else{
        ShmChunk *pNext = treeShmChunkRc(db, p->iNext, &rc);
        if( rc==LSM_OK ){
          if( pNext->iShmid!=p->iShmid+1 ){
            rc = LSM_CORRUPT_BKPT;
          }
          p = pNext;
        }
      }
    }else{
      p = 0;
    }
    nVisit++;
  }

  if( rc==LSM_OK && (u32)nVisit!=db->treehdr.nChunk-1 ){
    rc = LSM_CORRUPT_BKPT;
  }
  return rc;
}