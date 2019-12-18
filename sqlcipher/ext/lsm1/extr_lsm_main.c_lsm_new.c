#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_env ;
struct TYPE_4__ {int /*<<< orphan*/  iId; } ;
struct TYPE_5__ {int iReader; int iRwclient; TYPE_1__ compress; int /*<<< orphan*/  xLog; int /*<<< orphan*/  iMmap; int /*<<< orphan*/  bMultiProc; int /*<<< orphan*/  bUseLog; int /*<<< orphan*/  nMaxFreelist; int /*<<< orphan*/  nMerge; int /*<<< orphan*/  nDfltBlksz; int /*<<< orphan*/  nDfltPgsz; int /*<<< orphan*/  xCmp; int /*<<< orphan*/  eSafety; int /*<<< orphan*/  bAutowork; int /*<<< orphan*/  nAutockpt; int /*<<< orphan*/  nTreeLimit; int /*<<< orphan*/ * pEnv; } ;
typedef  TYPE_2__ lsm_db ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_COMPRESSION_NONE ; 
 int /*<<< orphan*/  LSM_DFLT_AUTOCHECKPOINT ; 
 int /*<<< orphan*/  LSM_DFLT_AUTOFLUSH ; 
 int /*<<< orphan*/  LSM_DFLT_AUTOMERGE ; 
 int /*<<< orphan*/  LSM_DFLT_AUTOWORK ; 
 int /*<<< orphan*/  LSM_DFLT_BLOCK_SIZE ; 
 int /*<<< orphan*/  LSM_DFLT_MMAP ; 
 int /*<<< orphan*/  LSM_DFLT_MULTIPLE_PROCESSES ; 
 int /*<<< orphan*/  LSM_DFLT_PAGE_SIZE ; 
 int /*<<< orphan*/  LSM_DFLT_SAFETY ; 
 int /*<<< orphan*/  LSM_DFLT_USE_LOG ; 
 int /*<<< orphan*/  LSM_MAX_FREELIST_ENTRIES ; 
 int LSM_NOMEM_BKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ lsmMallocZero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lsm_default_env () ; 
 int /*<<< orphan*/  xCmp ; 
 int /*<<< orphan*/  xLog ; 

int lsm_new(lsm_env *pEnv, lsm_db **ppDb){
  lsm_db *pDb;

  /* If the user did not provide an environment, use the default. */
  if( pEnv==0 ) pEnv = lsm_default_env();
  assert( pEnv );

  /* Allocate the new database handle */
  *ppDb = pDb = (lsm_db *)lsmMallocZero(pEnv, sizeof(lsm_db));
  if( pDb==0 ) return LSM_NOMEM_BKPT;

  /* Initialize the new object */
  pDb->pEnv = pEnv;
  pDb->nTreeLimit = LSM_DFLT_AUTOFLUSH;
  pDb->nAutockpt = LSM_DFLT_AUTOCHECKPOINT;
  pDb->bAutowork = LSM_DFLT_AUTOWORK;
  pDb->eSafety = LSM_DFLT_SAFETY;
  pDb->xCmp = xCmp;
  pDb->nDfltPgsz = LSM_DFLT_PAGE_SIZE;
  pDb->nDfltBlksz = LSM_DFLT_BLOCK_SIZE;
  pDb->nMerge = LSM_DFLT_AUTOMERGE;
  pDb->nMaxFreelist = LSM_MAX_FREELIST_ENTRIES;
  pDb->bUseLog = LSM_DFLT_USE_LOG;
  pDb->iReader = -1;
  pDb->iRwclient = -1;
  pDb->bMultiProc = LSM_DFLT_MULTIPLE_PROCESSES;
  pDb->iMmap = LSM_DFLT_MMAP;
  pDb->xLog = xLog;
  pDb->compress.iId = LSM_COMPRESSION_NONE;
  return LSM_OK;
}