#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pFS; } ;
typedef  TYPE_1__ lsm_db ;
typedef  scalar_t__ i64 ;
typedef  int /*<<< orphan*/  MetaPage ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  ckptLoadEmpty (TYPE_1__*) ; 
 scalar_t__ ckptLoadId (int /*<<< orphan*/ *) ; 
 int ckptTryLoad (TYPE_1__*,int /*<<< orphan*/ *,int,int*) ; 
 int lsmFsMetaPageGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lsmFsMetaPageRelease (int /*<<< orphan*/ *) ; 

int lsmCheckpointRecover(lsm_db *pDb){
  int rc = LSM_OK;                /* Return Code */
  i64 iId1;                       /* Id of checkpoint on meta-page 1 */
  i64 iId2;                       /* Id of checkpoint on meta-page 2 */
  int bLoaded = 0;                /* True once checkpoint has been loaded */
  int cmp;                        /* True if (iId2>iId1) */
  MetaPage *apPg[2] = {0, 0};     /* Meta-pages 1 and 2 */

  rc = lsmFsMetaPageGet(pDb->pFS, 0, 1, &apPg[0]);
  if( rc==LSM_OK ) rc = lsmFsMetaPageGet(pDb->pFS, 0, 2, &apPg[1]);

  iId1 = ckptLoadId(apPg[0]);
  iId2 = ckptLoadId(apPg[1]);
  cmp = (iId2 > iId1);
  bLoaded = ckptTryLoad(pDb, apPg[cmp?1:0], (cmp?2:1), &rc);
  if( bLoaded==0 ){
    bLoaded = ckptTryLoad(pDb, apPg[cmp?0:1], (cmp?1:2), &rc);
  }

  /* The database does not contain a valid checkpoint. Initialize the shared
  ** memory header with an empty checkpoint.  */
  if( bLoaded==0 ){
    ckptLoadEmpty(pDb);
  }

  lsmFsMetaPageRelease(apPg[0]);
  lsmFsMetaPageRelease(apPg[1]);

  return rc;
}