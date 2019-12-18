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
struct TYPE_5__ {scalar_t__ pVtab; } ;
struct TYPE_6__ {int nInstCount; int* aInst; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  Fts5Table ;
typedef  TYPE_2__ Fts5Cursor ;
typedef  int /*<<< orphan*/  Fts5Context ;

/* Variables and functions */
 scalar_t__ CsrFlagTest (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTS5CSR_REQUIRE_INST ; 
 int SQLITE_OK ; 
 int SQLITE_RANGE ; 
 int fts5CacheInstArray (TYPE_2__*) ; 
 scalar_t__ fts5IsOffsetless (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5ApiInst(
  Fts5Context *pCtx, 
  int iIdx, 
  int *piPhrase, 
  int *piCol, 
  int *piOff
){
  Fts5Cursor *pCsr = (Fts5Cursor*)pCtx;
  int rc = SQLITE_OK;
  if( CsrFlagTest(pCsr, FTS5CSR_REQUIRE_INST)==0 
   || SQLITE_OK==(rc = fts5CacheInstArray(pCsr)) 
  ){
    if( iIdx<0 || iIdx>=pCsr->nInstCount ){
      rc = SQLITE_RANGE;
#if 0
    }else if( fts5IsOffsetless((Fts5Table*)pCsr->base.pVtab) ){
      *piPhrase = pCsr->aInst[iIdx*3];
      *piCol = pCsr->aInst[iIdx*3 + 2];
      *piOff = -1;
#endif
    }else{
      *piPhrase = pCsr->aInst[iIdx*3];
      *piCol = pCsr->aInst[iIdx*3 + 1];
      *piOff = pCsr->aInst[iIdx*3 + 2];
    }
  }
  return rc;
}