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
struct TYPE_5__ {int iPg; int /*<<< orphan*/  eType; int /*<<< orphan*/  blob; scalar_t__ nKey; scalar_t__ pKey; TYPE_1__* aPg; int /*<<< orphan*/  pSeg; } ;
struct TYPE_4__ {int iCell; int /*<<< orphan*/  pPage; } ;
typedef  int /*<<< orphan*/  LsmPgno ;
typedef  TYPE_2__ BtreeCursor ;

/* Variables and functions */
 int LSM_CORRUPT_BKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  LSM_SEPARATOR ; 
 int pageGetBtreeKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btreeCursorLoadKey(BtreeCursor *pCsr){
  int rc = LSM_OK;
  if( pCsr->iPg<0 ){
    pCsr->pKey = 0;
    pCsr->nKey = 0;
    pCsr->eType = 0;
  }else{
    LsmPgno dummy;
    int iPg = pCsr->iPg;
    int iCell = pCsr->aPg[iPg].iCell;
    while( iCell<0 && (--iPg)>=0 ){
      iCell = pCsr->aPg[iPg].iCell-1;
    }
    if( iPg<0 || iCell<0 ) return LSM_CORRUPT_BKPT;

    rc = pageGetBtreeKey(
        pCsr->pSeg,
        pCsr->aPg[iPg].pPage, iCell,
        &dummy, &pCsr->eType, &pCsr->pKey, &pCsr->nKey, &pCsr->blob
    );
    pCsr->eType |= LSM_SEPARATOR;
  }

  return rc;
}