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
struct TYPE_5__ {scalar_t__ aTree; int nPtr; scalar_t__ pBtCsr; int nTree; TYPE_1__* pDb; } ;
struct TYPE_4__ {int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_2__ MultiCursor ;

/* Variables and functions */
 int CURSOR_DATA_SEGMENT ; 
 int LSM_OK ; 
 scalar_t__ lsmMallocZeroRc (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int multiCursorAllocTree(MultiCursor *pCsr){
  int rc = LSM_OK;
  if( pCsr->aTree==0 ){
    int nByte;                    /* Bytes of space to allocate */
    int nMin;                     /* Total number of cursors being merged */

    nMin = CURSOR_DATA_SEGMENT + pCsr->nPtr + (pCsr->pBtCsr!=0);
    pCsr->nTree = 2;
    while( pCsr->nTree<nMin ){
      pCsr->nTree = pCsr->nTree*2;
    }

    nByte = sizeof(int)*pCsr->nTree*2;
    pCsr->aTree = (int *)lsmMallocZeroRc(pCsr->pDb->pEnv, nByte, &rc);
  }
  return rc;
}