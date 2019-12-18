#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ nTransOpen; int nTreeLimit; scalar_t__ bAutowork; int /*<<< orphan*/  pFS; } ;
typedef  TYPE_1__ lsm_db ;

/* Variables and functions */
 int LSM_AUTOWORK_QUANT ; 
 int LSM_DELETE ; 
 int LSM_DRANGE ; 
 int LSM_MAX (int,int) ; 
 int LSM_OK ; 
 int LSM_WRITE ; 
 int lsmFsPageSize (int /*<<< orphan*/ ) ; 
 int lsmLogWrite (TYPE_1__*,int,void*,int,void*,int) ; 
 int lsmSortedAutoWork (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lsmSortedSaveTreeCursors (TYPE_1__*) ; 
 int lsmTreeDelete (TYPE_1__*,void*,int,void*,int) ; 
 int lsmTreeInsert (TYPE_1__*,void*,int,void*,int) ; 
 int lsmTreeSize (TYPE_1__*) ; 
 int lsm_begin (TYPE_1__*,int) ; 
 int lsm_commit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsm_rollback (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int doWriteOp(
  lsm_db *pDb,
  int bDeleteRange,
  const void *pKey, int nKey,     /* Key to write or delete */
  const void *pVal, int nVal      /* Value to write. Or nVal==-1 for a delete */
){
  int rc = LSM_OK;                /* Return code */
  int bCommit = 0;                /* True to commit before returning */

  if( pDb->nTransOpen==0 ){
    bCommit = 1;
    rc = lsm_begin(pDb, 1);
  }

  if( rc==LSM_OK ){
    int eType = (bDeleteRange ? LSM_DRANGE : (nVal>=0?LSM_WRITE:LSM_DELETE));
    rc = lsmLogWrite(pDb, eType, (void *)pKey, nKey, (void *)pVal, nVal);
  }

  lsmSortedSaveTreeCursors(pDb);

  if( rc==LSM_OK ){
    int pgsz = lsmFsPageSize(pDb->pFS);
    int nQuant = LSM_AUTOWORK_QUANT * pgsz;
    int nBefore;
    int nAfter;
    int nDiff;

    if( nQuant>pDb->nTreeLimit ){
      nQuant = LSM_MAX(pDb->nTreeLimit, pgsz);
    }

    nBefore = lsmTreeSize(pDb);
    if( bDeleteRange ){
      rc = lsmTreeDelete(pDb, (void *)pKey, nKey, (void *)pVal, nVal);
    }else{
      rc = lsmTreeInsert(pDb, (void *)pKey, nKey, (void *)pVal, nVal);
    }

    nAfter = lsmTreeSize(pDb);
    nDiff = (nAfter/nQuant) - (nBefore/nQuant);
    if( rc==LSM_OK && pDb->bAutowork && nDiff!=0 ){
      rc = lsmSortedAutoWork(pDb, nDiff * LSM_AUTOWORK_QUANT);
    }
  }

  /* If a transaction was opened at the start of this function, commit it. 
  ** Or, if an error has occurred, roll it back.  */
  if( bCommit ){
    if( rc==LSM_OK ){
      rc = lsm_commit(pDb, 0);
    }else{
      lsm_rollback(pDb, 0);
    }
  }

  return rc;
}