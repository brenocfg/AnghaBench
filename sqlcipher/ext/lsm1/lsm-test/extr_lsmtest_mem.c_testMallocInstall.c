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
struct TYPE_7__ {int /*<<< orphan*/  xFree; int /*<<< orphan*/  xRealloc; int /*<<< orphan*/  xMalloc; void* pMemCtx; int /*<<< orphan*/  (* xMutexStatic ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ lsm_env ;
struct TYPE_8__ {int /*<<< orphan*/  xSaveFree; int /*<<< orphan*/  xSaveRealloc; int /*<<< orphan*/  xSaveMalloc; void* pMutex; int /*<<< orphan*/  xDelMutex; int /*<<< orphan*/  xLeaveMutex; int /*<<< orphan*/  xEnterMutex; scalar_t__ (* xMalloc ) (int) ;int /*<<< orphan*/  xFree; int /*<<< orphan*/  xRealloc; } ;
typedef  TYPE_2__ TmGlobal ;
struct TYPE_9__ {int /*<<< orphan*/  pMutex; TYPE_1__* pEnv; } ;
typedef  TYPE_3__ LsmMutex ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_MUTEX_HEAP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmLsmEnvFree ; 
 int /*<<< orphan*/  tmLsmEnvMalloc ; 
 int /*<<< orphan*/  tmLsmEnvRealloc ; 
 int /*<<< orphan*/  tmLsmFree ; 
 scalar_t__ tmLsmMalloc (int) ; 
 int /*<<< orphan*/  tmLsmMutexDel ; 
 int /*<<< orphan*/  tmLsmMutexEnter ; 
 int /*<<< orphan*/  tmLsmMutexLeave ; 
 int /*<<< orphan*/  tmLsmRealloc ; 

void testMallocInstall(lsm_env *pEnv){
  TmGlobal *pGlobal;
  LsmMutex *pMutex;
  assert( pEnv->pMemCtx==0 );

  /* Allocate and populate a TmGlobal structure. */
  pGlobal = (TmGlobal *)tmLsmMalloc(sizeof(TmGlobal));
  memset(pGlobal, 0, sizeof(TmGlobal));
  pGlobal->xMalloc = tmLsmMalloc;
  pGlobal->xRealloc = tmLsmRealloc;
  pGlobal->xFree = tmLsmFree;
  pMutex = (LsmMutex *)pGlobal->xMalloc(sizeof(LsmMutex));
  pMutex->pEnv = pEnv;
  pEnv->xMutexStatic(pEnv, LSM_MUTEX_HEAP, &pMutex->pMutex);
  pGlobal->xEnterMutex = tmLsmMutexEnter;
  pGlobal->xLeaveMutex = tmLsmMutexLeave;
  pGlobal->xDelMutex = tmLsmMutexDel;
  pGlobal->pMutex = (void *)pMutex;

  pGlobal->xSaveMalloc = pEnv->xMalloc;
  pGlobal->xSaveRealloc = pEnv->xRealloc;
  pGlobal->xSaveFree = pEnv->xFree;

  /* Set up pEnv to the use the new TmGlobal */
  pEnv->pMemCtx = (void *)pGlobal;
  pEnv->xMalloc = tmLsmEnvMalloc;
  pEnv->xRealloc = tmLsmEnvRealloc;
  pEnv->xFree = tmLsmEnvFree;
}