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
typedef  int /*<<< orphan*/  lsm_db ;
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_3__ {int /*<<< orphan*/  nDel; int /*<<< orphan*/  iDelStart; int /*<<< orphan*/  nIns; int /*<<< orphan*/  iInsStart; } ;
typedef  TYPE_1__ SetupStep ;
typedef  int /*<<< orphan*/  Datasource ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_CONFIG_AUTOFLUSH ; 
 int /*<<< orphan*/  lsm_begin (int /*<<< orphan*/ *,int) ; 
 int lsm_checkpoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsm_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsm_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int lsm_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tdb_lsm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testDeleteDatasourceRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testWriteDatasourceRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void doSetupStep(
  TestDb *pDb, 
  Datasource *pData, 
  const SetupStep *pStep, 
  int *pRc
){
  testWriteDatasourceRange(pDb, pData, pStep->iInsStart, pStep->nIns, pRc);
  testDeleteDatasourceRange(pDb, pData, pStep->iDelStart, pStep->nDel, pRc);
  if( *pRc==0 ){
    int nSave = -1;
    int nBuf = 64;
    lsm_db *db = tdb_lsm(pDb);

    lsm_config(db, LSM_CONFIG_AUTOFLUSH, &nSave);
    lsm_config(db, LSM_CONFIG_AUTOFLUSH, &nBuf);
    lsm_begin(db, 1);
    lsm_commit(db, 0);
    lsm_config(db, LSM_CONFIG_AUTOFLUSH, &nSave);

    *pRc = lsm_work(db, 0, 0, 0);
    if( *pRc==0 ){
      *pRc = lsm_checkpoint(db, 0);
    }
  }
}