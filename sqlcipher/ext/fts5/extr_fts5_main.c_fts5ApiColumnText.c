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
struct TYPE_4__ {scalar_t__ pVtab; } ;
struct TYPE_5__ {scalar_t__ ePlan; int /*<<< orphan*/  pStmt; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  Fts5FullTable ;
typedef  TYPE_2__ Fts5Cursor ;
typedef  int /*<<< orphan*/  Fts5Context ;

/* Variables and functions */
 scalar_t__ FTS5_PLAN_SPECIAL ; 
 int SQLITE_OK ; 
 scalar_t__ fts5IsContentless (int /*<<< orphan*/ *) ; 
 int fts5SeekCursor (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fts5ApiColumnText(
  Fts5Context *pCtx, 
  int iCol, 
  const char **pz, 
  int *pn
){
  int rc = SQLITE_OK;
  Fts5Cursor *pCsr = (Fts5Cursor*)pCtx;
  if( fts5IsContentless((Fts5FullTable*)(pCsr->base.pVtab)) 
   || pCsr->ePlan==FTS5_PLAN_SPECIAL 
  ){
    *pz = 0;
    *pn = 0;
  }else{
    rc = fts5SeekCursor(pCsr, 0);
    if( rc==SQLITE_OK ){
      *pz = (const char*)sqlite3_column_text(pCsr->pStmt, iCol+1);
      *pn = sqlite3_column_bytes(pCsr->pStmt, iCol+1);
    }
  }
  return rc;
}