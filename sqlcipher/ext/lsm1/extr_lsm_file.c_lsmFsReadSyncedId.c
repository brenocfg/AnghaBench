#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {TYPE_3__* pFS; } ;
typedef  TYPE_1__ lsm_db ;
typedef  scalar_t__ i64 ;
struct TYPE_11__ {scalar_t__ nMapLimit; scalar_t__ pMap; } ;
struct TYPE_10__ {int /*<<< orphan*/ * aData; } ;
typedef  TYPE_2__ MetaPage ;
typedef  TYPE_3__ FileSystem ;

/* Variables and functions */
 int LSM_META_PAGE_SIZE ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fsGrowMapping (TYPE_3__*,int,int*) ; 
 int lsmFsMetaPageGet (TYPE_3__*,int /*<<< orphan*/ ,int,TYPE_2__**) ; 
 int /*<<< orphan*/  lsmFsMetaPageRelease (TYPE_2__*) ; 
 scalar_t__ lsmGetU64 (int /*<<< orphan*/ *) ; 

int lsmFsReadSyncedId(lsm_db *db, int iMeta, i64 *piVal){
  FileSystem *pFS = db->pFS;
  int rc = LSM_OK;

  assert( iMeta==1 || iMeta==2 );
  if( pFS->nMapLimit>0 ){
    fsGrowMapping(pFS, iMeta*LSM_META_PAGE_SIZE, &rc);
    if( rc==LSM_OK ){
      *piVal = (i64)lsmGetU64(&((u8 *)pFS->pMap)[(iMeta-1)*LSM_META_PAGE_SIZE]);
    }
  }else{
    MetaPage *pMeta = 0;
    rc = lsmFsMetaPageGet(pFS, 0, iMeta, &pMeta);
    if( rc==LSM_OK ){
      *piVal = (i64)lsmGetU64(pMeta->aData);
      lsmFsMetaPageRelease(pMeta);
    }
  }

  return rc;
}