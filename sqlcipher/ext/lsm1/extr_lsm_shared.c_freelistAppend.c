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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  lsm_env ;
struct TYPE_10__ {TYPE_1__* pWorker; TYPE_4__* pFreelist; scalar_t__ bUseFreelist; int /*<<< orphan*/ * pEnv; } ;
typedef  TYPE_2__ lsm_db ;
typedef  int i64 ;
struct TYPE_12__ {int nAlloc; int nEntry; TYPE_3__* aEntry; } ;
struct TYPE_11__ {scalar_t__ iBlk; int iId; } ;
struct TYPE_9__ {TYPE_4__ freelist; } ;
typedef  TYPE_3__ FreelistEntry ;
typedef  TYPE_4__ Freelist ;

/* Variables and functions */
 int LSM_NOMEM_BKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ lsmRealloc (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memmove (TYPE_3__*,TYPE_3__*,int) ; 

int freelistAppend(lsm_db *db, u32 iBlk, i64 iId){
  lsm_env *pEnv = db->pEnv;
  Freelist *p;
  int i; 

  assert( iId==-1 || iId>=0 );
  p = db->bUseFreelist ? db->pFreelist : &db->pWorker->freelist;

  /* Extend the space allocated for the freelist, if required */
  assert( p->nAlloc>=p->nEntry );
  if( p->nAlloc==p->nEntry ){
    int nNew; 
    int nByte; 
    FreelistEntry *aNew;

    nNew = (p->nAlloc==0 ? 4 : p->nAlloc*2);
    nByte = sizeof(FreelistEntry) * nNew;
    aNew = (FreelistEntry *)lsmRealloc(pEnv, p->aEntry, nByte);
    if( !aNew ) return LSM_NOMEM_BKPT;
    p->nAlloc = nNew;
    p->aEntry = aNew;
  }

  for(i=0; i<p->nEntry; i++){
    assert( i==0 || p->aEntry[i].iBlk > p->aEntry[i-1].iBlk );
    if( p->aEntry[i].iBlk>=iBlk ) break;
  }

  if( i<p->nEntry && p->aEntry[i].iBlk==iBlk ){
    /* Clobber an existing entry */
    p->aEntry[i].iId = iId;
  }else{
    /* Insert a new entry into the list */
    int nByte = sizeof(FreelistEntry)*(p->nEntry-i);
    memmove(&p->aEntry[i+1], &p->aEntry[i], nByte);
    p->aEntry[i].iBlk = iBlk;
    p->aEntry[i].iId = iId;
    p->nEntry++;
  }

  return LSM_OK;
}