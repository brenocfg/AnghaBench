#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bReadonly; TYPE_2__* pFS; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_6__ {scalar_t__ fdLog; } ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int LSM_IOERR_NOENT ; 
 int LSM_OK ; 
 scalar_t__ fsOpenFile (TYPE_2__*,int /*<<< orphan*/ ,int,int*) ; 

int lsmFsOpenLog(lsm_db *db, int *pbOpen){
  int rc = LSM_OK;
  FileSystem *pFS = db->pFS;

  if( 0==pFS->fdLog ){ 
    pFS->fdLog = fsOpenFile(pFS, db->bReadonly, 1, &rc); 

    if( rc==LSM_IOERR_NOENT && db->bReadonly ){
      rc = LSM_OK;
    }
  }

  if( pbOpen ) *pbOpen = (pFS->fdLog!=0);
  return rc;
}