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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ i64 ;
struct TYPE_5__ {scalar_t__ pCompress; scalar_t__ nMap; int /*<<< orphan*/  pDb; TYPE_1__* pMapped; int /*<<< orphan*/ * pMap; int /*<<< orphan*/  fdDb; int /*<<< orphan*/  pEnv; } ;
struct TYPE_4__ {int /*<<< orphan*/  aData; struct TYPE_4__* pMappedNext; } ;
typedef  TYPE_1__ Page ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int PAGE_HASPREV ; 
 int /*<<< orphan*/  assert (int) ; 
 int lsmEnvRemap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  lsmSortedRemap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsGrowMapping(
  FileSystem *pFS,                /* File system object */
  i64 iSz,                        /* Minimum size to extend mapping to */
  int *pRc                        /* IN/OUT: Error code */
){
  assert( pFS->pCompress==0 );
  assert( PAGE_HASPREV==4 );

  if( *pRc==LSM_OK && iSz>pFS->nMap ){
    int rc;
    u8 *aOld = pFS->pMap;
    rc = lsmEnvRemap(pFS->pEnv, pFS->fdDb, iSz, &pFS->pMap, &pFS->nMap);
    if( rc==LSM_OK && pFS->pMap!=aOld ){
      Page *pFix;
      i64 iOff = (u8 *)pFS->pMap - aOld;
      for(pFix=pFS->pMapped; pFix; pFix=pFix->pMappedNext){
        pFix->aData += iOff;
      }
      lsmSortedRemap(pFS->pDb);
    }
    *pRc = rc;
  }
}