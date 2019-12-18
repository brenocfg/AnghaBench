#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ pClient; scalar_t__ pWorker; int /*<<< orphan*/ * aSnapshot; } ;
typedef  TYPE_1__ lsm_db ;

/* Variables and functions */
 size_t CKPT_HDR_CMPID ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int lsmCheckpointLoad (TYPE_1__*,int /*<<< orphan*/ ) ; 

int lsmInfoCompressionId(lsm_db *db, u32 *piCmpId){
  int rc;

  assert( db->pClient==0 && db->pWorker==0 );
  rc = lsmCheckpointLoad(db, 0);
  if( rc==LSM_OK ){
    *piCmpId = db->aSnapshot[CKPT_HDR_CMPID];
  }

  return rc;
}