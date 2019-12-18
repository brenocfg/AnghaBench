#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nInstCount; } ;
typedef  TYPE_1__ Fts5Cursor ;
typedef  int /*<<< orphan*/  Fts5Context ;

/* Variables and functions */
 scalar_t__ CsrFlagTest (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTS5CSR_REQUIRE_INST ; 
 int SQLITE_OK ; 
 int fts5CacheInstArray (TYPE_1__*) ; 

__attribute__((used)) static int fts5ApiInstCount(Fts5Context *pCtx, int *pnInst){
  Fts5Cursor *pCsr = (Fts5Cursor*)pCtx;
  int rc = SQLITE_OK;
  if( CsrFlagTest(pCsr, FTS5CSR_REQUIRE_INST)==0 
   || SQLITE_OK==(rc = fts5CacheInstArray(pCsr)) ){
    *pnInst = pCsr->nInstCount;
  }
  return rc;
}