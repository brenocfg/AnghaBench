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
struct TYPE_9__ {int nData; void* pData; } ;
struct TYPE_8__ {int flags; TYPE_3__ val; TYPE_1__* pDb; int /*<<< orphan*/ * aTree; } ;
struct TYPE_7__ {int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_2__ MultiCursor ;

/* Variables and functions */
 int CURSOR_IGNORE_DELETE ; 
 int CURSOR_SEEK_EQ ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mcursorLocationOk (TYPE_2__*,int) ; 
 int multiCursorGetVal (TYPE_2__*,int /*<<< orphan*/ ,void**,int*) ; 
 int sortedBlobSet (int /*<<< orphan*/ ,TYPE_3__*,void*,int) ; 

int lsmMCursorValue(MultiCursor *pCsr, void **ppVal, int *pnVal){
  void *pVal;
  int nVal;
  int rc;
  if( (pCsr->flags & CURSOR_SEEK_EQ) || pCsr->aTree==0 ){
    rc = LSM_OK;
    nVal = pCsr->val.nData;
    pVal = pCsr->val.pData;
  }else{

    assert( pCsr->aTree );
    assert( mcursorLocationOk(pCsr, (pCsr->flags & CURSOR_IGNORE_DELETE)) );

    rc = multiCursorGetVal(pCsr, pCsr->aTree[1], &pVal, &nVal);
    if( pVal && rc==LSM_OK ){
      rc = sortedBlobSet(pCsr->pDb->pEnv, &pCsr->val, pVal, nVal);
      pVal = pCsr->val.pData;
    }

    if( rc!=LSM_OK ){
      pVal = 0;
      nVal = 0;
    }
  }
  *ppVal = pVal;
  *pnVal = nVal;
  return rc;
}