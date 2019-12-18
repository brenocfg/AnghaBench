#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__* aSnapshot; int /*<<< orphan*/  pFS; } ;
typedef  TYPE_1__ lsm_db ;
typedef  int /*<<< orphan*/  MetaPage ;

/* Variables and functions */
 size_t CKPT_HDR_NCKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ckptChangeEndianness (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lsmFsMetaPageData (int /*<<< orphan*/ *,int*) ; 
 int lsmFsMetaPageGet (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ **) ; 
 int lsmFsMetaPageRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 

int lsmCheckpointStore(lsm_db *pDb, int iMeta){
  MetaPage *pPg = 0;
  int rc;

  assert( iMeta==1 || iMeta==2 );
  rc = lsmFsMetaPageGet(pDb->pFS, 1, iMeta, &pPg);
  if( rc==LSM_OK ){
    u8 *aData;
    int nData;
    int nCkpt;

    nCkpt = (int)pDb->aSnapshot[CKPT_HDR_NCKPT];
    aData = lsmFsMetaPageData(pPg, &nData);
    memcpy(aData, pDb->aSnapshot, nCkpt*sizeof(u32));
    ckptChangeEndianness((u32 *)aData, nCkpt);
    rc = lsmFsMetaPageRelease(pPg);
  }
      
  return rc;
}