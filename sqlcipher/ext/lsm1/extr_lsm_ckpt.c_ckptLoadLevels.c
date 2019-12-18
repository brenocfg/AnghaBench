#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  void* u16 ;
struct TYPE_8__ {int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_9__ {int nRight; int /*<<< orphan*/ * aRhs; int /*<<< orphan*/  lhs; struct TYPE_9__* pNext; void* flags; void* iAge; } ;
typedef  int /*<<< orphan*/  Segment ;
typedef  TYPE_2__ Level ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  ckptNewSegment (int*,int*,int /*<<< orphan*/ *) ; 
 int ckptSetupMerge (TYPE_1__*,int*,int*,TYPE_2__*) ; 
 scalar_t__ lsmMallocZeroRc (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  lsmSortedFreeLevel (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int ckptLoadLevels(
  lsm_db *pDb,
  u32 *aIn, 
  int *piIn, 
  int nLevel,
  Level **ppLevel
){
  int i;
  int rc = LSM_OK;
  Level *pRet = 0;
  Level **ppNext;
  int iIn = *piIn;

  ppNext = &pRet;
  for(i=0; rc==LSM_OK && i<nLevel; i++){
    int iRight;
    Level *pLevel;

    /* Allocate space for the Level structure and Level.apRight[] array */
    pLevel = (Level *)lsmMallocZeroRc(pDb->pEnv, sizeof(Level), &rc);
    if( rc==LSM_OK ){
      pLevel->iAge = (u16)(aIn[iIn] & 0x0000FFFF);
      pLevel->flags = (u16)((aIn[iIn]>>16) & 0x0000FFFF);
      iIn++;
      pLevel->nRight = aIn[iIn++];
      if( pLevel->nRight ){
        int nByte = sizeof(Segment) * pLevel->nRight;
        pLevel->aRhs = (Segment *)lsmMallocZeroRc(pDb->pEnv, nByte, &rc);
      }
      if( rc==LSM_OK ){
        *ppNext = pLevel;
        ppNext = &pLevel->pNext;

        /* Allocate the main segment */
        ckptNewSegment(aIn, &iIn, &pLevel->lhs);

        /* Allocate each of the right-hand segments, if any */
        for(iRight=0; iRight<pLevel->nRight; iRight++){
          ckptNewSegment(aIn, &iIn, &pLevel->aRhs[iRight]);
        }

        /* Set up the Merge object, if required */
        if( pLevel->nRight>0 ){
          rc = ckptSetupMerge(pDb, aIn, &iIn, pLevel);
        }
      }
    }
  }

  if( rc!=LSM_OK ){
    /* An OOM must have occurred. Free any level structures allocated and
    ** return the error to the caller. */
    lsmSortedFreeLevel(pDb->pEnv, pRet);
    pRet = 0;
  }

  *ppLevel = pRet;
  *piIn = iIn;
  return rc;
}