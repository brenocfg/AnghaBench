#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pFS; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_10__ {int iPg; TYPE_2__* pSeg; int /*<<< orphan*/  pFS; } ;
struct TYPE_9__ {int /*<<< orphan*/  iRoot; } ;
typedef  TYPE_2__ Segment ;
typedef  TYPE_3__ BtreeCursor ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__* lsmMallocZeroRc (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int btreeCursorNew(
  lsm_db *pDb,
  Segment *pSeg,
  BtreeCursor **ppCsr
){
  int rc = LSM_OK;
  BtreeCursor *pCsr;
  
  assert( pSeg->iRoot );
  pCsr = lsmMallocZeroRc(pDb->pEnv, sizeof(BtreeCursor), &rc);
  if( pCsr ){
    pCsr->pFS = pDb->pFS;
    pCsr->pSeg = pSeg;
    pCsr->iPg = -1;
  }

  *ppCsr = pCsr;
  return rc;
}